#include "LedControl.h" //  need the library
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
const int rows = 8;
const int cols = 8;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER
 
const int n = 8;
 
void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}
void loop()
{
  //some animations
  road();
  delay(500);
  lc.clearDisplay(0);
  bread(); //or pizza
  delay(2000);
  lc.clearDisplay(0);
  flower();
  delay(2000);
  lc.clearDisplay(0);
  heart();
  delay(400);
  lc.clearDisplay(0);
  delay(500);
  heart();
  delay(400);
  lc.clearDisplay(0);
  delay(500);
  heart();
  delay(400);
  lc.clearDisplay(0);
  delay(500);
  heart();
  delay(400);
  lc.clearDisplay(0);
  delay(500);
}
 
//ROAD
void road()
{
  int i = 0, j = 0;
  for (j = 0; j < n; j++)
  {
    lc.setLed(0, 0, j, true);
    lc.setLed(0, 1, j, true);
    lc.setLed(0, 6, j, true);
    lc.setLed(0, 7, j, true);
  }
 
  for (i = 0; i <= n; i++)
    for (j = 0; j < n + 3; j++)
    {
      lc.setLed(0, 3, j - 3, false);
      lc.setLed(0, 4, j - 3, false);
      lc.setLed(0, 3, j - 2, true);
      lc.setLed(0, 4, j - 2, true);
      lc.setLed(0, 3, j - 1, true);
      lc.setLed(0, 4, j - 1, true);
      lc.setLed(0, 3, j, true);
      lc.setLed(0, 4, j, true);
      delay(70);
    }
}
 
 
//BREAD
void bread()
{
  int i = 0, j = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if ((i + j + 1) < 2 * (n - 1) && (i + j) > 1 && !(j >= (n - 2) && i <= 1 && (j - i) >= n - 2) && !(i >= (n - 2) && j <= 1 && (i - j) >= n - 2))
        lc.setLed(0, i, j, true);
  delay(500);
 
  for (i = 0; i < n / 2; i++) {
    for (j = 0; j < n / 2; j++)
    {
      lc.setLed(0, i, j, false);
    }
  }
  delay(500);
 
  for (i = 0; i < n / 2; i++) {
    for (j = 0; j < n / 2 + 1; j++)
    {
      lc.setLed(0, i, n - j, false);
    }
  }
  delay(500);
 
  for (i = 0; i < n / 2 + 1; i++) {
    for (j = 0; j < n / 2 + 1; j++)
    {
      lc.setLed(0, n - i, n - j, false);
    }
  }
  delay(500);
 
  for (i = 0; i < n / 2 + 1; i++) {
    for (j = 0; j < n / 2 + 1; j++)
    {
      lc.setLed(0, n - i, j, false);
    }
  }
}
 
//FLOWER
void flower()
{
  for (int i = 3; i >= 1; i--) {
    for (int j = 3; j >= 1; j--) {
      if ((i + j) != 4)
      {
        lc.setLed(0, i, j, true);
        delay(150);
        lc.setLed(0, n - i - 1, n - j - 1, true);
        delay(150);
        lc.setLed(0, n - i - 1, j, true);
        delay(150);
        lc.setLed(0, i, n - j - 1, true);
        delay(150);
      }
    }
  }
}
 
//HEART
void heart()
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n / 2; j++) {
      if (
        (i == 0 && (j == 0 || j == 3)) ||
        (i == 5 &&  j == 0) ||
        (i == 6 && (j == 0 || j == 1)) ||
        (i == 7 && (j == 0 || j == 1 || j == 2))
      )
      {
        lc.setLed(0, i, j, false);
        lc.setLed(0, i, n - j - 1, false);
      }
 
      else
      {
        lc.setLed(0, i, j, true);
        lc.setLed(0, i, n - j - 1, true);
      }
    }
  }
}
