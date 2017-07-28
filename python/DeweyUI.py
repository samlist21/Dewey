import Tkinter as tk
import serialInputs
import sys
from SimpleCV import Camera


class UI():
        
        def _init_(self):
            if sys.platform == "windows":
                meme = ""
                self.inputs = "W"
            else:
                self.inputs = serialInputs.serialInputs()
            self.inputs._init_()
            self.prev = "S"
            self.speeds = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
            self.camera = Camera()
        def key_input(self, event):
                key_press = event.keysym.upper()
                if key_press != self.prev:
                        if key_press == "RIGHT":
                            self.inputs.right()
                        if key_press == "LEFT":
                            self.inputs.left()
                        if key_press == "UP":
                            self.inputs.forward()
                        if key_press == "DOWN":
                            self.inputs.back()
                        if key_press == "S" or key_press == "0":
                            self.inputs.stop()
                        if key_press in self.speeds:
                            self.inputs.change_speed(key_press)
                        if key_press == "V":
                            self.inputs.start_record()
                        if key_press == "Q":
                            self.inputs.stop_record()
                        if key_press == "D":
                            self.inputs.start_playback()
                        if key_press == "E":
                            self.inputs.start_playback_file()
                        if key_press == "A":
                            self.inputs.start_autonomous();
                        self.prev = key_press
        def half(self,left,right): 
                result = left
                crop   = right.crop(right.width/2.0,0,right.width/2.0,right.height)
                result = result.blit(crop,(left.width/2,0))
                return result
        def updateCamera(self):
                #img = self.camera.getImage();
                #img.save('image.png')
                #img.show()
                while True:
                        img = self.camera.getImage()
                        output = img.edges(t1=80)
                        output.getHorzScanline(10)
                        output.show()

ui = UI()
ui._init_()
window = tk.Tk()
window.bind_all('<Key>', ui.key_input)
ui.updateCamera();
window.mainloop()
