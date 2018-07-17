 #!/usr/bin/env python
          
import time
import serial
              
ser = serial.Serial(
      port='/dev/ttyAMA0', baudrate = 115200, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)              
while 1:
       	ser.write('AT+CWLAP\r\n')
       	time.sleep(5)
		x=ser.readall()
        print x
