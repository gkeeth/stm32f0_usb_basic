/*
 * USB CDC_ACM example
 *
 * based on libopencm3 usb_simple, usb_cdcacm examples
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

/*
 * Descriptor Organization:
 *
 * Device Descriptor
 *      Configuration Descriptor
 *              Interface Descriptor
 *                      Endpoint Descriptor
 * Device:
 * - Class: 0x2 (CDC)
 * - Subclass: 0 (reserved, TODO: try 02=ACM?)
 * - Device Protocol: 0 (no protocol required, TODO: try 01=AT protocol)
 * - Endpoint0 packet size: 64
 * - Vendor: 0xCAFE
 * - Product: 0xCAFE
 * - Device: 0x0200
 * - Manufacturer String Index: 1
 * - Product String Index: 2
 * - Serial Number Index: 3
 * - Number of Configurations: 1
 *
 *   Configuration:
 *   - Number of Interfaces: 2
 *   - Configuration Number: 1
 *   - Configuration String Index: 0 (N/A)
 *   - Configuration Attributes: 0x80 (bus powered)
 *   - Configuration Max Power: 0x32 (100mA)
 *
 *     Communications Interface:
 *     - interface number: 0
 *     - alternate setting: 0
 *     - number of endpoints: 1
 *     - interface class: CDC
 *     - interface subclass: ACM
 *     - interface protocol: AT
 *     - interface string index: 0 (N/A)
 *
 *       Management Endpoint:
 *       - address: 0x83 (input, endpoint3)
 *       - attributes: Interrupt
 *       - packet size: 16
 *       - interval: 255
 *
 *     Data Interface:
 *     - interface number: 1
 *     - alternate setting: 0
 *     - number of endpoints: 2
 *     - interface class: data
 *     - interface subclass: 0
 *     - interface protocol: 0
 *     - interface string index: 0 (N/A)
 *
 *       Data Endpoint 1:
 *       - address: 0x01 (output, endpoint1)
 *       - attributes: bulk
 *       - packet size: 64
 *       - interval: 1
 *
 *       Data Endpoint 2:
 *       - address: 0x82 (input, endpoint2)
 *       - attributes: bulk
 *       - packet size: 64
 *       - interval: 1
 *
 */

#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>

/* LEDs are on PA0 and PA1 */
#define PORT_LED GPIOA
#define PIN_LED0 GPIO0
#define PIN_LED1 GPIO1

/* user button is on PA2 */
#define PORT_BUT GPIOA
#define PIN_BUT GPIO2

/* USB pins are on PA11/PA12 */
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

const struct usb_device_descriptor dev = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE, /* device descriptor */
    .bcdUSB = 0x0200,                 /* USB 2.0 */
    .bDeviceClass = USB_CLASS_CDC,    /* vendor-specified class code */
    .bDeviceSubClass = 0,             /* subclass 0 */
    .bDeviceProtocol = 0,             /* device protocol 0 */
    .bMaxPacketSize0 = 64,            /* max packet size for endpoint 0 */
    .idVendor = 0xCAFE,               /* vendor ID */
    .idProduct = 0xCAFE,              /* product ID */
    .bcdDevice = 0x0200,              /* Device Release Number (2.0?) */
    .iManufacturer = 1,               /* Manufacturer string is at index 1 */
    .iProduct = 2,                    /* product string is at index 2 */
    .iSerialNumber = 3,               /* serial number string is at index 3 */
    .bNumConfigurations = 1,          /* only 1 configuration */
};

/* communications notification endpoint
 * libopencm3 example notes that linux cdc_acm driver requires this even
 * though it isn't necessary per USB CDC spec. */
#define ENDPOINT_ADDR_COMM_INPUT 0x83
#define PACKET_SIZE_COMM 16
static const struct usb_endpoint_descriptor comm_endp[] = {{
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = ENDPOINT_ADDR_COMM_INPUT,
    .bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
    .wMaxPacketSize = PACKET_SIZE_COMM,
    .bInterval = 255,
}};

/* data endpoints */
#define ENDPOINT_ADDR_DATA_OUTPUT 0x01
#define ENDPOINT_ADDR_DATA_INPUT 0x82
#define PACKET_SIZE_DATA 64
static const struct usb_endpoint_descriptor data_endp[] = {{
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = ENDPOINT_ADDR_DATA_OUTPUT,
    .bmAttributes = USB_ENDPOINT_ATTR_BULK,
    .wMaxPacketSize = PACKET_SIZE_DATA,
    .bInterval = 1,
}, {
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = ENDPOINT_ADDR_DATA_INPUT,
    .bmAttributes = USB_ENDPOINT_ATTR_BULK,
    .wMaxPacketSize = PACKET_SIZE_DATA,
    .bInterval = 1,
}};


/* CDC Functional Descriptors, USBCDC1.2 section 5.2.3 */
static const struct {
    struct usb_cdc_header_descriptor header;
    struct usb_cdc_call_management_descriptor call_mgmt;
    struct usb_cdc_acm_descriptor acm;
    struct usb_cdc_union_descriptor cdc_union;
} __attribute__((packed)) cdcacm_functional_descriptors = {
    .header = { /* USBCDC1.2 section 5.2.3.1 */
        .bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_HEADER,
        .bcdCDC = 0x0120, /* CDC Specification version 1.2 */
    },
    .call_mgmt = { /* PSTN1.2 section 5.3.1 */
        .bFunctionLength = sizeof(struct usb_cdc_call_management_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
        .bmCapabilities = 0, /* device doesn't handle call management*/
        .bDataInterface = 1, /* muxed commands handled by data_iface */
    },
    .acm = { /* PSTN1.2 section 5.3.2 */
        .bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_ACM,
        /* support SET/GET_LINE_CODING, SET_CONTROL_LINE_STATE, SERIAL_STATE */
        .bmCapabilities = 0x2,
    },
    .cdc_union = { /* USBCDC1.2 section 5.2.3.2 */
        .bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_UNION,
        .bControlInterface = 0, /* control interface is comm_iface */
        .bSubordinateInterface0 = 1, /* data_iface */
    }
};

const struct usb_interface_descriptor comm_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 0,
    .bAlternateSetting = 0,         /* alternate setting 0 for iface0 */
    .bNumEndpoints = 1,             /* one endpoint (besides default) */
    .bInterfaceClass = USB_CLASS_CDC,
    .bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
    .bInterfaceProtocol = USB_CDC_PROTOCOL_AT,
    .iInterface = 0,                /* interface string is at index 0 (N/A) */

    .endpoint = comm_endp,

    /* communications class-specific descriptor information */
    .extra = &cdcacm_functional_descriptors,
    .extralen = sizeof(cdcacm_functional_descriptors)
}};

const struct usb_interface_descriptor data_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 1,
    .bAlternateSetting = 0,         /* alternate setting 0 for iface1 */
    .bNumEndpoints = 2,             /* two endpoints: one input, one output*/
    .bInterfaceClass = USB_CLASS_DATA,
    .bInterfaceSubClass = 0,
    .bInterfaceProtocol = 0,
    .iInterface = 0,                /* interface string is at index 0 (N/A) */

    .endpoint = data_endp,

    /* data class does not define class-specific descriptor information */
}};

/* TODO: libopencm3 docs say this should not need to be implemented in user code
 * however, this is the only way interfaces are specified, and it doesn't work
 * without this */
const struct usb_interface ifaces[] = {{
    .num_altsetting = 1,
    .altsetting = comm_iface,
}, {
    .num_altsetting = 1,
    .altsetting = data_iface,
}};


const struct usb_config_descriptor config = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = 0, /* automatically calculated by driver */
    .bNumInterfaces = 2,
    .bConfigurationValue = 1,
    .iConfiguration = 0,        /* no configuration string provided */
    .bmAttributes = 0x80,       /* bus powered */
    .bMaxPower = 0x32,          /* 100mA (50 * 2mA) */

    /* TODO: libopencm3 docs say this shouldn't be necessary.
     * However, interfaces are not otherwise specified, and the device doesn't
     * work without it. */
    .interface = ifaces,
};

const char *usb_strings[] = {
    "gkeeth technologies", /* manufacturer */
    "first test",          /* product */
    "1234",                /* serial number */
};

/* buffer for control requests */
uint8_t usbd_control_buffer[128];

/* hardcode line coding */
static const struct usb_cdc_line_coding line_coding = {
    .dwDTERate = 115200,
    .bCharFormat = USB_CDC_1_STOP_BITS,
    .bParityType = USB_CDC_NO_PARITY,
    .bDataBits = 0x08,
};

#define USB_CDC_REQ_GET_LINE_CODING 0x21 /* not defined in usbcdc.h */
static enum usbd_request_return_codes cdcacm_control_request(
        usbd_device *usbd_dev, struct usb_setup_data *req,
        uint8_t **buf, uint16_t *len,
        void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req)) {
    /* avoid compiler warnings */
    (void) buf;
    (void) complete;
    (void) usbd_dev;

    switch (req->bRequest) {
    case USB_CDC_REQ_SET_CONTROL_LINE_STATE: {
        char local_buf[10];
        struct usb_cdc_notification *notif = (void *)local_buf;

        /* echo signals back to host */
        notif->bmRequestType = 0xA1; /* D-to-H, class, interface (USB9.3) */
        notif->bNotification = USB_CDC_NOTIFY_SERIAL_STATE;
        notif->wValue = 0;
        notif->wIndex = 0;
        notif->wLength = 2;
        local_buf[8] = req->wValue & 3;
        local_buf[9] = 0;
        usbd_ep_write_packet(usbd_dev, ENDPOINT_ADDR_COMM_INPUT, local_buf, 10);

        /* not a real transceiver, so no RTS/DTE lines to do anything with */
        return USBD_REQ_HANDLED;
    }
    case USB_CDC_REQ_SET_LINE_CODING:
        if (*len < sizeof(struct usb_cdc_line_coding)) {
            return USBD_REQ_NOTSUPP;
        }
        return USBD_REQ_HANDLED;
    case USB_CDC_REQ_GET_LINE_CODING:
        *buf = (uint8_t *) &line_coding;
        /* TODO: is buf automatically sent in a control transfer after return?
         * trace out call graph
         */
        return USBD_REQ_HANDLED;
    }

    return USBD_REQ_NOTSUPP;
}

static void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep) {
    (void) ep; /* avoid compiler warning */

    const int BUFSIZE = 64;
    char buf[BUFSIZE];

    /* read data from host */
    int len = usbd_ep_read_packet(usbd_dev, ENDPOINT_ADDR_DATA_OUTPUT, buf, BUFSIZE);
    if (len) {
        /* Toggle LED */
        gpio_toggle(PORT_LED, PIN_LED0);

        /* echo back to host
         * TODO: modify to achieve desired demo behavior */
        if (buf[0] == '\r') {
            /* clobber buf[1]... Assume single character in buf */
            /* TODO: handle multi-character buffers.
             * Any number of characters in buffer could be \r...
             * TODO: handle backspace?
             */
            buf[1] = '\n';
            ++len;
        }

        usbd_ep_write_packet(usbd_dev, ENDPOINT_ADDR_DATA_INPUT, buf, len);
        buf[len] = 0;
    }
}

/* callback for "set config"
 * on every "set config", this callback will register a "control" callback */
static void cdcacm_set_config(usbd_device *usbd_dev, uint16_t wValue) {
    (void) wValue; /* avoid compiler warning */

    usbd_ep_setup(usbd_dev, ENDPOINT_ADDR_DATA_OUTPUT, USB_ENDPOINT_ATTR_BULK,
                  PACKET_SIZE_DATA, cdcacm_data_rx_cb);
    usbd_ep_setup(usbd_dev, ENDPOINT_ADDR_DATA_INPUT, USB_ENDPOINT_ATTR_BULK,
                  PACKET_SIZE_DATA, NULL);
    usbd_ep_setup(usbd_dev, ENDPOINT_ADDR_COMM_INPUT,
                  USB_ENDPOINT_ATTR_INTERRUPT, PACKET_SIZE_COMM, NULL);

    usbd_register_control_callback(usbd_dev,
            USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
            USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
            cdcacm_control_request);
}

static void setup(void) {
    /* use external 8MHz oscillator to derive 48MHz clock from PLL
     * this is an oscillator, not a crystal, so disable the builtin oscillator
     * circuit (enable oscillator bypass) */
    rcc_osc_bypass_enable(RCC_HSE);
    rcc_clock_setup_in_hse_8mhz_out_48mhz();
    STK_CVR = 0; /* clear systick current value to start immediately */

    /* enable clocks for USB & LED pins
     * clocks for USB peripheral itself are enabled by the USB driver, later */
    rcc_periph_clock_enable(RCC_GPIOA);

    /* Pins for usb don't need to be setup because they are additional
     * functions, not alternate functions */

    /* set LED pins to output push-pull */
    gpio_mode_setup(PORT_LED, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED0 | PIN_LED1);
}

int main(void) {
    /* USB CDC demo:
     * receive ascii input from serial terminal
     * if input == "on", turn LED on and give feedback to user
     * if input == "off", turn LED off and give feedback to user
     * otherwise, give feedback to user ("invalid command")
     */

    usbd_device *usbd_dev;
    setup();
    usbd_dev = usbd_init(&st_usbfs_v2_usb_driver, &dev, &config, usb_strings, 3,
            usbd_control_buffer, sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(usbd_dev, cdcacm_set_config);

    gpio_clear(PORT_LED, PIN_LED0 | PIN_LED1);

    while (1) {
        usbd_poll(usbd_dev);
    }

    return 0;
}


