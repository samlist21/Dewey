# Need to run the program with python (2)
# from the dewey directory run command 
#   sudo python/sendSerialDewey.py

# must have serial to use serial functions
# use sudo apt-get install pyserial

# Other funcitons that need tobe installed to use this code.
# use sudo apt-get install <none specified yet>
# sudo apt-get install python-picamera   OR
# sudo apt-get install python3-picamera




import time
import serial
import record
#import pygame, sys
# import pygame.locals()
#import curses

import tty
import sys
import termios
import select

import os
import picamera



orig_settings = termios.tcgetattr(sys.stdin)

tty.setraw(sys.stdin)


# must have aplay and/ or mpg123 to use sound functions
# use sudo apt-get install asla-utils   OR
# use sudo apt-get install mpg123 



# setup pygame to use key press
#pygame.init()
#BLACK = (0,0,0)
#WIDTH = 1280
#HEIGHT = 1024
#windowSurface = pygame.display.set_mode((100, 50), 0,32)
#windowSurface.fill(BLACK)

# this window must have the focus

# set up curses
#stdscr = curses.initscr()

#curses.cbreak()

# Setup Camera Stuff
camera = picamera.PiCamera()
os.chdir("/home/pi")
camera.hflip=True
camera.vflip=True
camera.stop_preview()


print("Starting Dewey Program ")


# get on with Dewey code

i=0
x='a'

#try:
ser = serial.Serial('/dev/ttyACM0',115200)


deweyRecord = record.record()

#except Exception, e:
#    print "error open serail port: "+ str(e)
#    exit()

def playback ():
    for step in runList:
        print (step)
        print(step['command'] +" will run for "+ str(step['time']) + " seconds\r")
        # convert string to byte and write out
        ser.write(step['command'].encode('utf-8'))
        print("Wrote out a "  + step['command'])

        time.sleep(step['time'])
    print("-- Done running Playback -- \r")


def printHelpMenu ():
	print('Enter your commands below.\r')
	print('Available Commands:(uppercase preferred but not necessary)\r')
	print('F = Forward\r')
	print('B = Backward\r')
	print('R = Turn Right\r')
	print('L = Turn Left\r')
	print('S or 0 = Stop\r')
	print('Available Speeds 1, 2, 3, 4...9\r')
	print('V = Start Recording steps\r')
	print('Q = Stop Recording steps\r')
	print('D = Playback Recorded steps\r')
	print('E = Playback Recorded steps from a file\r')
	print('P = Take a picture\r')
	print('H = Print Help Menu\r')
	print('T = Print Talk - Play Sound\r')
	print('I = Run GLCD program - Currently needs Python3\r')
	print('\r')
	print('Press ESC, "x", or "X" to Exit (leave application) and STOP Dewey.\r')

def playSound( sound):
	if (sound == 1 ):
		print("Playing Sound - /usr/share/sounds/asla/Front_Center.wav")
		os.system("aplay /home/pi/dewey/sounds/Front_Center.wav &")
		
	if (sound == 2 ):
		print("Playing Sound -  /home/pi/dewey/sounds/bizarre-guitar-daniel_simon.mp3")
		os.system("mpg123 /home/pi/dewey/sounds/bizarre-guitar-daniel_simon.mp3 &")
	
	
def runGLCD():
	print("Would be sending GLCD commands here if it worked")

def takePicture():
    takePicture.counter += 1
    counter = takePicture.counter
    camera.start_preview()
    time.sleep(5)
    camera.capture("/home/pi/Pictures/image"+str(counter)+".jpg")
    camera.stop_preview()
    print("Photo taken /home/pi/Pictures/image"+str(counter)+".jpg")

# static attributes must be initalized
takePicture.counter = 0 

# start of Dewey Program	
ser.isOpen()
print("First Action - Stopping Dewey\r")
ser.write('S'.encode('utf-8'))
print(' ')
# clear serial buffer so no bad characters come out and crash the program.
# Should see hello from Pi

# probably nothing to read now if not the first time since Arduino is fixed
#print("First read from Pi")
#a= ser.read(44)
# if this is the first time
#Should read back "Dewey is Alive and Ready to take commands"
#if everything is okay
# print(a)

printHelpMenu()




inputVal = "a"
inputValUpper = 'A'
while 1:

    #else:

    out = ''
    #let's wait one second before reading output
    #(give device time to read and respond.
    time.sleep(0.25)
    while ser.inWaiting()>0:

        a = ser.read(1)
        # first time Dewey sends an 0x87 ot sure why.
        if a < b'\x7F':
            # need to strip this off
                        #read and convert bytes to string

            out += a.decode('utf-8')
        else:
            print ("Bad Character="),
            print (a)


    if out != '':
        print("< " +out),
#    else:
#        print('.'),

    #get keyboard input
    #inputVal = input(">> ")
    # now using pygame
#    for event in pygame.event.get():
#        if (event.type == pygame.KEYDOWN):
#            inputVal = char(event.key)
#            inputVal1 = event.key
#            print(inputVal1),
#            inputVal = str(unichr(inputVal1))
#            print(inputVal),
#            inputValUpper = inputVal.upper()
#            print(inputValUpper)

    if select.select([sys.stdin,],[],[],0.0)[0]:
#        print("have Data")

        x=sys.stdin.read(1)[0]
#        print("you pressed ",x),
#        print(" ESC will exit")

    #    c= stdscr.getch()
    #    stdscr.clear()
    #    stdscr.addstr("Key Detected")
    #    stdscr.addstr(str(c))
        inputVal = x.encode('utf-8')
#        print(inputVal),
    #    inputVal1 = int(inputVal)
    #    print(inputVal1),
#        inputValUpper = inputVal.upper()
#        print(inputValUpper)


    # .encode('utf-8')
    #    presssed = pygame.key.get_pressed()
    #    if pressed[pygame.K_x]:
    #        inputVal = 'x'
    #        print (pressed.name())
    #    if pressed[pygame.K_f]:
    #        inputVal = 'f'
    #        print (pressed.name())

        inputValUpper = inputVal.upper()
        print('Received inputVal='+ str(inputVal) + ",Sending=" + str(inputValUpper)+ " \r")

            # send character to the serial device
            #note that I could append a \n\r carriage return and linefeed characters
            # to the end of the sent charaterto the device
            # ser.write(input + '\r\n')
     #       if inputVal == 'V':
     #           print ("In here with a V but should not be")

        # convert string to byte and write out
        #ser.write(inputValUpper.encode('utf-8'))
        ser.write(inputValUpper.encode('utf-8'))
        # Print to screen to verify what was sent and that it was an Upper
        #print("Wrote out a "  + inputValUpper)
        deweyRecord.command_store(inputValUpper)

#        print("Early inputValUpper is in "),
#        print(inputValUpper in ['X','V','Q','D','E'] )


    # Python 2 users
    #input = raw_input(">> ")

    #            print("inputValUpper is in "),
    #            print(inputValUpper in ['X','V','Q','D','E'] )

    if inputValUpper in ['X','V','Q','D','E','H','P', 'T', 'I'] or inputVal == chr(27):
#        print("Late inputValUpper is="),
#        print(inputValUpper)

        if inputValUpper =='X' or inputVal == chr(27):
            
#        print("you pressed ESC will exit",x)
#        break:
            # could send an X to Arduino but it would kill any restart
            # So now just sending an 'S'
            ser.write('S'.encode('utf-8'))
            # if recording was not stopped end recording.
            print("Dewey Record Ending - if it was going\r")
            deweyRecord.rec_stop()
            print("Stopping Dewey\r")
            ser.close()
            camera.close()
            #print("Pygame Display closed")
            #pygame.display.quit()
            #print("Pygame closed")
            #pygame.quit()
#            curses.nocbreak()
#            curses.endwin()
            termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)
            print("Stdin closed\r")



            print("Port and program closed")
            # Exit if desired
            break
            #exit()
            #sys.exit()

        if inputValUpper == 'V':
            # V Means start recording
            print("Dewey Record Beginning.....")
            termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)
            deweyRecord.rec_start()
            tty.setraw(sys.stdin)

        if inputValUpper == 'H':
            printHelpMenu()

        if inputValUpper == 'T':
            playSound(1)

        if inputValUpper == 'I':
            runGLCD()

        if inputValUpper == 'P':
            takePicture()

        if inputValUpper == 'Q':
            # Q Means stop recording

            # Stop the recording
            print("....Dewey Record Ending")
            deweyRecord.rec_stop()


            # Print out the list so we can verify it - if desired
            deweyRecord.rec_print()

        if inputValUpper =='D':
        # D Means Do Playback
            print("Dewey Record Playback")
            # Next  Line prints the list - if desired
            #deweyRecord.rec_print()

            #Next Line shows file - if desired
            #deweyRecord.playback()  # this runs without moving

            # Playback from the current list - Retrieve list
            termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)
            runList = deweyRecord.playback_list()
            tty.setraw(sys.stdin)
            print("-- Running Playback -- ")
            playback()

        if inputValUpper =='E':
        # E Means Do Playback from a file
            print("Dewey File Record Playback")
            termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)
            runList = deweyRecord.playback_file()
            tty.setraw(sys.stdin)
            print("-- Running Playback from File -- ")
            playback()
    inputVal = "a"
    inputValUpper = 'A'

termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)
#curses.nocbreak()
#curses.endwin()

 #       else:
 #           inputValUpper = 'a'
 #           print('Not Sent')










