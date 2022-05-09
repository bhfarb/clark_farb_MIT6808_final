"""Code from https://www.learnrobotics.org/blog/arduino-data-logger-csv/"""

import serial

arduino_port = "/dev/cu.usbmodem14201" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud
fileName="analog-data.csv" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")

samples = 500 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
while line <= samples:
    # incoming = ser.read(9999)
    # if len(incoming) > 0:
    if print_labels:
        if line==0:
            print("Printing Column Headers")
        else:
            print("Line " + str(line) + ": writing...")
    getData=str(ser.readline())
    data=getData[0:][:-2]
    data_to_add = ''.join(c for c in data if (c.isdigit() or c =='.'))
    print(data_to_add)

    file = open(fileName, "a")
    file.write(data_to_add + "\n") #write data with a newline
    line = line+1

print("Data collection complete!")
file.close()
