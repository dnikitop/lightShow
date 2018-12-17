#!/usr/bin/env python

import sys
#!/usr/bin/env python
import mido
import time
from mido import MidiFile
from pygame import mixer

filename = "first.mid"

mixer.init()
mixer.music.load('song.mp3')
mixer.music.play()
time.sleep(.5)
if len(sys.argv) == 3:
    portname = sys.argv[2]
else:
    portname = None

with mido.open_output(portname) as output:
    try:
        midifile = MidiFile(filename)
        t0 = time.time()
        for message in midifile.play():
            print(message)
            output.send(message)
        print('play time: {:.2f} s (expected {:.2f})'.format(
                time.time() - t0, midifile.length))

    except KeyboardInterrupt:
        print()
        output.reset()

