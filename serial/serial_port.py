#!/usr/bin/env python

import time
import serial
import datetime

ser = serial.Serial(
        port='/dev/ttyS10', 
        baudrate = 115200, 
        parity=serial.PARITY_NONE, 
        stopbits=serial.STOPBITS_ONE, 
        bytesize=serial.EIGHTBITS, 
        timeout=1 )

print '[START ACTIVE]'+str(datetime.datetime.now())+'\r\n'
ser.write('AT+CWLAP\r\n')
while 1:
        #time.sleep(1)
        data=ser.readline()
        if (len(data)>0):
            print data
            if(data.find('OK') != -1 ):
                break

print '[END ACTIVE]'+str(datetime.datetime.now())
