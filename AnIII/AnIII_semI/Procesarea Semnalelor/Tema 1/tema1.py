import csv
import numpy as np
import sounddevice as sd


class MusicalNotes:
    def __init__(self, frequency, time_of_view):

        self.frequency = frequency
        self.amplitude = 20000
        self.phase = 0
        self.sampling_rate = 44100
        self.time_of_view = time_of_view
        self.sampling_period = 1. / self.sampling_rate  # s
        n_samples = self.time_of_view / self.sampling_period
        self.time = np.linspace(0, time_of_view, int(n_samples + 1))

        self.tone = np.array

    def sine(self):
        return self.amplitude * np.sin(2 * np.pi * self.frequency * self.time + self.phase)

    def playTone(self):
        sd.default.samplerate = self.sampling_rate
        tone = self.sine()
        wav_wave = np.array(tone, dtype=np.int16)
        sd.play(wav_wave, blocking=True)
        sd.stop()

    def getTone(self):
        sd.default.samplerate = self.sampling_rate
        tone = self.sine()
        wav_wave = np.array(tone, dtype=np.int16)
        return wav_wave



# ex1

"""
musicalNotes = {
    "DO1": 261.63,
    "RE": 293.66,
    "MI": 329.63,
    "FA": 349.23,
    "SOL": 392.00,
    "LA": 440.00,
    "SI": 493.88,
    "DO2": 523.25
}

musicalNotes = {
    "DO1": 65.41,
    "RE": 73.42,
    "MI": 82.41,
    "FA": 87.31,
    "SOL": 98.00,
    "LA": 110.00,
    "SI": 123.47,
    "DO2": 130.81
}

"""

musicalNotes = {
    "DO1": 130.81,
    "RE": 146.83,
    "MI": 164.81,
    "FA": 174.61,
    "SOL": 196.00,
    "LA": 220.00,
    "SI": 246.94,
    "DO2": 261.63
}

DO1 = MusicalNotes(musicalNotes["DO1"], 0.4)
#DO1.playTone()

RE = MusicalNotes(musicalNotes["RE"], 0.4)
#RE.playTone()

MI = MusicalNotes(musicalNotes["MI"], 0.4)
#MI.playTone()

FA = MusicalNotes(musicalNotes["FA"], 0.4)
#FA.playTone()

SOL = MusicalNotes(musicalNotes["SOL"], 0.4)
#SOL.playTone()

LA = MusicalNotes(musicalNotes["LA"], 0.4)
#LA.playTone()

SI = MusicalNotes(musicalNotes["SI"], 0.6)
#SI.playTone()

DO2 = MusicalNotes(musicalNotes["DO2"], 0.4)
#DO2.playTone()

# ex2
notes = [FA, SOL, LA, FA, FA, SOL, LA, FA, SOL, LA, SI, SOL, LA, SI]
song = [note.getTone() for note in notes]
n = np.concatenate(song, axis=0)

"""
sd.play(n, blocking=True)
sd.stop()
"""

# ex3
sheet = open('partitura.csv')
csvreader = csv.reader(sheet, quoting=csv.QUOTE_NONNUMERIC)
header = []
header = next(csvreader)
rows = []
for row in csvreader:
    rows.append(row)

sheet.close()

songToPlay = []
for r in rows:
    newNote = MusicalNotes(r[0], r[1])
    songToPlay.append(newNote.getTone())
newSong = np.concatenate(songToPlay)
sd.play(newSong, blocking=True)
sd.stop()



