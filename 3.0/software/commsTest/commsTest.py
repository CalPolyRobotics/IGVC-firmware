#!/usr/bin/python

import serial
import time

packet = bytearray(['A','B',0,4,0,7, 3])

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0)

ser.write(packet)

#time.sleep(3)

#print ser.read(1024)

ser.close()


