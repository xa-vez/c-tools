#!/bin/bash


$(res) = ""
echo "initilizing ..."
gatttool -b 80:EA:CA:70:A3:2B --char-read --handle=0x0042; 
sleep 1;
gatttool -b 80:EA:CA:70:A3:2B --char-write-req --handle=0x0044 --value=0x0A080306030600020A000100000005;
sleep 1;
gatttool -b 80:EA:CA:70:A3:2B --char-write-req --handle=0x0044 --value=0x0100;
sleep 1; 
gatttool -b 80:EA:CA:70:A3:2B --char-read --handle=0x0046; 
sleep 1;
gatttool -b 80:EA:CA:70:A3:2B --char-read --handle=0x0049; 
echo $res
sleep 1;
echo "finished"

