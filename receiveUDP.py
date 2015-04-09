import socket
import time
import serial

#UDP_IP_IN = "192.168.1.245"
UDP_IP_IN = "127.0.0.1"
#UDP_IP_OUT = "192.168.1.245"
UDP_PORT_IN = 5005
#UDP_PORT_OUT = 5006

#ser = serial.Serial('/dev/ttyAMA0', 9600)	#RPI hardware serial
ser = serial.Serial('/dev/ttyACM0', 38400)	#USB

sock_in = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP from Control CPU
sock_in.bind((UDP_IP_IN, UDP_PORT_IN))

#leaving 1 bit space to add direction in future
maxspeed = 127 #0b1111111

while True:
	data, addr = sock_in.recvfrom(1024) # buffer size is 1024 bytes
	msg = 0

	if (data == "F"):
		msg = chr(70)
		#value = chr(maxspeed)
		#direction = 128 #0b10000000
	elif (data == "B"):
		msg = chr(66)
		#value = chr(maxspeed)
		#direction = 0 #0b0000000
	elif (data == "L"):
		msg = chr(76)
		#value = chr(maxspeed)
		#direction = 128 #0b10000000
	elif (data == "R"):
		msg = chr(82)
		#value = chr(maxspeed)
		#direction = 0 #0b0000000
	elif (data == "U"):
		msg = chr(85)
		#value = chr(maxspeed)
		#direction = 128 #0b10000000
	elif (data == "D"):
		msg = chr(68)
		#value = chr(maxspeed)
		#direction = 0 #0b0000000
	elif (data == "O"):
		msg = chr(79)
		#value = chr(stepsize)
	elif (data == "C"):
		msg = chr(67)
		#value = chr(stepsize)
	
	if (msg != 0):
		packet = msg #+ value
		print packet
		ser.write(packet)

	time.sleep(.01)
