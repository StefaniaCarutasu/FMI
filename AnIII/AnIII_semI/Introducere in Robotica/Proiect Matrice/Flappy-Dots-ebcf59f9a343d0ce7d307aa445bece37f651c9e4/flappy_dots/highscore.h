#include<EEPROM.h>

// Highscores
String highscoreNames[3];
int highscoreValues[3];

int namesAddresses[3] = {4, 7, 10};
int scoresAddresses[3] = {13, 15, 17};

String scores[] = {
  "",
  "",
  "",
  "Back"
};

void writeIntIntoEEPROM(int address, int number)
{
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.update(address, byte1);
  EEPROM.update(address + 1, byte2);
}

int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (int)((byte1 << 8) + byte2);
}

void getHighScores() {

  int current = 0;
  String player;

  for (int i = 0; i < 3; i++) {
    player = "";
    for (int j = namesAddresses[current]; j < namesAddresses[current] + 3; j++) {
      player += char(EEPROM.read(j));
    }
    highscoreNames[current] = String(player);
    current++;
  }

  current = 0;
  for (int i = 0; i < 3; i++ ) {
    highscoreValues[current] = readIntFromEEPROM(scoresAddresses[i]);
    current++;

  }

  for (int i = 0; i < 3; i++) {
    String newEntry = highscoreNames[i] + " " + String(highscoreValues[i]);
    scores[i] = newEntry;
  }
}

int compareScores(int score) {
  for (int i = 0; i < 3; i++) {
    if (score > highscoreValues[i]) {
      return i;
    }
  }

  return -1;
}

void shiftScores(String player, int score, int pos) {
  if (pos == 1) {
    highscoreNames[2] = highscoreNames[1];
    highscoreValues[2] = highscoreValues[1];
  }
  else if (pos == 0) {
    highscoreNames[2] = highscoreNames[1];
    highscoreValues[2] = highscoreValues[1];
    
    highscoreNames[1] = highscoreNames[0];
    highscoreValues[1] = highscoreValues[0];   
  }
  
  highscoreNames[pos] = player;
  highscoreValues[pos] = score;
}

void updateEEPROM() {

  for (int i = 0; i < 3; i++) {
    int k = 0;
    for (int j = namesAddresses[i]; j < namesAddresses[i] + 3; j++) {
      EEPROM.update(j, highscoreNames[i][k]);
      k++;
    }
  }

  for (int i = 0; i < 3; i++) {
    writeIntIntoEEPROM(scoresAddresses[i], highscoreValues[i]);
  }
}

void resetScores() {
  for (int i = 0; i < 3; i++) {
    highscoreNames[i] = "aaa";
    highscoreValues[i] = 0;
  }

  updateEEPROM();
}
