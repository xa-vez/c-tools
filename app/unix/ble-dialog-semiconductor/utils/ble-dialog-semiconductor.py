#!/usr/bin/python 
#
# root@OpenWrt:~# btmgmt info
# Index list with 1 item
# hci0:   Primary controller
#         addr 6C:0B:84:27:28:F4 version 7 manufacturer 29 class 0x000000
#         supported settings: powered connectable fast-connectable discoverable bondable link-security ssp br/edr hs le advertising secure-conn debug-keys privacy static-addr 
#         current settings: powered bondable ssp br/edr le 
#         name 
#         short name 
#         
# root@OpenWrt:~# gatttool -I
# 
# [                 ][LE]> connect 80:EA:CA:70:A3:2B
# Attempting to connect to 80:EA:CA:70:A3:2B
# Connection successful
# 
# [80:EA:CA:70:A3:2B][LE]> char-write-req 0x0044 0A080306030600020A000100000005
# Characteristic value was written successfully
# 
# [80:EA:CA:70:A3:2B][LE]> char-write-req 0x0044 01
# Characteristic value was written successfully
# 
# [80:EA:CA:70:A3:2B][LE]> char-read-hnd 49
# Characteristic value/descriptor: a5 05 04 02 03 9b 88 01 00 05 02 03 4c 88 00 00 06 02 03 d8 09 00 00 

#
#http://www.bx.psu.edu/~nate/pexpect/pexpect.html
#

import pexpect
import time
from compiler.pycodegen import EXCEPT

logs_enabled = 1


def trace_log(msg):
    if (logs_enabled == 1):
        print(msg)

def hexStrToInt(hexstr):
    val = int(hexstr[0:2], 16) + (int(hexstr[3:5], 16) << 8) + (int(hexstr[6:8], 16) << 16) + (int(hexstr[9:11], 16) << 24)
    if ((val & 0x80000000) == 0x80000000):  # treat signed 16bits
        val = -((val ^ 0xffff) + 1)
        return val
       
# Dialog Semiconducto BLE interface
# 
#
class DialogSemiconductor(object):

    def __init__(self, address):
        self.address = address
        self.tempetature = 0
        self.pressure = 0
        self.humidity = 0
        self.child = 0
        self.connect()
        self.configure()
        self.read()
        self.disconnect()
        self.exit()
        pass

    def connect(self):
        
        try:
            # Connect to device.
            self.child = pexpect.spawn("gatttool -I")
            self.child.sendline("connect {0}".format(self.address))
            self.child.expect("Connection successful", timeout=5)
            time.sleep(1)
        
        except:
            return    
            
        try:    
            # Device Info
            self.child.sendline("char-read-hnd 0x42")
            self.child.expect("Characteristic value/descriptor: ", timeout=5)
            self.child.expect("\n", timeout=5)
            trace_log("[BLE] Device Info: " + self.child.before)
            time.sleep(1)

        except pexpect.EOF: 
            self.child.sendline("disconnect")
            trace_log("CONNECT EOF")
        except pexpec.TIMEOUT:
            self.child.sendline("disconnect")
            trace_log("CONNECT TIMEOUT")       

    def configure(self):

        try:
            # request configuration  
            trace_log("[BLE] Configuring: 0A 08 03 06 03 06 00 02 0A 00 01 00 00 00 05"),
            self.child.sendline("char-write-req 0x0044 0A080306030600020A000100000005")
            #self.child.expect("Characteristic value was written successfully", timeout=5)
            self.child.expect("> ", timeout=5)
    
            # save configuration into flash
            self.child.sendline("char-write-req 0x0044 04")
            self.child.expect("> ", timeout=5)
        
        except pexpect.EOF: 
            self.child.sendline("disconnect")
            trace_log("CONFIGURE EOF")
        except pexpec.TIMEOUT:
            self.child.sendline("disconnect")
            trace_log("CONFIGURE TIMEOUT")

    def read(self):
        try:
            trace_log("[BLE] Reading Device...")
        
            # enable readings
            self.child.sendline("char-write-req 0x0044 01")
            self.child.expect("> ", timeout=5)
            
            # read status request
            #self.child.sendline("char-read-hnd 0x0044")
            #self.child.expect("Characteristic value/descriptor: ", timeout=5)
            #self.child.expect("> ", timeout=5)
            #time.sleep(1)
            
            # send read command
            self.child.sendline("char-read-hnd 0x0049")
            self.child.expect("Characteristic value/descriptor: ", timeout=5)
            self.child.expect("\n", timeout=5)
            trace_log("[BLE] Multisensor: " + self.child.before),
        
        except pexpect.EOF: 
            self.child.sendline("disconnect")
            trace_log ("READ EOF")
            return
        except pexpect.TIMEOUT:
            self.child.sendline("disconnect")
            trace_log("READ TIMEOUT")  
            return 
            
        # store data into file
        file = open("/tmp/ble-dialog-semiconductor.txt", "w")
        file.write(self.child.before) 
        file.close() 

        # self.pressure = int(self.child.before[15:17], 16) + (int(self.child.before[18:20], 16) << 8) + (int(self.child.before[21:23], 16) << 16) + (int(self.child.before[24:26], 16) << 24)
        # print("\r\nPressure: ")
        # print(float(self.pressure) / 100)
        
        # self.humidity = int(self.child.before[36:38], 16) + (int(self.child.before[39:41], 16) << 8) + (int(self.child.before[42:44], 16) << 16) + (int(self.child.before[45:47], 16) << 24)
        # print("\r\nHumidity: ")
        # print(float(self.humidity) / 1000)
        
        # self.temperature = int(self.child.before[57:59], 16) + (int(self.child.before[60:62], 16) << 8) + (int(self.child.before[63:65], 16) << 16) + (int(self.child.before[66:68], 16) << 24)
        # print("\r\nTemperature: ")
        # print(float(self.temperature) / 100)

    def disconnect(self):
        try: 
            self.child.expect("> ", timeout=5)
            self.child.sendline("disconnect")
            time.sleep(1)
        except pexpect.EOF: 
            self.child.sendline("disconnect")
            trace_log ("DISCONNECT EOF")
        except pexpect.TIMEOUT:
            self.child.sendline("disconnect")
            trace_log("DISCONNECT TIMEOUT")   

    def exit(self):
        try: 
            self.child.expect("> ", timeout=5)
            self.child.sendline("exit")
            time.sleep(1)
        except pexpect.EOF: 
            self.child.sendline("disconnect")
            trace_log ("EXIT EOF")
        except pexpect.TIMEOUT:
            self.child.sendline("disconnect")
            trace_log("EXIT TIMEOUT")   


###################################################################
###################################################################
###################################################################
if __name__ == '__main__':
    trace_log("[BLE] Initializing BLE Application")
    ble_device = DialogSemiconductor("80:EA:CA:70:A3:2B")
    trace_log("[BLE] Done")

