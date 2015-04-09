import socket
import time
import serial
import sys
import time
import cv2.cv as cv
import cv2
import numpy as np
import pickle

#UDP_IP_IN = "192.168.1.245"
IP = "127.0.0.1"
PORT = 5010

receive = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP from process over lan
receive.bind((IP, PORT))


while True:
	data,addr = receive.recvfrom(10000000)
	print 'got past read'
	#L = pickle.loads(data)
	frame = np.fromstring(data, dtype=np.uint8)
	frame2 = np.reshape(frame, (80,60,3))
	frame3 = cv2.resize(frame2,(320,640))
	cv2.imshow('received',frame3)
	time.sleep(.01)
