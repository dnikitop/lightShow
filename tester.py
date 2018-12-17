#!/usr/bin/env python
import rospy
import sys
import mido
import time
from srslib_framework.msg import MsgUpdateBodyLights
from srslib_framework.msg import MsgBodyLightsState
from srslib_framework.msg import MsgUpdateToteLights
from mido import MidiFile

class action:
	def __init__(self, note, channel, starttime):
		self.note = note
		self.channel = channel
		self.starttime = starttime
		self.endtime = 0
        
	def printA(self):
		print(self.note, " ", self.channel, " ", self.starttime, " ", self.endtime)
class event:
    
    red = 0
    green = 0
    unit = 0
    fade = True
    body = False
    v1 = []
    v2 = []
    blue = 0
    def __init__(self, note, on, time, duration):
        self.note = note
        self.on = on
        self.time = time
        self.duration = duration
    def printE(self):
        print(self.note, " ", self.on, " ", self.time, " ", self.duration)
    def makeMessage(self):
        sNote = self.note
        if(self.note >= 58 ):
            self.fade = False
            sNote = self.note - 36
        if(self.note % 2 == 0):
            self.green = 255
            self.red = 0
        else:
            self.green = 0
            self.red = 255
            sNote = sNote - 1
        if(sNote == 22):
            self.body = True
            self.unit = 205
        elif(sNote == 24):
            self.body = True
            self.unit = 204
        elif(sNote == 26):
            self.v1 = [0,1,0]
            self.v2 = [25,1,0]
        elif(sNote == 28):
            self.v1 = [0,1,1]
            self.v2 = [25,1,1]
        elif(sNote == 30):
            self.v1 = [0,0,0]
            self.v2 = [25,0,0]
        elif(sNote == 32):
            self.v1 = [0,0,1]
            self.v2 = [25,0,1]
        elif(sNote == 34):
            self.v1 = [0,1,0]
            self.v2 = [8,1,0]
        elif(sNote == 36):
            self.v1 = [9,1,0]
            self.v2 = [16,1,0]
        elif(sNote == 38):
            self.v1 = [17,1,0]
            self.v2 = [25,1,0]
        elif(sNote == 40):
            self.v1 = [0,1,1]
            self.v2 = [8,1,1]
        elif(sNote == 42):
            self.v1 = [9,1,1]
            self.v2 = [16,1,1]
        elif(sNote == 44):
            self.v1 = [17,1,1]
            self.v2 = [25,1,1]
        elif(sNote == 46):
            self.v1 = [0,0,0]
            self.v2 = [8,0,0]
        elif(sNote == 48):
            self.v1 = [9,0,0]
            self.v2 = [16,0,0]
        elif(sNote == 50):
            self.v1 = [17,0,0]
            self.v2 = [25,0,0]
        elif(sNote == 52):
            self.v1 = [0,0,1]
            self.v2 = [8,0,1]
        elif(sNote == 54):
            self.v1 = [9,0,1]
            self.v2 = [16,0,1]
        elif(sNote == 56):
            self.v1 = [17,0,1]
            self.v2 = [25,0,1]

    def setColor(self):
        self.newMsg.startColor.r = self.red
        self.newMsg.startColor.g = self.green
        self.newMsg.startColor.b = 0
        self.newMsg.startColor.a = 0
        self.newMsg.endColor.r = 0
        self.newMsg.endColor.g = 0
        self.newMsg.endColor.b = 0
        self.newMsg.endColor.a = 0
        self.newMsg.frequency = 1.0/self.duration
    def setOffColor(self):
        self.newMsg.startColor.r = 0
        self.newMsg.startColor.g = 0
        self.newMsg.startColor.b = 0
        self.newMsg.startColor.a = 0
        self.newMsg.endColor.r = 0
        self.newMsg.endColor.g = 0
        self.newMsg.endColor.b = 0
        self.newMsg.endColor.a = 0
        self.newMsg.frequency = 0

    def setColor2(self):
        self.newMsg2.startColor.r = self.red
        self.newMsg2.startColor.g = self.green
        self.newMsg2.startColor.b = 0
        self.newMsg2.startColor.a = 0
        self.newMsg2.endColor.r = 0
        self.newMsg2.endColor.g = 0
        self.newMsg2.endColor.b = 0
        self.newMsg2.endColor.a = 0
        self.newMsg2.frequency = 1.0/self.duration
    def setOffColor2(self):
        self.newMsg2.startColor.r = 0
        self.newMsg2.startColor.g = 0
        self.newMsg2.startColor.b = 0
        self.newMsg2.startColor.a = 0
        self.newMsg2.endColor.r = 0
        self.newMsg2.endColor.g = 0
        self.newMsg2.endColor.b = 0
        self.newMsg2.endColor.a = 0
        self.newMsg2.frequency = 0

    def makeActualMessage(self):
        self.newMsg = MsgBodyLightsState()
        self.newMsg2 = MsgUpdateToteLights()
        if(self.body):
            self.newMsg.entity = self.unit
            if(self.on == 1): 
                if(self.fade):
                    self.newMsg.lightCmd = 2
                    self.setColor()
                else:
                    self.newMsg.lightCmd = 1
                    self.setColor()
            else:
                self.newMsg.lightCmd = 0
                self.setOffColor()
        else:
            self.newMsg2.startSegment.x = self.v1[0]
            self.newMsg2.startSegment.y = self.v1[1]
            self.newMsg2.startSegment.z = self.v1[2]
            self.newMsg2.endSegment.x = self.v2[0]
            self.newMsg2.endSegment.y = self.v2[1]
            self.newMsg2.endSegment.z = self.v2[2]
            if(self.on == 1): 
                if(self.fade):
                    self.newMsg2.lightCmd = 2
                    self.blue = 255
                    self.setColor2()
                    
                else:
                    self.newMsg2.lightCmd = 1
                    self.setColor2()
            else:
                self.newMsg2.lightCmd = 0
                self.setOffColor2()

    def publish(self):
        if(self.body):
            msgs = MsgUpdateBodyLights()
            msgs.bodyLightUpdates.append(self.newMsg)
            return msgs
        else:
            return self.newMsg2




filename = "second.mid"
mid = MidiFile(filename)
print (mid.ticks_per_beat)
actionList = []
time = 0
for msg in mid:
    if(msg.time != 0):
        time = time + msg.time
    if(msg.type == 'note_on'):
        if(msg.channel == 1):
            x = action(msg.note, msg.channel, time)
            actionList.append(x) 
    elif(msg.type == 'note_off'):
        if(msg.channel == 1):
            i = 0
            for act in actionList:
                if (msg.note == act.note and act.endtime == 0 and msg.channel == act.channel and i == 0):
                    act.endtime = time
                    i = 1
events = []
for act in actionList:
    events.append(event(act.note, 1, act.starttime, act.endtime - act.starttime))
for act in actionList:
    for i in range(len(events)):
        if(act.endtime >= events[i].time and (i+1 == len(events) or act.endtime < events[i+1].time)):
            events.insert(i+1,event(act.note,0,act.endtime,0))
            break



for eve in events:
    eve.makeMessage()
    #eve.printE()
    eve.makeActualMessage() 

pub1 = rospy.Publisher('/drivers/brainstem/cmd/update_body_lights', MsgUpdateBodyLights, queue_size=10)
pub2 = rospy.Publisher('/drivers/brainstem/cmd/update_tote_lights', MsgUpdateToteLights, queue_size=10)
rospy.init_node('talker',anonymous=True)
now = rospy.get_time()
for eve in events:
    
    while(rospy.get_time() - now < eve.time):
        #do Nothing
        pass
    print eve.newMsg2.lightCmd, eve.time
    if(eve.body):
        pub1.publish(eve.publish())
    else:   
        pub2.publish(eve.publish())
