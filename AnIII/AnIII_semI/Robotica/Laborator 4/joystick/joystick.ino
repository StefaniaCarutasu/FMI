//const int pinSW = 10; // digital pin connected to switch output
//const int pinX = A0; // A0 - analog pin connected to X output
//const int pinY = A1; // A1 - analog pin connected to Y output
//int switchValue;
//int xValue = 0;
//int yValue = 0;
//void setup() {
//  pinMode(pinSW, INPUT_PULLUP); //activate pull-up resistor on the                     // push-button pin
//  // Start the serial communication.
//  Serial.begin(9600);
//}
//
//void loop() {
//  switchValue = digitalRead(pinSW);
//  xValue = analogRead(pinX);
//  yValue = analogRead(pinY);
// 
//  Serial.print("Switch:  ");
//  Serial.print(switchValue);
//  Serial.print("  |  ");
//  Serial.print("X-axis: ");
//  Serial.print(xValue);
//  Serial.print("  |  ");
//  Serial.print("Y-axis: ");
//  Serial.print(yValue);
//  Serial.println("  |  ");
//  delay(200);
//}

// declare all the joystick pins
const int pinSW = 10; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// declare all the segments pins
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int segSize = 8;
const int noOfDigits = 10;
// dp on or off
bool dpState = LOW;
// states of the button press
bool swState = LOW;
bool lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int digit = 0;
int minThreshold= 400;
int maxThreshold= 600;

// store the pins in an array for easier access
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
  digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}
void setup() {
  // initialize all the pins
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
 
  displayNumber(digit, dpState); // initial value displayed. Choose any value
}

void loop() {
  xValue = analogRead(pinX);
  swState = digitalRead(pinSW);
 // On Ox axis, if the value is lower than a chosen min threshold, then
 // decrease by 1 the digit value.

 if(xValue < minThreshold && joyMoved == false) {
  joyMoved = true;
  digit--; 

  if(digit < 0) {
    digit = 9;
  }
 }

 if(xValue > maxThreshold && joyMoved == false) {
  joyMoved = true;
  digit++; 

  if(digit > 9) {
    digit = 0;
  }
 }

 if (minThreshold <= xValue && xValue <= maxThreshold) {
  joyMoved = false;
 }

 if (swState == LOW && swState != lastSwState) {
  dpState = !dpState;
 }

 lastSwState = swState;

 displayNumber(digit, dpState);
 
 delay(1);
}
