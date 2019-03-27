import serial
import sys
import subprocess
import os

ser = serial.Serial("/dev/ttyUSB0",baudrate=9600)
# while (True):
#     str_input = input()
#     ser.write(str_input.encode())
#     print(ser.read(len(str_input)).decode('utf-8',errors="ignore"))

file = open("capture.pcap","w+")

line = ser.readline()
while b'<<START>>' not in line:
    line = ser.readline()
    print(line)
    continue

print("[*] Starting wireshark")
cmd = "tail -f -c +0 capture.pcap | wireshark -k -i -"
p = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True, preexec_fn=os.setsid)

while True:
    ch=ser.read()
    file.write(ch)