import serial
import numpy as np

board = serial.Serial("COM3", 38400)
# This creates an object able to establish a serial communication channel
# with the board. The first parameter depends on your operating system
# and probably needs to be updated.
# The second is the baud rate. It needs to match the board's settings.

datapoints = 10000
array = np.empty((datapoints, 2))

index = 0
while index < (datapoints*2):
    line = board.readline()
    text = line.decode('utf-8')
    text = text.strip()
    data = float(text)
    print(str(((index * 100) / (datapoints * 2))) + "    " + str(data))
    array[index//2, index%2] = data
    index += 1

if index == (datapoints*2):
    np.save("software/imu_dump/A_1_66K", array)