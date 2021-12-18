import numpy as np
import sounddevice as sd


class MusicalNotes:
    def __init__(self, frequency, time_of_view):
        self.frequency = frequency
        self.amplitude = 10000
        self.phase = 0
        self.sampling_rate = 44100
        self.time_of_view = time_of_view
        self.sampling_period = 1. / self.sampling_rate  # s
        n_samples = self.time_of_view / self.sampling_period
        self.time = np.linspace(0, time_of_view, int(n_samples + 1))

    def sine(self):
        return self.amplitude * np.sin(2 * np.pi * self.frequency * self.time + self.phase)

    def playTone(self):
        sd.default.samplerate = self.sampling_rate
        tone = self.sine()
        wav_wave = np.array(tone, dtype=np.int16)
        sd.play(wav_wave, blocking=True)
        sd.stop()

        return wav_wave

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

DO1 = MusicalNotes(musicalNotes["DO1"], 0.3)
#DO1.playTone()

RE = MusicalNotes(musicalNotes["RE"], 0.3)
#RE.playTone()

MI = MusicalNotes(musicalNotes["MI"], 0.3)
#MI.playTone()

FA = MusicalNotes(musicalNotes["FA"], 0.3)
#FA.playTone()

SOL = MusicalNotes(musicalNotes["SOL"], 0.3)
#SOL.playTone()

LA = MusicalNotes(musicalNotes["LA"], 0.3)
#LA.playTone()

SI = MusicalNotes(musicalNotes["SI"], 0.3)
#SI.playTone()

DO2 = MusicalNotes(musicalNotes["DO2"], 0.3)
#DO2.playTone()

song = [DO1, RE, MI, DO1, DO1, RE, MI, DO1, MI, FA, MusicalNotes(musicalNotes["SOL"], 0.6), MI, FA, MusicalNotes(musicalNotes["SOL"], 0.6)]
for i in song:
    i.playTone()


