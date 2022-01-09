#include<LiquidCrystal.h>

// lcd variables
const int A = 4;
const int V0 = 5;
const int RS = 8;
const int enable = 9;
const int d4 = 7;
const int d5 = 6;
const int d6 = 13;
const int d7 = 3;


LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const int lcd_contrast_address = 1;
const int lcd_brightness_address = 2;

#define displayCols 16
#define displayRows 2

// down arrow
byte downArrowByte[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

// up arrow
byte upArrowByte[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

// right arrow
byte rightArrowByte[8] = {
  B01000,
  B00100,
  B00010,
  B00001,
  B00001,
  B00010,
  B00100,
  B01000
};

byte heartByte[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

const int downArrow = 0;
const int upArrow = 1;
const int rightArrow = 2;
const int heart = 3;

// Scrolling text variables
int L1 = 14;
int L11 = 0;
