#!/usr/bin/python 
import pexpect
import time
 
DEVICE = "80:EA:CA:70:A3:2B"

def hexStrToInt(hexstr):
    val = int(hexstr[0:2],16) + (int(hexstr[3:5],16)<<8) + (int(hexstr[6:8],16)<<16) + (int(hexstr[9:11],16)<<24)
    if ((val&0x80000000)==0x80000000): # treat signed 16bits
        val = -((val^0xffff)+1)
        return val

print("Multisensor Address:"),
print(DEVICE)
 
# Run gatttool interactively.
print("Run gatttool...")
child = pexpect.spawn("gatttool -I")
 
# Connect to the device.
print("Connecting to"),
print(DEVICE),
child.sendline("connect {0}".format(DEVICE))
child.expect("Connection successful", timeout=5)
print("(Connected)")


# Device Info
child.sendline("char-read-hnd 0x42")
child.expect("Characteristic value/descriptor: ", timeout=5)
child.expect("\r\n", timeout=5)
print("Device Info: "),
print(child.before),
 

# request configuration  
time.sleep(1)
child.sendline("char-write-req 0x0044 0A080306030600020A000100000005")
child.expect("Characteristic value was written successfully", timeout=5)
child.expect("\r\n", timeout=5)
print("Configuration Written: 0A080306030600020A000100000005"),

# request
time.sleep(1)
child.sendline("char-write-req 0x0044 01")
child.expect("\r\n", timeout=5)

# read status request
time.sleep(1)
child.sendline("char-read-hnd 0x0044")
child.expect("Characteristic value/descriptor: ", timeout=5)
child.expect("\r\n", timeout=5)
print("\r\nConfiguration: "),
print(child.before),


while True:	
    time.sleep(1)
    child.sendline("char-read-hnd 0x0049")
    child.expect("Characteristic value/descriptor: ", timeout=5)
    child.expect("\r\n", timeout=5)
    print("\r\nMultisensor: "),
    print(child.before),
    
    pressure = int(child.before[15:17], 16) + (int(child.before[18:20], 16) << 8) + (int(child.before[21:23], 16) << 16) + (int(child.before[24:26], 16) << 24)
    print("\r\nPressure: ")
    print(float(pressure) / 100)
    
    humidity = int(child.before[36:38], 16) + (int(child.before[39:41], 16) << 8) + (int(child.before[42:44], 16) << 16) + (int(child.before[45:47], 16) << 24)
    print("\r\nHumidity: ")
    print(float(humidity) / 1000)
    
    temperature = int(child.before[57:59], 16) + (int(child.before[60:62], 16) << 8) + (int(child.before[63:65], 16) << 16) + (int(child.before[66:68], 16) << 24)
    print("\r\nTemperature: ")
    print(float(temperature) / 100)
  

  
