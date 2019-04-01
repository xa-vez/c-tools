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

import pexpect
import time


def hexStrToInt(hexstr):
    val = int(hexstr[0:2],16) + (int(hexstr[3:5],16)<<8) + (int(hexstr[6:8],16)<<16) + (int(hexstr[9:11],16)<<24)
    if ((val&0x80000000)==0x80000000): # treat signed 16bits
        val = -((val^0xffff)+1)
        return val

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
        pass

    def connect(self):
        # Connect to device.
        self.child = pexpect.spawn("gatttool -I")
        self.child.sendline("connect {0}".format(self.address))
        self.child.expect("Connection successful", timeout=5)

        # Device Info
        self.child.sendline("char-read-hnd 0x42")
        self.child.expect("Characteristic value/descriptor: ", timeout=5)
        self.child.expect("\r\n", timeout=5)
        print("[BLE] Device Info: "+ self.child.before + "\n"),

    def configure(self):
        # request configuration  
        print("[BLE] Configuring: 0A080306030600020A000100000005\n"),
        time.sleep(1)
        self.child.sendline("char-write-req 0x0044 0A080306030600020A000100000005")
        self.child.expect("Characteristic value was written successfully", timeout=5)
        self.child.expect("\r\n", timeout=5)

        # save configuration into flash
        self.child.sendline("char-write-req 0x0044 04")
        self.child.expect("\r\n", timeout=5)

        self.child.sendline("char-write-req 0x0044 01")
        self.child.expect("\r\n", timeout=5)

        # read status request
        self.child.sendline("char-read-hnd 0x0044")
        self.child.expect("Characteristic value/descriptor: ", timeout=5)
        self.child.expect("\r\n", timeout=5)

    def read(self):
        time.sleep(1)

        print("[BLE] Reading Device...")
        self.child.sendline("char-read-hnd 0x0049")
        self.child.expect("Characteristic value/descriptor: ", timeout=5)
        self.child.expect("\r\n", timeout=5)
        print("[BLE] Multisensor: " + self.child.before + "\n"),

        file = open("/tmp/ble-dialog-semiconductor.txt","w")
        file.write(self.child.before) 
        file.close() 

        self.pressure = int(self.child.before[15:17], 16) + (int(self.child.before[18:20], 16) << 8) + (int(self.child.before[21:23], 16) << 16) + (int(self.child.before[24:26], 16) << 24)
        print("\r\nPressure: ")
        print(float(self.pressure) / 100)
        
        self.humidity = int(self.child.before[36:38], 16) + (int(self.child.before[39:41], 16) << 8) + (int(self.child.before[42:44], 16) << 16) + (int(self.child.before[45:47], 16) << 24)
        print("\r\nHumidity: ")
        print(float(self.humidity) / 1000)
        
        self.temperature = int(self.child.before[57:59], 16) + (int(self.child.before[60:62], 16) << 8) + (int(self.child.before[63:65], 16) << 16) + (int(self.child.before[66:68], 16) << 24)
        print("\r\nTemperature: ")
        print(float(self.temperature) / 100)

    def disconnect(self):
        self.child.sendline("exit")

###################################################################
###################################################################
###################################################################
if __name__ == '__main__':
    print("\n[BLE] Initializing BLE Application\n")
    ble_device = DialogSemiconductor("80:EA:CA:70:A3:2B")
    print("\n[BLE] Done\n")

