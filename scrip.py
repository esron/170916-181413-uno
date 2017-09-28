#!/usr/bin/python
# -*- coding: utf8 -*-
"""
    This scrip promps for two values via serial portt hen sends to a webserver
    via a API RESTful. The port, baudhate and motor id are givem by the
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
parser.add_argument('baud', help='Baudhate in the serial port to communicate.')

args = parser.parse_args()

ser = serial.Serial(args.port, args.baud) # Serial port configuration

conn = httplib.HTTPConnection(ServerUrl) # Server connection

headers = {
    'content-type': "application/x-www-form-urlencoded",
    'cache-control': "no-cache",
    }

params = urllib.urlencode({
    'motor_number': args.motor,
    'rpm_indutivo': '1',
    'rpm_optico': '1',
    'voltage': '0'
    })

while True:
    sensor = ser.readline().rstrip()
    value  = ser.readline().rstrip()
    print "Received. sensor: ", sensor, ", value = ", value

    inductiveRPM = (value) / (12 * 60)

    sensor = ser.readline().rstrip()
    value  = ser.readline().rstrip()
    print "Received. sensor: ", sensor, ", value = ", value

    opticRPM = (value) / (12 * 60)

    # conn.request("POST", POSTUrl, params, headers)
    # results = conn.getresponse()
    # print "Request status: ", results.status, results.reason
    # conn.close()
    #
    # while int(results.status) != 200:
    #     conn.request("POST", POSTUrl, params, headers)
    #     results = conn.getresponse()
    #     print "Request status: ", results.status, results.reason
    #     conn.close()
