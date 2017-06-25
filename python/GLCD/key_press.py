from msvcrt import getch

#import getch
import time

waitTime = 1.0

while True:
    #key1 = input()

    #print(key1)
    print("....")
    key = getch()
    print(key)
    print("Waiting for key")

    time.sleep(1.0)
