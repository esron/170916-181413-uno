#!/usr/bin/python
# -*- coding: utf8 -*-
"""
    This scrip promps for two values via serial portt hen sends to a webserver
    via a API RESTful. The port, baudrate and motor id are givem by the
    user via comand line
"""
# Serial port communication library
import serial

# HTTP libraries
import httplib
import urllib

# Comand line argument parser
import argparse

# Constants
ServerUrl     = "rpmreadapi.herokuapp.com"
POSTUrl       = "/reads"
pulsesPerTurn = 4

# Arguments configuration
parser = argparse.ArgumentParser()
parser.add_argument('port', help='The serial port to communicate.')
parser.add_argument('motor', help='The motor\'s that is in test.' )
parser.add_argument('baud', help='Baudrate in the serial port to communicate.')
parser.add_argument('voltage', help='Voltage in the motor')

args = parser.parse_args()

ser = serial.Serial(args.port, args.baud) # Serial port configuration

conn = httplib.HTTPConnection(ServerUrl) # Server connection

headers = {
    'content-type': "application/x-www-form-urlencoded",
    'cache-control': "no-cache",
    }


while True:
    sensor = ser.readline().rstrip()
    value  = ser.readline().rstrip()
    inductiveRPM = 3 * int(value)

    print "Received. sensor: ", sensor, ", value = ", value, ", RPM = ", str(inductiveRPM)

    sensor = ser.readline().rstrip()
    value  = ser.readline().rstrip()
    opticRPM = 3 * int(value)

    print "Received. sensor: ", sensor, ", value = ", value, ", RPM = ", str(opticRPM)

    params = urllib.urlencode({
        'motor_number': args.motor,
        'rpm_indutivo': str(inductiveRPM),
        'rpm_optico': str(opticRPM),
        'voltage': args.voltage
        })

    if (inductiveRPM != 0) and (opticRPM != 0) :
        conn.request("POST", POSTUrl, params, headers)
        results = conn.getresponse()
        print "Request status: ", results.status, results.reason
        conn.close()
