import serial

ser = serial.Serial("/dev/ttyUSB0",baudrate=9600)
while (True):
    str_input = input()
    ser.write(str_input.encode())
    print(ser.read(len(str_input)).decode('utf-8',errors="ignore"))