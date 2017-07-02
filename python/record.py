import time
#import pickle  # an alternate to json but did not work 
import json as simplejson

class record():
    """ record  the manual actions for Dewey playback """

    def __init__(self):
        """  Initialize the blank list and a recording vaiable"""
        self.my_List = []
        self.start_Time = 0
        self.end_Time = 0
        # means we are ready to begin recording
        self.recording = False
        self.savedCommand = '$'

    def rec_start(self):
        # if list decicde to save or clear
        if self.my_List:
            print ("I got to here before input")
            listSave = input("List Exists - Do you want to save previous list? (Y/n)")
            print ("I got to here")
            print("Save value is", listSave)
            if listSave == "n":
                # Don't save so cear list
                print("Clearing old list - No Save")

                
            else:
                # Save so save to file
                self.rec_saveList()

                # List Saved
                print("Old list Saved - now Clearing old list")

        # Clear the list
        self.my_List = []

        print("Recording Queued...")
        self.recording = True
        # start time is irrelevant but can be printed
        #print("Recording Started...at " + str(startTime))

    def rec_stop(self):
        # Send one last Step to capture the last command
        self.command_store('$')
        self.recording = False
        print("...Recording Stopped")


    def command_store(self, command):
        # if this is the first command begin the timer at current time
        if self.recording == True  :

            # first time in - don't record until step is complete (we have time)
            if self.savedCommand != '$' :

                # End time of last step
                self.end_Time =time.time()

                roundTime = round(self.end_Time-self.start_Time,2)
                # Store last step command and time of last step (Duration)
                currentStep = {'command':self.savedCommand,'time':roundTime}
                # append Step and time to list
                self.my_List.append(currentStep)
                
                # Print recorded Step for us to see
                print("Current Recording Step")
                print (currentStep)

            # Store if recording
            # no sense storing if not recording
            self.start_Time =time.time()    # New Start Time 
            self.savedCommand = command    # Store this new Command 

    def playback(self):
        """ playback that runs the list """
        if self.my_List:
            print("-- Running Playback -- ")
            for step in self.my_List:
                print (step)
                print(step['command'] +" will run for "+ str(step['time']) + " seconds")
                time.sleep(step['time'])

    def playback_list(self):
        """ playback to just return the list """
        # other program will execute the commands
        return  self.my_List

    def playback_file(self):
        """ Get list from file for playback """
        self.rec_loadList(self)
        # list is loaded into my_List
        # should probably check for overwrite = OK
        # Assume it is or you wouldn't want to be loading
        # also could start a new record to save last list

        return  self.my_List

    def rec_print(self):
        if self.my_List:
            print("-- Here is your list --")
            for step in self.my_List:
                print (step)
        else:
            print("No List to Print")


    def rec_saveList(self):
        # default is to save - anything but a small "n"
        filenameSave = input("Enter Save Filename - no spaces ")
        f = open(filenameSave,"w")
        simplejson.dump(self.my_List,f)

        f.close()

    def rec_loadList(self):
        filenameGet = input("Enter Filename to Load that contains the Command List" )
        f = open(filenameGet,"r")
        self.my_List = simplejson.load(f)
        self.rec_print()
        f.close()
        
