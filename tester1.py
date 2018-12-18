#!/usr/bin/env python
import rospy
import sys
import mido
import time
from srslib_framework.msg import MsgUpdateBodyLights
from srslib_framework.msg import MsgBodyLightsState
from srslib_framework.msg import MsgUpdateToteLights
from mido import MidiFile
import math

def killAll(pub1, pub2):
    newMsg = MsgBodyLightsState()
    newMsg1 = MsgBodyLightsState()
    newMsg2 = MsgUpdateToteLights()
    mssg = MsgUpdateBodyLights()
    newMsg.lightCmd = 1
    newMsg.entity = 204
    mssg.bodyLightUpdates.append(newMsg)
    pub1.publish(mssg)

    newMsg1.lightCmd = 1
    newMsg1.entity = 205
    mssg2 = MsgUpdateBodyLights()
    mssg2.bodyLightUpdates.append(newMsg1)
    pub1.publish(mssg2)
    newMsg2.frequency = 3
    newMsg2.startColor.r = 0
    newMsg2.startColor.g = 0
    newMsg2.startColor.b = 0
    newMsg2.startColor.a = 0
    newMsg2.endColor.r = 0
    newMsg2.endColor.g = 0
    newMsg2.endColor.b = 0
    newMsg2.endColor.a = 0

    newMsg2.lightCmd = 1
    newMsg2.startSegment.x = 0
    newMsg2.startSegment.y = 0
    newMsg2.startSegment.z = 0
    newMsg2.endSegment.x = 25
    newMsg2.endSegment.y = 0
    newMsg2.endSegment.z = 0
    pub2.publish(newMsg2)
    newMsg2.startSegment.y = 1
    newMsg2.endSegment.y = 1
    pub2.publish(newMsg2)
    newMsg2.startSegment.z = 1
    newMsg2.endSegment.z = 1
    pub2.publish(newMsg2)
    newMsg2.startSegment.y = 0
    newMsg2.startSegment.z = 1
    newMsg2.endSegment.y = 0
    newMsg2.endSegment.z = 1
    pub2.publish(newMsg2) 
  



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
        if(self.body):
            self.rosMessage = MsgBodyLightsState()
        else:
            self.rosMessage = MsgUpdateToteLights()

    def setColor(self):
        self.rosMessage.startColor.r = self.red
        self.rosMessage.startColor.g = self.green
        self.rosMessage.startColor.b = 0
        self.rosMessage.startColor.a = 0
        self.rosMessage.endColor.r = 0
        self.rosMessage.endColor.g = 0
        self.rosMessage.endColor.b = 0
        self.rosMessage.endColor.a = 0
        self.rosMessage.frequency = 1.0/self.duration
    def setOffColor(self):
        self.rosMessage.startColor.r = 0
        self.rosMessage.startColor.g = 0
        self.rosMessage.startColor.b = 0
        self.rosMessage.startColor.a = 0
        self.rosMessage.endColor.r = 0
        self.rosMessage.endColor.g = 0
        self.rosMessage.endColor.b = 0
        self.rosMessage.endColor.a = 0
        self.rosMessage.frequency = 1

    def makeActualMessage(self):
        if(self.on == 1):
            if(self.fade):
                    self.rosMessage.lightCmd = 2
                    self.setColor()
            else:
                    self.rosMessage.lightCmd = 1
                    self.setColor()
        else:
                self.rosMessage.lightCmd = 1
                self.setOffColor()
        if(self.body):
            self.rosMessage.entity = self.unit
        else:
            self.rosMessage.startSegment.x = self.v1[0]
            self.rosMessage.startSegment.y = self.v1[1]
            self.rosMessage.startSegment.z = self.v1[2]
            self.rosMessage.endSegment.x = self.v2[0]
            self.rosMessage.endSegment.y = self.v2[1]
            self.rosMessage.endSegment.z = self.v2[2]

    def publish(self):
        if(self.body):
            msgs = MsgUpdateBodyLights()
            msgs.bodyLightUpdates.append(self.rosMessage)
            return msgs
        else:
            return self.rosMessage
    def printMes(self):
        if(self.body):
            print "CMD:", self.rosMessage.lightCmd, " Entity: ", self.rosMessage.entity, " Frequency: ", self.rosMessage.frequency, " Red: ", self.rosMessage.startColor.r, " Green: ", self.rosMessage.startColor.g
        else:
            print "CMD: ", self.rosMessage.lightCmd, " Start: ", self.rosMessage.startSegment.x, " ", self.rosMessage.startSegment.y," ", self.rosMessage.startSegment.z, " End: ", self.rosMessage.endSegment.x, " ", self.rosMessage.endSegment.y," ", self.rosMessage.endSegment.z, " Frequency: ", self.rosMessage.frequency, " Red: ", self.rosMessage.startColor.r, " Green: ", self.rosMessage.startColor.g



class midiFile:
    def __init__(self,filename):
        self.filename = filename
        mid = MidiFile(filename)
        print (mid.ticks_per_beat)
        self.actionList = []
        time = 0
        for msg in mid:
            if(msg.time != 0):
                time = time + msg.time
            if(msg.type == 'note_on'):
                if(msg.channel == 1):
                    #print msg
                    x = action(msg.note, msg.channel, time)
                    self.actionList.append(x) 
            elif(msg.type == 'note_off'):
                if(msg.channel == 1):
                    #print msg
                    for act in self.actionList:
                        if (msg.note == act.note and act.endtime == 0 and msg.channel == act.channel):
                            act.endtime = time
                            break
        self.events = []
        for act in self.actionList:
            self.events.append(event(act.note, 1, act.starttime, act.endtime - act.starttime))
        for act in self.actionList:
            for i in range(len(self.events)):
                if(act.endtime >= self.events[i].time and (i+1 == len(self.events) or act.endtime < self.events[i+1].time)):
                    self.events.insert(i+1,event(act.note,0,act.endtime,0))
                    break
        for eve in self.events:
            eve.makeMessage()
            eve.makeActualMessage()
            eve.printMes()
    def killAll(self,pub1, pub2, rate):
        self.xevents = []
        self.xevents.append(event(22,0,0,1))
        self.xevents.append(event(24,0,0,1))
        self.xevents.append(event(26,0,0,1))
        self.xevents.append(event(28,0,0,1))
        self.xevents.append(event(30,0,0,1))
        self.xevents.append(event(32,0,0,1))
        for eve in self.xevents:
            eve.makeMessage()
            eve.makeActualMessage()
            if (eve.body):
                pub1.publish(eve.publish())
            else:
                pub2.publish(eve.publish())
            eve.printMes()
            rate.sleep()

def talker(midiFile):
    
    pub1 = rospy.Publisher('/drivers/brainstem/cmd/update_body_lights', MsgUpdateBodyLights, queue_size=10)
    pub2 = rospy.Publisher('/drivers/brainstem/cmd/update_tote_lights', MsgUpdateToteLights, queue_size=10)
    rospy.init_node('talker',anonymous=True)
    time.sleep(2)
    now = rospy.get_time()
    rate = rospy.Rate(100) # 10hz
    print "*******************************************************************"
    midiFile.killAll(pub1, pub2, rate)
    print "0000000000000000000000000000000000000000000000000000000000000000000"
    while(math.floor(rospy.get_time()) % 10 != 0):
        pass
    print rospy.get_time()
    for eve in midiFile.events:
        while(rospy.get_time() - now < eve.time ):
            #do Nothing
            pass
        if(eve.body):
            pub1.publish(eve.publish())
        else:   
            pub2.publish(eve.publish())
        eve.printMes()
    midiFile.killAll(pub1,pub2,rate)
if __name__ == '__main__':
    first = midiFile("second.mid")
    try:
        talker(first)
    except rospy.ROSInterruptException:
       pass