#! /usr/bin/env python

# This file adapted from libopencm3 project
# original author:
# Copyright (C) 2011 Piotr Esden-Tempski <piotr@esden.net>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.
#

import serial
import time

with serial.Serial("/dev/ttyACM0", timeout=0.01) as ser:
    print("connected to device: {}".format(ser.name))
    s = b'abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()[]{};:\'"/?,<.>'
    errorcount = 0
    while True:
        sent = ser.write(s)
        rec = ser.read(1024)
        if rec != s:
            errorcount += 1
            print("error: received {}".format(rec))
            print("{} errors so far".format(errorcount))
        time.sleep(0.01)
