import socket
import time
import serial
import sys
import time
import cv2.cv as cv
import cv2
import numpy as np


#UDP_IP_IN = "192.168.1.245"
IP = "127.0.0.1"
PORT = 5010

receive = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP from process over lan
receive.bind((IP, PORT))


while True:
	data,addr = receive.recvfrom(4096)
	L = pickle.loads(data)
	L = frame

	cv2.imshow('received',frame)
	time.sleep(.1)
