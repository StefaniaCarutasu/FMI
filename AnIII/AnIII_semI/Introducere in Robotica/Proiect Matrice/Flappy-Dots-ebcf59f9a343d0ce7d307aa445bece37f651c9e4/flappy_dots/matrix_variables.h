#include<LedControl.h>

// matrix variables
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

byte matrixBrightness = 2;
const int matrix_brightness_address = 3;

const byte moveInterval = 100;
unsigned long long lastMoved = 0;

#define matrixSize 8
bool matrixChanged = true;

bool matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}  
};

bool birdAnimationMatrix[matrixSize][matrixSize] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 1, 0, 1, 0, 0},
  {0, 1, 0, 0, 1, 1, 1, 0},
  {1, 1, 1, 0, 0, 1, 0, 0},
  {1, 0, 0, 0, 0, 1, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}  
};

bool trophyAnimationMatrix[matrixSize][matrixSize] = {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {1, 1, 0, 0, 0, 1, 1, 0},
  {1, 1, 0, 0, 0, 1, 1, 0},
  {0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 1, 0, 0, 0},
  {0, 1, 1, 0, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 0}  
};

bool xAnimationMatrix[matrixSize][matrixSize] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 1}  
};
