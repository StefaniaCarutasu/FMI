#include "LedControl.h" //  need the library
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
const int rows = 8;
const int cols = 8;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER
 
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219
 
void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

void loop()
{
  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      lc.setLed(0, col, row, true); // turns on LED at col, row
      delay(25);
    }
  }
  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      lc.setLed(0, col, row, false); // turns off LED at col, row
      delay(25);
    }
  }
}
