import tkinter as tk
import serialInputs

class UI():
        
        def _init_(self):
                self.inputs = serialInputs.serialInputs()
                self.inputs._init_()
                self.prev = "S"
                
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
                        if key_press == "S":
                                self.inputs.stop()
                        if key_press == "V":
                                self.inputs.start_record()
                        if key_press == "Q":
                                self.inputs.stop_record()
                        if key_press == "D":
                                self.inputs.start_playback()
                        if key_press == "E":
                                self.inputs.start_playback_file()
                        self.prev = key_press

                
ui = UI()
ui._init_()
window = tk.Tk()
window.bind_all('<Key>', ui.key_input)
window.mainloop()

