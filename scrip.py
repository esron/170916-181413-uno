#!/usr/bin/python
# -*- coding: utf8 -*-

# Libraries for http and serial handling
import serial
import httplib
import urllib

# Constants
ServerUrl = "rpmreadapi.herokuapp.com"
POSTUrl    = "/reads"

ser = serial.Serial('COM9', 115200) # Serial port configuration

conn = httplib.HTTPConnection(ServerUrl) # Server connection

headers = {
    'content-type': "application/x-www-form-urlencoded",
    'cache-control': "no-cache",
    }

params = urllib.urlencode({'motor_number': '1', 'rpm_indutivo': '1', 'rpm_optico': '1'})

while True:
    atmegaResponse = ser.readline()
    conn.request("POST", POSTUrl, params, headers)
    results = conn.getresponse()
    print "Request status: ", results.status, results.reason
    conn.close()

    while int(results.status) != 200:
        conn.request("POST", POSTUrl, params, headers)
        results = conn.getresponse()
        print "Request status: ", results.status, results.reason
        conn.close()
