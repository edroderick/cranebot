#!/usr/bin/env python


import sys
import time
import socket
import cv2.cv as cv
import cv2
import numpy as np
import pickle

#initialize UDP Socket
#IP = "192.168.1.245"	#static IP of raspberry pi
IP = "127.0.0.1"		#for testing purposes on same computer
PORT = 5010


send = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP to 2nd internal process  


cap = cv2.VideoCapture(0)


while True:
    ret, frame = cap.read()
    resized_img = cv2.resize(frame, (80, 60)) 
    cv2.imshow('small',resized_img)
    cv2.waitKey(10)
    #image2 = (resized_image.reshape(0,1))
    #print len(resized_image)
    #resized_img_str = resized_img.tostring()

    send.sendto(resized_img, (IP, PORT))

    time.sleep(.01)




