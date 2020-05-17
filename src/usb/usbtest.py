#! /usr/bin/env python

import usb.core
import time

if __name__ == "__main__":
    dev = usb.core.find(idVendor=0xcafe, idProduct=0xcafe)
    if dev is None:
        raise ValueError('Device not found')

    dev.set_configuration()

    while True:
        print("turning on LED")
        dev.ctrl_transfer(0x40, 0, 1, 0, 'Hello World!')
        time.sleep(0.5)
        print("turning off LED")
        dev.ctrl_transfer(0x40, 0, 0, 0, 'Goodnight World!')
        time.sleep(0.5)
