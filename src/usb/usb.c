/* example based on libopencm3 miniblink/systick_blink/button/usb_simple examples
 *
 * original author:
 * Copyright (C) 2010 Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/usb/usbd.h>

// LEDs are on PA0 and PA1
#define PORT_LED GPIOA
#define PIN_LED0 GPIO0
#define PIN_LED1 GPIO1

// user button is on PA2
#define PORT_BUT GPIOA
#define PIN_BUT GPIO2

// USB pins are on PA11/PA12
#define PORT_USB GPIOA
#define PIN_USBDM GPIO11
#define PIN_USBDP GPIO12

volatile uint32_t counter = 0;

void sys_tick_handler(void) {
    ++counter;
}

uint32_t millis(void);
uint32_t millis(void) {
    return counter;
}

// device descriptor
const struct usb_device_descriptor dev = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE, // device descriptor
    .bcdUSB = 0x0200,                 // USB 2.0
    .bDeviceClass = 0xFF,             // vendor-specified class code
    .bDeviceSubClass = 0,             // subclass 0
    .bDeviceProtocol = 0,             // device protocol 0
    .bMaxPacketSize0 = 64,            // max packet size for endpoint 0
    .idVendor = 0xCAFE,               // vendor ID
    .idProduct = 0xCAFE,              // product ID
    .bcdDevice = 0x0200,              // Device Release Number (2.0?)
    .iManufacturer = 1,               // Manufacturer string is at index 1
    .iProduct = 2,                    // product string is at index 2
    .iSerialNumber = 3,               // serial number string is at index 3
    .bNumConfigurations = 1,          // only 1 configuration
};

// interface descriptor
const struct usb_interface_descriptor iface = {
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,    // interface descriptor
    .bInterfaceNumber = 0,                  // this is interface 0
    .bAlternateSetting = 0,                 // this is alternate setting 0 for iface0
    .bNumEndpoints = 0, // 0 endpoints for this interface (other than endpoint0)
    .bInterfaceClass = 0xFF,                // vendor-specified class code
    .bInterfaceSubClass = 0,                // subclass 0
    .bInterfaceProtocol = 0,                // interface protocol 0
    .iInterface = 0,                        // interface string is at index 0 (N/A)
};

// interface list
// TODO: libopencm3 says this should not need to be implemented in user code
// however, this is the only way interfaces are specified, and it doesn't work
// without this
const struct usb_interface ifaces[] = {{
    .num_altsetting = 1,
    .altsetting = &iface,
}};

// configuration descriptor
const struct usb_config_descriptor config = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION, // configuration descriptor
    // wTotalLength: number of bytes returned
    // this accounts for the configuration descriptor and the interface
    // descriptors for the configuration (only one interface)
    // any endpoints would also be included, but we don't have any other than
    // endpoint0, which is not counted
    .wTotalLength = USB_DT_CONFIGURATION_SIZE + USB_DT_INTERFACE_SIZE,
    .bNumInterfaces = 1,                     // only 1 interface in this config
    .bConfigurationValue = 1,                // this is configuration 1
    .iConfiguration = 0, // string descriptor for this config is at index 0 (N/A)
    .bmAttributes = 0x80,                    // bus powered
    .bMaxPower = 0x32,                       // 100mA (50 * 2mA)
    // TODO: libopencm3 docs says this shouldn't be necessary.
    // However, interfaces are not otherwise specified, and the device doesn't
    // work without it.
    .interface = ifaces,                     // interfaces for this configuration
};


// endpoint descriptor(s)
// (only endpoint0 exists, so none are specified)

// usb strings
const char *usb_strings[] = {
    "gkeeth technologies", // manufacturer
    "first test",          // product
    "1234",                // serial number
};

// buffer for control requests
uint8_t usbd_control_buffer[128];

static enum usbd_request_return_codes simple_control_callback(
        usbd_device *usbd_dev, struct usb_setup_data *req,
        uint8_t **buf, uint16_t *len,
        void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req)) {
    // avoid compiler warnings
    (void) buf;
    (void) len;
    (void) complete;
    (void) usbd_dev;

    if (req->bmRequestType != 0x40) {
        return USBD_REQ_NOTSUPP; // only vendor requests are supported
    }

    if (req->wValue & 1) {
        gpio_set(PORT_LED, PIN_LED0);
    } else {
        gpio_clear(PORT_LED, PIN_LED0);
    }

    return USBD_REQ_HANDLED;
}

// callback for "set config"
// on every "set config", this callback will register a "control" callback
static void usb_set_config_cb(usbd_device *usbd_dev, uint16_t wValue) {
    (void) wValue; // avoid compiler warning

    usbd_register_control_callback(usbd_dev,
            USB_REQ_TYPE_VENDOR, USB_REQ_TYPE_TYPE, simple_control_callback);
}

static void setup(void) {
    // use external 8MHz oscillator to derive 48MHz clock from PLL
    // this is an oscillator, not a crystal, so disable the builtin oscillator
    // circuit (enable oscillator bypass)
    rcc_osc_bypass_enable(RCC_HSE);
    rcc_clock_setup_in_hse_8mhz_out_48mhz();
    STK_CVR = 0; // clear systick current value to start immediately

    // enable clocks for USB & LED pins
    // clocks for USB peripheral itself are enabled by the USB driver, later
    rcc_periph_clock_enable(RCC_GPIOA);

    // Pins for usb don't need to be setup because they are additional
    // functions, not alternate functions
    // gpio_mode_setup(PORT_USB, GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_USBDM | PIN_USBDP);

    // set LED pins to output push-pull
    gpio_mode_setup(PORT_LED, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED0 | PIN_LED1);
}



int main(void) {
    usbd_device *usbd_dev;
    setup();
    usbd_dev = usbd_init(&st_usbfs_v2_usb_driver, &dev, &config, usb_strings, 3,
            usbd_control_buffer, sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(usbd_dev, usb_set_config_cb);

    while (1) {
        usbd_poll(usbd_dev);
    }

    return 0;
}


