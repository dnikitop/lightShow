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

class action:
	def __init__(self, note, channel, starttime):
		self.note = note
		self.channel = channel
		self.starttime = starttime
		self.endtime = 0
        
	def printA(self):
		print("Note: ", self.note, "Channel ", self.channel, "StartTime ", self.starttime, "EndTime ", self.endtime)
class event:
    red = 0
    green = 0
    unit = 0
    fade = True
    body = False
    v1 = []
    v2 = []
    def __init__(self, note, on, time, duration, channel):
        self.note = note
        self.on = on
        self.time = time
        self.duration = duration
        self.channel = channel
    def printE(self):
        print("Note: ", self.note, " On: ", self.on, " StartTime ", self.time, " Duration ", self.duration, " Channel:", self.channel)
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
            self.v2 = [26,1,0]
        elif(sNote == 28):
            self.v1 = [0,1,1]
            self.v2 = [26,1,1]
        elif(sNote == 30):
            self.v1 = [0,0,0]
            self.v2 = [26,0,0]
        elif(sNote == 32):
            self.v1 = [0,0,1]
            self.v2 = [26,0,1]
        elif(sNote == 34):
            self.v1 = [0,1,0]
            self.v2 = [8,1,0]
        elif(sNote == 36):
            self.v1 = [9,1,0]
            self.v2 = [17,1,0]
        elif(sNote == 38):
            self.v1 = [18,1,0]
            self.v2 = [26,1,0]
        elif(sNote == 40):
            self.v1 = [0,1,1]
            self.v2 = [8,1,1]
        elif(sNote == 42):
            self.v1 = [9,1,1]
            self.v2 = [17,1,1]
        elif(sNote == 44):
            self.v1 = [18,1,1]
            self.v2 = [26,1,1]
        elif(sNote == 46):
            self.v1 = [0,0,0]
            self.v2 = [8,0,0]
        elif(sNote == 48):
            self.v1 = [9,0,0]
            self.v2 = [17,0,0]
        elif(sNote == 50):
            self.v1 = [18,0,0]
            self.v2 = [26,0,0]
        elif(sNote == 52):
            self.v1 = [0,0,1]
            self.v2 = [8,0,1]
        elif(sNote == 54):
            self.v1 = [9,0,1]
            self.v2 = [17,0,1]
        elif(sNote == 56):
            self.v1 = [18,0,1]
            self.v2 = [26,0,1]
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
        if(1.0/self.duration < .32):
            self.rosMessage.frequency = .32
        else:
            self.rosMessage.frequency = 1.0/(self.duration+.08)
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
        if(self.body):
            self.msgs = MsgUpdateBodyLights()
            self.msgs.bodyLightUpdates.append(self.rosMessage)

    def publish(self):
        if(self.body):
            return self.msgs
        else:
            return self.rosMessage
    def printMes(self):
        if(self.body):
            print "CMD:", self.rosMessage.lightCmd, " Channel: ", self.channel, " Entity: ", self.rosMessage.entity, " Frequency: ", self.rosMessage.frequency, " Red: ", self.rosMessage.startColor.r, " Green: ", self.rosMessage.startColor.g
        else:
            print "CMD: ", self.rosMessage.lightCmd, " Channel: ", self.channel, " Start: ", self.rosMessage.startSegment.x, " ", self.rosMessage.startSegment.y," ", self.rosMessage.startSegment.z, " End: ", self.rosMessage.endSegment.x, " ", self.rosMessage.endSegment.y," ", self.rosMessage.endSegment.z, " Frequency: ", self.rosMessage.frequency, " Red: ", self.rosMessage.startColor.r, " Green: ", self.rosMessage.startColor.g



class midiFile:
    def __init__(self,filename):
        self.filename = filename
        mid = MidiFile(filename)
        #print (mid.ticks_per_beat)
        self.actionList = []
        time = 0
        for msg in mid:
            #print msg
            if(msg.time != 0):
                time = time + msg.time
            if(msg.type == 'note_on'):
            	x = action(msg.note, msg.channel, time)
                self.actionList.append(x) 
            elif(msg.type == 'note_off'):
                for act in self.actionList:
                    if (msg.note == act.note and act.endtime == 0 and act.channel == msg.channel):
                        if(time - act.starttime > 2):
                            act.endtime = act.starttime + 2
                        else:
                            act.endtime = time
                        break
            else:
                print msg
        self.events = []
        for act in self.actionList:
            self.events.append(event(act.note, 1, act.starttime, act.endtime - act.starttime, act.channel))
        for act in self.actionList:
            for i in range(len(self.events)):
                if(act.endtime >= self.events[i].time and(i+1 == len(self.events) or act.endtime < self.events[i+1].time)):
                    self.events.insert(i+1,event(act.note,0,act.endtime,0,act.channel))
                    break
        for eve in self.events:
            eve.makeMessage()
            eve.makeActualMessage()

    def killAll(self,pub1, pub2, rate, channel):
        print "Killing all lights"
        self.xevents = []
        self.xevents.append(event(22,0,0,1,channel))
        self.xevents.append(event(24,0,0,1,channel))
        self.xevents.append(event(26,0,0,1,channel))
        self.xevents.append(event(28,0,0,1,channel))
        self.xevents.append(event(30,0,0,1,channel))
        self.xevents.append(event(32,0,0,1,channel))
        for eve in self.xevents:
            eve.makeMessage()
            eve.makeActualMessage()
            if (eve.body):
                pub1.publish(eve.msgs)
            else:
                pub2.publish(eve.rosMessage)
            #eve.printMes()
            rate.sleep()
    def play(self, pub1, pub2, rate, channel):
        now = rospy.get_time()
        print "*******************************************************************"
        for eve in self.events:
            if(eve.channel == channel):
                while(rospy.get_time() - now < eve.time ):
                    rate.sleep()
                if(eve.body):
                    pub1.publish(eve.msgs)
                else:   
                    pub2.publish(eve.rosMessage)
            #eve.printMes()
        q = len(self.events)
        while(rospy.get_time() - now < self.events[q-1].time):
            rate.sleep()


def talker(midiFiles, channel):
    print "Starting pubs"
    pub1 = rospy.Publisher('/drivers/brainstem/cmd/update_body_lights', MsgUpdateBodyLights, queue_size=30)
    pub2 = rospy.Publisher('/drivers/brainstem/cmd/update_tote_lights', MsgUpdateToteLights, queue_size=30)
    rospy.init_node('talker',anonymous=True)
    rate = rospy.Rate(200) # 10hz
    midiFiles[0].killAll(pub1,pub2,rate,channel)
    print "Waiting for the mod 10"
    while(math.floor(rospy.get_time()) % 10 != 0):
        rate.sleep()
    print "Starting Song"
    i = 1
    now = rospy.get_time()
    for mid in midiFiles:
        print "Starting part ", i, " at time: ", rospy.get_time()
        mid.play(pub1,pub2,rate,channel)
        i = i + 1
    print "Finished at time: ", rospy.get_time()
    midiFiles[0].killAll(pub1,pub2,rate,channel)

if __name__ == '__main__':
    channel = 0
    if len(sys.argv) == 2:
        channel = int(sys.argv[1])
    print "Channel: ", channel
    midiFiles = []
    print "Loading data..."
    first = midiFile("firstgood.mid")
    second = midiFile("thirdgood.mid")
    midiFiles.append(first)
    midiFiles.append(second)
    try:
        talker(midiFiles, channel)
    except rospy.ROSInterruptException:
       pass