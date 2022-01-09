#include "pitches.h"
const int buzzerPin = 1;

float song[] = {
  DO1, MI, RE, FA, MI, SOL, FA, LA, SOL, SI, LA, DO2
};

#define songLength 12

const int noteDuration = 4;

unsigned long lastTone = 0;
int toneInterval = (1000 / 4) * 1.30;
int note = 0;

#define musicChoiceAddress 19
int playMusic = 1;

void playMelody() {
  int noteDuration = 1000 / noteDuration;
  tone(buzzerPin, song[note], noteDuration);
  note++;
}

void playDeathPitch() {
  tone(buzzerPin, C2, 700);
}

void playMoveUpPitch() {
  tone(buzzerPin, DO2, 200);
}

void playMoveDownPitch() {
  tone(buzzerPin, DO1, 200);
}
