import msvcrt

print ("press 'escape' or A to quit...")

while 1:
    char = msvcrt.getch()
    if char == chr(27):
        print (char),
        print ("..."),
        print (ord(char)),
        break
    if 27 == ord(char):
        print (char),
        print ("..."),
        print (ord(char)),
        break

    if 65 == ord(char):
        print (char),
        print ("..."),
        print (ord(char)),
        break

    if 97 == ord(char):
        print (char),
        print ("..."),
        print (ord(char)),
        break
    if char == chr(41):
        print (char),
        print ("..."),
        print (ord(char)),
        break
    print (char),
    print ("..."),
    print (ord(char)),
    if char == chr(13):
        print
