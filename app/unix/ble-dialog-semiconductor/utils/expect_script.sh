#!/usr/bin/expect

#spawn ./interactive_program.sh
#expect -exact "[                 ][LE]>"
#send -- "connect 80:EA:CA:70:A3:2B\r"
#expect -exact "How many dogs you have?\r"
#send -- "2\r"
#expect -exact "How many cats you have?\r"
#send -- "2\r"
#expect eof

#spawn ./interactive_program.sh
spawn gatttool -I
send -- "connect 80:EA:CA:70:A3:2B\r"
sleep 2
send -- "char-write-req 0x0044 01\r"
sleep 2
send -- "char-read-hnd 49\r"
sleep 2 
send -- "disconnect\r"
sleep 2 
send -- "exit\r"

expect eof
