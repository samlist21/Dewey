# Dewey_GLCD.py
# Python module to interface with DX160 serial graphic LCD screen
# Fayetteville Free Library Robotics Club
# June 2016, Bob Lawler

# Additional modules
#from collections import namedtuple     # Named tuple objects
from enum import Enum                           # Enum module
from enum import IntEnum                        # Integer Enum module
from PIL import Image                           # Image processing module
from PIL import ImageOps                        # Image manipulation operations
import time                                                     # Used for sleep delay
import serial                                           # Used for communication over serial port
import Dewey_utils                                      # Custom utility module
import sys								# to test for non-blockign input 

ser = serial.Serial()
WriteToScreen = True   # False
# Define global serial object
TEXT = Enum('TEXT_SIZE','LARGE SMALL')          # Text size Enum
TEXT_SIZE = TEXT.LARGE                                          # Variable to hold text size (1 = large/default, 2 = small)
class COLOR(IntEnum):                                           # Enumerator for color values
        WHITE = int(0)
        BLACK = int(1)
        INVERT = int(2)
posX = 1                                                                        # Text x position
posY = 1                                                                        # Text y position

def init():             # Set-up GLCD functions
        returnValue = _initSerial()                                   # Initialize serial connection
        global TEXT_SIZE
        TEXT_SIZE = TEXT.LARGE          # Initialize to default text size (large)
        return returnValue 

def _initSerial():
        print("Opening GLCD serial connection...\r")
        # Set default comms parameters
        #ser = serial.Serial()
        ser.port = "/dev/ttyUSB0"                       # Linux
        #ser.port = "/dev/ttyUSB1"                       # Linux
        #ser.port = "/dev/ttyAMA0"                       # Linux
        #ser.port = "/dev/ttyS0"                       # Linux
        #ser.port = "COM12"                                      # Windows
        #ser.baudrate = 57600
        ser.baudrate = 57600
        ser.bytesize = serial.EIGHTBITS         # Set number of bits per byte
        ser.parity = serial.PARITY_NONE         # Set parity
        ser.stopbits = serial.STOPBITS_ONE      # Set stop bits
        ser.timeout = 0                                         # Read timeout value
                                                                                # None (block read), *1* (non-block read), 2 (timeout block read)
        ser.xonxoff = False                                     # Disable software flow control
        ser.rtscts = False                                      # Disable hardware (RTS/CTS) flow control
        ser.dsrdtr = False                                      # Disable hardware (DSR/DTR) flow control
        #ser.writeTimeout = 2                           # Timeout for write (default 2)
        #ser.write_timeout = 2                          # Write timeout value
        
        # Open port
        try:
                ser.open()
                print("GLCD Serial Port Open...\r")
                _writeToPort(bytes([191]))
                print("GLCD Serial Port set to 57600...\r")
                returnValue  = True
        except (KeyboardInterrupt, SystemExit):
                raise
        except Exception as e:
                print ("Error opening serial port: " + str(e)+"\r")
                #exit()
                returnValue = False
        return returnValue        

def stop():             # Stop GLCS functions
        print("Closing GLCD serial connection...\r")
        _closeSerial()
        
def _closeSerial():
        try:
                ser.close()             # Close serial connection
        except (KeyboardInterrupt, SystemExit):
                raise
        except Exception as e:
                print ("Error closing serial port: " + str(e))
                exit()
                
def _writeToPort(data, waitTime = 0.1):        # Write data (bytes) to serial port was 0.04
        if ser.isOpen():
                try:
                        byteCount = ser.write(data)
                        time.sleep(waitTime)            # Wait for serial port
                                                                                # 0.04s seems enough for text @ 57.6kbps
                                                                                # Longer waits may be required for graphics routines
                        WriteToScreen
#                        if (WriteToScreen):
								#x=1
 #                               print("Writing: " + str(data) + ", " + str(byteCount) +  " bytes")
                except (KeyboardInterrupt, SystemExit):
                        raise
                except Exception as e:
                        print("Comm error: " + str(e))
        else:
                print("Cannot open serial port")
                
def clearScreen():      # Clear screen and set row/column to 1
        global posX, posY
        posX = 1
        posY = 1
        _writeToPort(bytes([186]))

def toggleBacklight():  # Toggle backlight status
        _writeToPort(bytes([185]))
        
def toggleSplashScreen():       # Toggle splash screen at startup
        _writeToPort(bytes([187]))
        
def setRow(row):        # Set row position (text), column set to 1
        row = Dewey_utils.clamp(row,1,8)
        _writeToPort(bytes([row+126]))
        global posX, posY
        posX = 1
        posY = row
        
def setColumn(col):     # Set column position (text), row remains
        if (TEXT_SIZE == TEXT.LARGE):   # Large text
                col = Dewey_utils.clamp(col,1,21)
        elif (TEXT_SIZE == TEXT.SMALL): # Small text
                col = Dewey_utils.clamp(col,1,32)
        else:   # Error
                print("Text size invalid: " + str(TEXT_SIZE))
        
        _writeToPort(bytes([col+135]))
        global posX
        posX = col
                
def setPosition(col,row):       # Set text position
        setRow(row)
        setColumn(col)
        
def setLargeText():     # Set text size to large (1)
        global TEXT_SIZE
        TEXT_SIZE = TEXT.LARGE
        _writeToPort(bytes([180]), 0.5)

def setSmallText():     # Set text size to small (2)
        global TEXT_SIZE
        TEXT_SIZE = TEXT.SMALL
        _writeToPort(bytes([181]), 0.5)

def getMaxCharactersPerRow():   # Return maximum number of characters per row at current text size
        if (TEXT_SIZE == TEXT.LARGE):   # Large text
                return 21
        if (TEXT_SIZE == TEXT.SMALL):   # Small text
                return 32
        else:   # Error
                return -1
        
def writeString(s):     # Write string to LCD (80 character limit)
        if (TEXT_SIZE == TEXT.SMALL):   # Small text only supports uppercase characters
                s = s.upper()
                
        data = bytes([255])     # Termination byte
        data = bytes(s, 'utf-8') + data # Format data
        _writeToPort(data)
        
        # Handle cursor position update
        global posX, posY
        if (TEXT_SIZE == TEXT.LARGE):   # Large text
                lineWidth = 21  # Line limit of 21 characters
        if (TEXT_SIZE == TEXT.SMALL):   # Small text
                lineWidth = 32  # Line limit of 32 characters
        
        posY = min(8, posY + (posX+len(s))/lineWidth)   # Handle 8 row maximum
        posX = (posX + len(s)) % lineWidth      # Handle line wrapping
        
def drawFilledRect(x1, y1, x2, y2, color):      # Draw a filled rectangle
                                                                                        # color = 0/1/2 for white/black/invert
        # Constrain inputs
        x1 = Dewey_utils.clamp(x1,0,127)
        y1 = Dewey_utils.clamp(y1,0,63)
        x2 = Dewey_utils.clamp(x2,0,127)
        y2 = Dewey_utils.clamp(y2,0,63)
        color = Dewey_utils.clamp(color,0,2)
        
        data = bytes([200, 1, x1, y1, x2, y2, color, 200])
        _writeToPort(data)

def drawRect(x1, y1, x2, y2, color):    # Draw non-filled rectangle
                                                                                # color = 0/1/2 for white/black/invert
        # Constrain inputs
        x1 = Dewey_utils.clamp(x1,0,127)
        y1 = Dewey_utils.clamp(y1,0,63)
        x2 = Dewey_utils.clamp(x2,0,127)
        y2 = Dewey_utils.clamp(y2,0,63)
        color = Dewey_utils.clamp(color,0,2)
        
        data = bytes([200, 2, x1, y1, x2, y2, color, 200])
        _writeToPort(data)
        
def drawCircle(x, y, r, color): # Draw non-filled circle
                                                                # color = 0/1/2 for white/black/invert
        # Constrain inputs
        x = Dewey_utils.clamp(x,0,127)
        y = Dewey_utils.clamp(y,0,63)
        r = max(r,0)    # Prevent negative radii
        color = Dewey_utils.clamp(color,0,2)
        
        data = bytes([200, 3, x, y, r, color, 200])
        _writeToPort(data)
        
def drawLine(x1, y1, x2, y2, color):    # Draw line
                                                                                # color = 0/1/2 for white/black/invert
        # Constrain inputs
        x1 = Dewey_utils.clamp(x1,0,127)
        y1 = Dewey_utils.clamp(y1,0,63)
        x2 = Dewey_utils.clamp(x2,0,127)
        y2 = Dewey_utils.clamp(y2,0,63)
        color = Dewey_utils.clamp(color,0,2)
        
        data = bytes([200, 4, x1, y1, x2, y2, color, 200])
        _writeToPort(data)
        
def drawPixel(x, y, color):     # Draw pixel
                                                        # color = 0/1/2 for white/black/invert
        # Constrain inputs
        #x = Dewey_utils.clamp(x1,0,127)
        #y = Dewey_utils.clamp(y1,0,63)
        if (x<0 or x>127 or y<0 or y>63):
                return
        #color = Dewey_utils.clamp(color,0,2)
        
        data = bytes([200, 5, x, y, color, 200])
        _writeToPort(data,0)
        
def loadImage(filepath):        # Load an image from a file, return formatted Image object
        try:
                # Open with PIL and convert to 1 bit per byte (per pixel) color mode
                img = Image.open(filepath)
                bw_img = img.convert('1')
                
                # print(str(bw_img.tobytes()))  # Debug output
        except (KeyboardInterrupt, SystemExit):
                raise
        except Exception as e:
                print("Error loading image: " + str(e))
        
        #bw_img.save("Pillow_BW.png")   # Debug output
                
        return bw_img
        
def drawImage(x, y, img):       # Draw an image of any size to the display at (x,y)
                                                        # img must be formatted from loadImage()
        # Bounds checking (is there anything to display?)
        if (x > 127 or y > 63 or x+img.size[0] < 0 or y+img.size[1] < 0):
                return
        
        # Iterate through  pixels
        for i in range(img.size[0]):
                for j in range(img.size[1]):
                        pixVal = img.getpixel((i,j))
                        pixVal = 0 if pixVal>0 else 1   # Invert to standard coloring
                        drawPixel(x+i,y+j,pixVal)
        
        
def drawFullscreenImage(img):   # Draw a fullscreen image to the display (128x64)
                                                                # img must be formatted from loadImage()
        if (img.size[0] != 128 or img.size[1] != 64):   # Not a 128x64 image
                print("Incorrect image size passed to drawFullscreenImage()")
                print("\tExpected 128x64, Received " + str(img.size[0]) + "x" + str(img.size[1]))
                return
        
        rawData = img.tobytes()         # Test value
        if (len(rawData) != 1024):      # Data not in 1024 byte block
                print("Incorrect number of bytes passed to drawFullscreenImage()")
                print("\tExpected 1024 bytes, Received " + str(len(rawData)) + " bytes")
                return
        
        data = bytearray(1024)  # Storage for output data (sized to 1024 bytes)
        for row in range(8):    # Index through 8 rows of display
                for srcX in range(128): # Index horizontally across display
                        for i in range(8):              # Index through each set of 8 bits (vertically)
                                srcY = (row*8) + i      # Set source y-value for source image data
                                byteIndex = (row*128) + srcX    # Set bytearray index (so we work on one byte at a time)
                                
                                pixVal = img.getpixel((srcX,srcY))      # Get pixel data at source location
                                pixVal = Dewey_utils.clamp(pixVal,0,1)  # Pixel data must be 1 or 0
                                pixVal = 0 if pixVal>0 else 1   # Invert to standard coloring
                                
                                # Binary OR to set appropriate pixel value in data
                                data[byteIndex] = (pixVal << i) | data[byteIndex]
                                
        
        _writeToPort(bytes([200, 6, 200]))      # Command to begin processing image data
        _writeToPort(data, 0.250)                       # Data to display (50-200ms required processing time)
