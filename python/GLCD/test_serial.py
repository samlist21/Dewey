# test_serial.py
# Python module to test interface with DX160 serial graphic LCD screen
# Fayetteville Free Library Robotics Club
# June 2016, Bob Lawler

from PIL import Image                           # Image processing module
import random                                           # Random number generation
import time                                                     # Used for sleep delay

import Dewey_GLCD1 as lcd                        # GLCD control module

# if windows usee this
# not sure for other OSs
# if getch is use it can only be run from cammand line NOT IDLE
from msvcrt import getch

lcd.init()
quit = False
WriteToScreen = False
s = "FFL Robotics!"     # Set text
#lcd.setSmallText()     # Set small text size
lcd.setLargeText()      # Set large text size

lcd.clearScreen()

# Load Data
try:
        img_lg = lcd.loadImage("ffl_logomultismall_BW_128x64.png")      # Load splash screen image
        img_sm = lcd.loadImage("ffl_logomultismall_BW_64x27.png")       # Load small icon
except (KeyboardInterrupt, SystemExit):
        raise
except Exception as e:
        print("Resource loading exception: " + str(e))

print("Sending image to Display..... ESC or Ctrl-C for next ") 
lcd.drawFullscreenImage(img_lg)

lcd.setPosition(int((lcd.getMaxCharactersPerRow() - len(s)) / 2) + 1, 8)        # Center text on bottom row
lcd.writeString(s)      # Write text

# Wait loop
while not quit:
        try:
                time.sleep(0.250)
                # Wait 250ms
#                print(ord(getch()))
                key = ord(getch())
                
                if (key == 27):
                        print(key)
                        quit = True
                        
                        # break  # or possibly break
        except KeyboardInterrupt:
                quit = True
        except Exception as e:
                print("Wait loop exception: " + str(e))

key =0
quit = False            # Reset loop variable
lcd.setSmallText()      # Resize text

while not quit:
        try:
                
                lcd.clearScreen()       # Clear display
                if (lcd.TEXT_SIZE == lcd.TEXT.LARGE):   # Position range for large text
                        lcd.setPosition(random.randint(1,22-len(s)), random.randint(1,8))       # Set random position
                else:   # Position range for small text
                        lcd.setPosition(random.randint(1,33-len(s)), random.randint(1,8))       # Set random position
                lcd.writeString(s)      # Write text
                print("Sending circles to Display..... ")       
                # Draw random circles
                lcd.drawCircle(random.randint(0,127), random.randint(0,63), random.randint(2,20), lcd.COLOR.BLACK)
                lcd.drawCircle(random.randint(0,127), random.randint(0,63), random.randint(2,20), lcd.COLOR.BLACK)
                print("Sending small icon to Display..... ESC Ctrl-C to quit ")     
                # Draw small icon
                lcd.drawImage(random.randint(0,127-img_sm.size[0]), random.randint(0,63-img_sm.size[1]), img_sm)
                
                time.sleep(1.0) # Wait
#                print(ord(getch()))
                key = ord(getch())

                if key == 27: # ESC
                        print(key)
                        quit = True
                        # break  # or possibly break 
        except KeyboardInterrupt:
                quit = True
        except Exception as e:
                print("Main loop exception: " + str(e))

lcd.stop()
