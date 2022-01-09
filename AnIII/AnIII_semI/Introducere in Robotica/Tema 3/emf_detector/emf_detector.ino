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

//for the antenna
const int pinAntenna = A0;
unsigned int readValue = 0;

const int maxConstraint = 100;
const int maxDisplayed = 9;

//buzer variables
const int buzzerPin = 11;
int buzzerTone = 0;
int toneDuration = 10;

//time constant
const int readingInterval = 500;
unsigned int elapsedTime = 0;

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

void setup() {
  // initialize all the pins
  for (int i = 0; i < segSize; i++) {
  pinMode(segments[i], OUTPUT);
  }

  pinMode(pinAntenna, INPUT);

  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void displayNumber(byte digit) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }

//  buzzerTone = (digit + 1) * 100;
//  tone(buzzerPin, buzzerTone, toneDuration);
}

void loop() {
  
  readValue = analogRead(pinAntenna);
  Serial.println(readValue);
  if(readValue >= 1) { 
    readValue = constrain(readValue, 1, maxConstraint);
    readValue = map(readValue, 1, maxConstraint, 1, maxDisplayed);
    displayNumber(readValue);
    
  }
  else {
    displayNumber(readValue);
  }

  delay(readingInterval);
 
}
