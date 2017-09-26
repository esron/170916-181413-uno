#!/usr/bin/python
# -*- coding: utf-8 -*-

import serial

ser = serial.Serial('COM4', 115200)

while True:
    response = ser.readline()
    print "Getting: " + response
