#!/usr/bin/env python

import sys
#!/usr/bin/env python
import mido
import time
from mido import MidiFile
from pygame import mixer

class action:
	def __init__(self, note, channel, starttime):
		self.note = note
		self.channel = channel
		self.starttime = starttime
		self.endtime = 0
	def print(self):
		print(self.note, " ", self.channel, " ", self.starttime, " ", self.endtime)

filename = "second.mid"
mid = MidiFile(filename)
print (mid.ticks_per_beat)
actionList = []
time = 0
for msg in mid:
    if(msg.time != 0):
        time = time + msg.time
    if(msg.type == 'note_on'):
        x = action(msg.note, msg.channel, time)
        actionList.append(x) 
    elif(msg.type == 'note_off'):
        i = 0
        for act in actionList:
            if (msg.note == act.note and act.endtime == 0 and msg.channel == act.channel and i == 0):
                act.endtime = time
                i = 1
        if(i == 0):
        	print("**************************")
for act in actionList:
    if(act.channel == 1):
	    act.print()