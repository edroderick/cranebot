# Robot Controller Sample
# Daniel M. Lofaro
# Georgemason University
# http://danlofaro.com
# Sample Python/Pygame Programs
# Simpson College Computer Science
# http://programarcadegames.com/
# http://simpson.edu/computer-science/
 
import pygame
import socket
import math

UDP_IP = "192.168.1.212"
#UDP_IP = "127.0.0.1"
UDP_PORT = 5006
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
 
# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
  
pygame.init()
 
# Loop until the user clicks the close button.
done = False
 
# Used to manage how fast the screen updates
clock = pygame.time.Clock()
 
# Current position
x_coord = 10
y_coord = 10

maxi = 32768.0
lastmessage = '0'
 
# Count the joysticks the computer has
joystick_count = pygame.joystick.get_count()
if joystick_count == 0:
    # No joysticks!
    print("Error, I didn't find any joysticks.")
else:
    # Use joystick #0 and initialize it
    my_joystick = pygame.joystick.Joystick(0)
    my_joystick.init()

while not done:
 
    # ALL EVENT PROCESSING SHOULD GO BELOW THIS COMMENT
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    # ALL EVENT PROCESSING SHOULD GO ABOVE THIS COMMENT
 
    # ALL GAME LOGIC SHOULD GO BELOW THIS COMMENT
 
    # As long as there is a joystick
    if joystick_count != 0:
 
        # This gets the position of the axis on the game controller
        # It returns a number between -1.0 and +1.0
        jl00 = my_joystick.get_axis(0)
        jl01 = my_joystick.get_axis(1)
        jl10 = my_joystick.get_axis(2)
        jl11 = my_joystick.get_axis(3)
        #for i in range(0,16):
         # my_joystick.get_button(i)


	if (jl01 < 0):
		MESSAGE = 'F' + str(abs(jl01))
	elif (jl01 > 0):
		MESSAGE = 'B'+ str(abs(jl01))
	elif (jl00 < 0):
		MESSAGE = 'L'+ str(abs(jl00))
	elif (jl00 > 0):
		MESSAGE = 'R'+ str(abs(jl00))
	elif (my_joystick.get_button(4) == 1):
		MESSAGE = 'O'+ '1'
	elif (my_joystick.get_button(6) == 1):
		MESSAGE = 'C'+ '1'
	else:
		MESSAGE = 'S' 
	
	if (lastmessage != MESSAGE):
		sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

	lastmessage = MESSAGE

    # ALL GAME LOGIC SHOULD GO ABOVE THIS COMMENT
 
    clock.tick(60)
 
pygame.quit()
