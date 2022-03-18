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

musicalNotes = {
    "C3": 130.81,
    "C3#": 138.59,
    "D3": 146.83,
    "D3#": 155.56,
    "E3": 164.81,
    "F3": 174.61,
    "F3#": 185.00,
    "G3": 196.00,
    "G3#": 207.65,
    "A3": 220.00,
    "A3#": 233.08,
    "B3": 246.94,
    "C4": 261.63,
    "C4#": 277.18,
    "D4": 293.66,
    "D4#": 311.13,
    "E4": 329.63,
    "F4": 349.23,
    "F4#": 369.99,
    "G4": 392.00,
    "G4#": 415.30,
    "A4": 440.00,
    "A4#": 466.16,
    "B4": 493.88,
    "C5": 523.25,
    "C5#": 554.37,
    "D5": 587.33,
    "D5#": 622.25,
    "E5": 659.25,
    "F5": 698.46,
    "F5#": 739.99,
    "G5": 783.99,
    "G5#": 830.61,
    "A5": 880.00,
    "A5#": 932.33,
    "B5": 987.77,
}

C4 = MusicalNotes(musicalNotes["C4"], 0.4)
# DO1.playTone()

D4 = MusicalNotes(musicalNotes["D4"], 0.4)
# RE.playTone()

E4 = MusicalNotes(musicalNotes["E4"], 0.4)
# MI.playTone()

F4 = MusicalNotes(musicalNotes["F4"], 0.4)
# FA.playTone()

G4 = MusicalNotes(musicalNotes["G4"], 0.4)
# SOL.playTone()

A4 = MusicalNotes(musicalNotes["A4"], 0.4)
# LA.playTone()

B4 = MusicalNotes(musicalNotes["B4"], 0.6)
# SI.playTone()

C5 = MusicalNotes(musicalNotes["C5"], 0.4)
# DO2.playTone()

# ex2
notes = [F4, G4, A4, F4, F4, G4, A4, F4, G4, A4, B4, G4, A4, B4]
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
    newNote = MusicalNotes(musicalNotes[r[0]], r[1])
    songToPlay.append(newNote.getTone())
newSong = np.concatenate(songToPlay)
sd.play(newSong, blocking=True)
sd.stop()
