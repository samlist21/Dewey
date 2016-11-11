import serial
import record
import time

ser = serial.Serial('/dev/ttyACM0',115200)

class serialInputs():
    def _init_(self):
        inputVal = 1
        self.deweyRecord = record.record()
    # TODO move this print('Received inputVal='+ inputVal + ",Sending=" + inputValUpper)
    # Python 2 users
    #input = raw_input(">> ")    
    def stop_record(self):
        # could send an X to Arduino but it would kill any restart
        # So now just sending an 'S'
        ser.write('S'.encode('utf-8'))
        # if recording was not stopped end recording. 
        print("Dewey Record Ending - if it was going")
        self.deweyRecord.rec_stop()
        print("Stopping Dewey")
        ser.close()
        print("Port and program closed")
        # Exit if desired
        #exit()

    def start_record(self):
        # V Means start recording
        print("Dewey Record Beginning.....")
        self.deweyRecord.rec_start()

    def stop_record(self):
        # Q Means stop recording  
        # Stop the recording
        print("....Dewey Record Ending")
        self.deweyRecord.rec_stop()
        # Print out the list so we can verify it - if desired
        self.deweyRecord.rec_print()
        
    def start_playback(self):
        # D Means Do Playback
        print("Dewey Record Playback")
        # Next  Line prints the list - if desired
        #deweyRecord.rec_print()    
        #Next Line shows file - if desired
        #deweyRecord.playback()
        # this runs without moving
        # Playback from the current list - Retrieve list
        self.runList = self.deweyRecord.playback_list()
        print("-- Running Playback -- ")
        self.playback()

    def start_playback_file(self):
        # E Means Do Playback from a file
        print("Dewey File Record Playback")
        self.runList = self.deweyRecord.playback_file()
        print("-- Running Playback from File -- ")
        self.playback()
        
    def forward(self):
        inputVal = 'F'
        ser.write(inputVal.encode('utf-8'))
        print("Forward")
        
    def back(self):
        inputVal = 'B'
        ser.write(inputVal.encode('utf-8'))
        print("Back")
        
    def left(self):
        inputVal = 'L'
        ser.write(inputVal.encode('utf-8'))
        print("Left")
        
    def right(self):
        inputVal = 'R'
        ser.write(inputVal.encode('utf-8'))
        print("Right")

    def stop(self):
        inputVal = 'S'
        ser.write(inputVal.encode('utf-8'))
        print("Stop")

    def change_speed(self, speed):
        ser.write(speed.encode('utf-8'))
        print("Change Speed" + speed);

    def playback(self):
        for run in self.runList:
            print(step['command'] + " will run for " + str(step['time']) + " seconds\r")
            ser.write(step['command'].encode('utf-8'))
            print("Wrote out a " + step['command'])
            time.sleep(step['time'])
        
