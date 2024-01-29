import serial
import struct

# Set the serial port and baud rate according to your Arduino configuration
ser = serial.Serial('COM5', baudrate=9600)  # Change 'COMX' to your Arduino's port

# Define the number of data points in each array
data_points = 1000  # Change this according to the number of floats you are sending in each array
num_arrays = 20   # Change this to the number of arrays you'll be sending

for _ in range(num_arrays):
    # Read the bytes from the serial port
    data_bytes = ser.read(data_points * 4)  # Assuming each float is 4 bytes (32 bits)

    # Convert the bytes to a list of floats
    data_list = struct.unpack('!{}f'.format(data_points), data_bytes)

    # Print the received data for the current array
    print("Received data:", data_list)

# Close the serial port
ser.close()