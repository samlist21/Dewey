# Dewey_Operation.py
# Console interface to control/monitor Dewey
# Fayetteville Free Library Robotics Club
# July 2017, Ken Samuelson 

# Need to run the program with python, Currently uses python3 
# but also seems to work with python (2) with the exception of GLCD which uses enum not support by python (2)
# from the dewey directory run command 
#   sudo python3 python/sendSerialDewey.py
# You may use python (2) but won't have the GLCD functions

# Must have serial to use serial functions
# use sudo apt-get install pyserial

# Other functions that need to be installed to use this code.
# Will keep adding here as they get discovered or included.
# use sudo apt-get install <specified file/ function>
# sudo apt-get install python-picamera   OR
# sudo apt-get install python3-picamera

# must have aplay and/ or mpg123 to use sound functions
# use sudo apt-get install asla-utils   OR
# use sudo apt-get install mpg123 
# use sudo apt-get install omxplayer


import time
import serial
import record
import tty
import sys
import termios
import select
import os
import picamera

# add path to GLCD files - needed since it is not in this directory
# this is the way to use .py code in other directories.
sys.path.insert(0,'python/GLCD/')

# Save directories so that they can change globally
picturesDir = "/home/pi/Pictures/"
soundsDir = "/home/pi/dewey1/sounds/"
GLCD_Dir = "/home/pi/dewey1/python/GLCD/"

# find version number
version = sys.version_info[0]
print("Running from python version " + str(version) +" ...\r")

setGLCD = False   # start with false and see if can be changed to true
if version > 2:
    # includes for GLCD
    from PIL import Image                           # Image processing module
    import random                                   # Random number generation
    import Dewey_GLCD as lcd                        # GLCD control module
    setGLCD = True
    

# ALL def functions up here
#  Playback Function for recorded track data
def playback ():
    for step in runList:
        print (step)
        print(step['command'] +" will run for "+ str(step['time']) + " seconds\r")
        # convert string to byte and write out
        ser.write(step['command'].encode(encoding='utf-8'))
        print("Wrote out a "  + step['command'])

        time.sleep(step['time'])
    print("-- Done running Playback -- \r")

#Ability to Print the Help Menu at any time by pressing H
def printHelpMenu ():
    print('Enter your commands below.\r')
    print('Available Commands:(uppercase preferred but not necessary)\r')
    print('No need to hit enter - Just the key\r')
    print('A = Autonomous\r')
    print('F = Forward\r')
    print('B = Backward\r')
    print('R = Turn Right\r')
    print('L = Turn Left\r')
    print('N = Turn Left 90 degrees')
    print('M = Turn Right 90 degrees')   
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
    print('\r')
    print('If the Terminal program does not work after running this code,\r')
    print('Try the reset command in the Terminal Window\r')

# Play Sound Function  Called when user hits T
def playSound( sound):
    global soundCode
    if (soundCode == 1 ):
        #print("Playing Sound - ront_Center.wav\r")
        #os.system("aplay soundsDir + "Front_Center.wav &")
        print("Playing Sound -  HelpImStuck.mp3\r")
        #os.system("mpg123 -q /home/pi/dewey/sounds/HelpImStuck.mp3 &")
        os.system("omxplayer -o local " + soundsDir + "HelpImStuck.mp3  > /dev/null &")
        soundCode = 2

       
    elif (soundCode == 2 ):
        print("Playing Sound - WhatsYourName1.mp3\r")
        #os.system("mpg123 -q /home/pi/dewey1/sounds/WhatsYourName1.mp3 &")
        os.system("omxplayer -o local " + soundsDir + "WhatsYourName1.mp3>/dev/null &")
        soundCode = 3

    elif (soundCode == 3 ):
        print("Playing Sound - YourPretty.mp3\r")
        #os.system("mpg123 -q /home/pi/dewey/sounds/YourPretty.mp3 &")
        os.system("omxplayer -o local " + soundsDir + "YourPretty.mp3 > /dev/null &")

        soundCode = 4

    elif (soundCode == 4 ):
        print("Playing Sound - bizarre-guitar-daniel_simon.mp3\r")
        #os.system("mpg123 -q /home/pi/dewey/sounds/bizarre-guitar-daniel_simon.mp3 &")
        os.system("omxplayer -o local " + soundsDir + "bizarre-guitar-daniel_simon.mp3  > /dev/null &")

        soundCode = 1

def randomCirclesTextGLCD():
    lcd.clearScreen()
    img_sm = loadFFLImage(GLCD_Dir + "ffl_logomultismall_BW_64x27.png")
    # Clear display
    if (lcd.TEXT_SIZE == lcd.TEXT.LARGE): # Position range for large text
            lcd.setPosition(random.randint(1,22-len(s)), random.randint(1,8))       # Set random position
    else:   # Position range for small text
            lcd.setPosition(random.randint(1,33-len(s)), random.randint(1,8))       # Set random position
    lcd.writeString(s)      # Write text
    print("Sending circles to Display..... \r")       
    # Draw random circles
    lcd.drawCircle(random.randint(0,127), random.randint(0,63), random.randint(2,20), lcd.COLOR.BLACK)
    lcd.drawCircle(random.randint(0,127), random.randint(0,63), random.randint(2,20), lcd.COLOR.BLACK)
    print("Sending small icon to Display....\r")     
    # Draw small icon
    lcd.drawImage(random.randint(0,127-img_sm.size[0]), random.randint(0,63-img_sm.size[1]), img_sm)

    
# GLCD Function  Called when user hits I
# Used to show stuff on the GLCD display.
def runGLCD():
    global setGLCD
    if setGLCD:
        #print("Sending set of GLCD commands\r")
        global GLCDcode
        if (GLCDcode == 1 ):
            print("Showing GLCD 1 - FFL Logo\r")
            setFFLLogoGLCD()
            GLCDcode = 2
            
        elif (GLCDcode == 2 ):
            print("Showing GLCD 2 - Circles, small FFL Logo, and text \r")
            randomCirclesTextGLCD()
            GLCDcode = 1
        
    else:
        print("GLCD can not be run.  No Serial port. \r")

# Funciton to find highest image number
def findLastImageNumber():
# does not handle if low numbers and high number images are in the directory. Will pick highest.
# possibly a better was is to check date first. then latest date and begin after that number
    maxNumber = 0
    intNumber = 0
    for filename in os.listdir(picturesDir):
        #print("Found Filename="+filename+"\r")
        if filename.endswith(".jpg") and filename[:2]=="im":
            #print("Acting on Filename="+filename+"\r")
            #print('Found File='+filename)
            number = os.path.splitext(filename)[0]
            intNumber = int(number[5:])
            #print('Found Number='+ number[5:]+"\r")
            
            #print('Found int Number='+ str(intNumber)+"\r")
            if intNumber > maxNumber:
                #print("Previous Max Number was"+ str(maxNumber))
                maxNumber = intNumber
    print("Last Image Number in Pictures Directory was:"+ str(maxNumber) +"\r")
    return maxNumber  

# Photo Function  Called when user hits P
# Currently takes 640x480.  Not sure why but okay to be small.
# Increments image numbers and over writes any images after a 254 rollover 
# imagexxx.jpg is the result
# with the same number in the Pictures directory 
def takePicture():
    takePicture.counter += 1  #increment prior to taking the picture
    if takePicture.counter > 254:  #handle image rollover
        takePicture.counter = 1  # restart image counter if greater than 254
        # this will begin to overwrite the previous files and begin at 1
        #on next start unless images are removed.
    counter = takePicture.counter
    # if filename (lenght or identification) is changed make sure to change findLastImageNumber function too 
    print("Taking Photo "+ picturesDir + "image" + str("{0:03}".format(counter))+".jpg\r")
    #camera.start_preview()
    #time.sleep(5)
    camera.capture(picturesDir + "image" + str("{0:03}".format(counter))+".jpg")
    #camera.stop_preview()
    print("Photo complete\r")


def loadFFLImage(imageFile):
    # Load Data
    try:
            image = lcd.loadImage(imageFile)      # Load splash screen image
            # Seems to need absolute path to work. 
    except Exception as e:
            print("Resource loading exception: " + str(e) +"\r")
    return image        

def setFFLLogoGLCD():
    # Send FFl Logo to GLCD display

    print("Sending image to Display..... \r") 
    lcd.drawFullscreenImage(loadFFLImage(GLCD_Dir + "ffl_logomultismall_BW_128x64.png"))

    # Set write position and write initial text 
    lcd.setPosition(int((lcd.getMaxCharactersPerRow() - len(s)) / 2) + 1, 8)        # Center text on bottom row
    lcd.writeString(s)      # Write text
    # end GLCD first image

def setLastImageGLCD():
    if setGLCD:
        # Send last picture taken to GLCD display

        print("Sending picture image to Display..... \r")
        print(picturesDir +"image"+ str("{0:03}".format(takePicture.counter))+".jpg") 
        lcd.drawFullscreenImage(loadFFLImage(picturesDir +"image"+ str("{0:03}".format(takePicture.counter))+".jpg"))

        # Set write position and write initial text
        # coudl put persons name here
        #lcd.setPosition(int((lcd.getMaxCharactersPerRow() - len(s)) / 2) + 1, 8)        # Center text on bottom row
        #lcd.writeString(s)      # Write text
        # end GLCD last image


# Dewey Setup Code
#Setup System to read keys
orig_settings = termios.tcgetattr(sys.stdin)

tty.setraw(sys.stdin)

# make sure this is in the Pi Directory so the files can be accessed
os.chdir("/home/pi")

# Setup Camera Stuff
camera = picamera.PiCamera()

camera.hflip=True
camera.vflip=True
# remove this comment to take pitures and send to the screen
#camera.resolution = (128,64)

# Also uncomment line 457 - works but poor resolution. 

# attempt to turn off the camera until needed.
# Does not seem to work at this time.  Camera light stays on.
camera.stop_preview()

i=0
x='z'

# sound and GLCD toggle values 
soundCode =1
GLCDcode =1

print("Starting Dewey Program\r")

#os.system("mpg123 -q /home/pi/dewey/sounds/HelloNameIsDeweyLoud.mp3")
os.system("omxplayer -o local "+ soundsDir +"HelloNameIsDeweyLoud.mp3 >/dev/null")

# get on with Dewey code

# try to find and use serial port for Arduino.  
#If not there quit since need serial to move. 
try:
    ser = serial.Serial('/dev/ttyACM0',115200)
    print("Done opening Serial to Arduino\r")

except:
    e = sys.exc_info()[0]  # anohter way to get the exception
    print ("Error opening serial port to Arduino, Error: "+ str(e) + "\r")
    print ("Sorry, Can't use Dewey without Serial port to Arduino \r")
    exit(0)


# Setup GLCD serial port and clear screen

if setGLCD:
    setGLCD = lcd.init()
    # get second chance to see if GLCD can be initialized
    if setGLCD:
        print("LCD Initialized...\r")
        quit = False
        WriteToScreen = False
        WriteToScreen = True
        s = "FFL Robotics!"     # Set text
        lcd.setSmallText()     # Set small text size
        #lcd.setLargeText()      # Set large text size
        print("LCD Set...\r")
        lcd.clearScreen()
        print("LCD Cleared...\r")
        setFFLLogoGLCD()        # send first screen image 
else:
    # No serail port so nothing to send.
    print("No GLCD Serial port found GLCD may not be used...\r")

# Call the record function so that it is ready to record when called. 
deweyRecord = record.record()

# static attributes must be initalized
# attribute to hold the next picture number
takePicture.counter = findLastImageNumber() 

# start of Dewey Program    
ser.isOpen()
print("First Action - Stoping Dewey in case moving\r")
ser.write('S'.encode(encoding='utf-8'))
print(' \r')
# clear serial buffer so no bad characters come out and crash the program.
# Should see "Hello from Arduino, alive and well"

# probably nothing to read now if not the first time since Arduino is fixed
#print("First read from Pi")
bytesAtPort = ser.inWaiting()
if bytesAtPort >0:
    a= ser.read(bytesAtPort)
    # if this is the first time
    #Should read back "Dewey is Alive and Ready to take commands"
    #if everything is okay
    print(a)

printHelpMenu() # Print first help menu.

inputVal = b"z" # used to start Arduino in known state, byte "z" character.  
#Do not use A (anymore) since it is now autonomous mode. 
inputValUpper = b'Z'
while 1:

    out = ''  # clear the out buffer 
    #let's wait one quarter of a second between reading output
    #give device time to read and respond.
    time.sleep(0.25)
    while ser.inWaiting()>0:

        a = ser.read(1)
        # first time Dewey sends an 0x87 not sure why.
        # could be because of a leftover byte from the Arduino programming.
        if a < b'\x7F':
            # need to strip this off
            #read and convert bytes to string

            out += a.decode(encoding='utf-8')
        else:
            print ("Bad Character="),
            print (a)

# displays anything coming back from the Arduino serial port
    if out != '':
        print("< " +out +"\r"),


    #get keyboard input
    #inputVal = input(">> ")  # this is a blocking call which we do not want. 
    # We want to see and status coming back from the Arduino serial port

    if select.select([sys.stdin,],[],[],0.0)[0]:
        #print("have Data")

        x=sys.stdin.read(1)[0]
       #print("you pressed ",x),
       #print(" ESC will exit")

       #c= stdscr.getch()
       #stdscr.clear()
       #stdscr.addstr("Key Detected")
       #stdscr.addstr(str(c))

        inputVal = x
        # Tests to figure out what key and what kind of key we receive
        #print(inputVal)
        #inputVal1 = int(inputVal)
        #print(inputVal1),
        #inputValUpper = inputVal.upper()
        #print(inputValUpper)

        inputValUpper = inputVal.upper()
        print('Received inputVal='+ str(inputVal) + ",Sending=" + str(inputValUpper)+ " \r")

            # send character to the serial device
            #note that I could append a \n\r carriage return and linefeed characters
            # to the end of the sent charaterto the device
            # ser.write(input + '\r\n')
            #if inputVal == 'V':
                #print ("In here with a V but should not be")

        # convert string to byte and write out
        #ser.write(inputValUpper.encode('utf-8'))
        ## verison for python2
        ##ser.write(inputValUpper.encode('utf-8'))
        # update for python3
        ser.write(inputValUpper.encode(encoding='utf-8'))
        # Testing remove encode for python 3
        #ser.write(inputValUpper)
        # Print to screen to verify what was sent and that it was an Upper
        #print("Wrote out a "  + inputValUpper)
        deweyRecord.command_store(inputValUpper)

#        print("Early inputValUpper is in "),
#        print(inputValUpper in ['X','V','Q','D','E'] )


    # Python 2 users
    #input = raw_input(">> ")

    #            print("inputValUpper is in "),
    #            print(inputValUpper in ['X','V','Q','D','E'] )

    if inputValUpper in ['X','V','Q','D','E','H','P', 'T', 'I', 'F'] or inputVal == chr(27):
#        print("Late inputValUpper is="),
#        print(inputValUpper)

        if inputValUpper =='X' or inputVal == chr(27):
            
            #print("you pressed ESC will exit",x)  # ESC key works. No need to print

            # could send an X to Arduino but it would kill any restart
            # So now just sending an 'S'
            ser.write('S'.encode(encoding='utf-8'))
            # if recording was not stopped end recording.
            print("Dewey Record Ending - if it was going\r")
            deweyRecord.rec_stop()
            #os.system("mpg123 -q /home/pi/dewey1/sounds/DeweyTiredRestNow.mp3")
            os.system("omxplayer -o local "+ soundsDir + "DeweyTiredRestNow.mp3  > /dev/null &")

            print("Stopping Dewey\r")
            ser.close()
            camera.close()

            termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)
            print("Stdin closed\r")

            if setGLCD:
                print("GLCD Port closed")
                lcd.stop()
                
            print("Port and program closed")

            # Exit if desired
            #exit()
            #sys.exit()
            # don't exit because we need to run the termios command below or the one above. 
            break


        if inputValUpper == 'V':
            # V Means start recording
            print("Dewey Record Beginning.....\r")
            termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)
            deweyRecord.rec_start()
            tty.setraw(sys.stdin)

        if inputValUpper == 'H':
            printHelpMenu()

        if inputValUpper == 'F':
            #os.system("mpg123 -q /home/pi/dewey/sounds/WatchOut.mp3")
            os.system("omxplayer -o local " + soundsDir + "WatchOut.mp3  > /dev/null &")


        if inputValUpper == 'T':
            playSound(1)

        if inputValUpper == 'I':
            runGLCD()

        if inputValUpper == 'P':
            #os.system("mpg123 -q /home/pi/dewey/sounds/CanTakePicture.mp3")
            os.system("omxplayer -o local " + soundsDir + "CanTakePicture.mp3  > /dev/null ")

            #os.system("mpg123 -q /home/pi/dewey/sounds/SayCheese1.mp3")
            os.system("omxplayer -o local " + soundsDir + "SayCheese1.mp3  > /dev/null ")

            takePicture()
            #os.system("mpg123 -q /home/pi/dewey/sounds/ThankYou.mp3 &")
            os.system("omxplayer -o local " + soundsDir + "ThankYou.mp3  > /dev/null &")

            # setLastImageGLCD()
            

        if inputValUpper == 'Q':
            # Q Means stop recording

            # Stop the recording
            print("....Dewey Record Ending\r")
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
    inputVal = "z"
    inputValUpper = 'Z'

termios.tcsetattr(sys.stdin,termios.TCSADRAIN, orig_settings)











