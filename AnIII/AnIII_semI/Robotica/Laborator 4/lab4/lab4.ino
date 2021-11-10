//const int pinA = 2;
//const int pinB = 3;
//const int pinC = 4;
//const int pinD = 5;
//const int pinE = 6;
//const int pinF = 7;
//const int pinG = 8;
//const int pinDP = 9;
//
//const int segSize = 8;
//int index = 0;
//int state = HIGH;
//
//int segments[segSize] = {
//  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
//};
//
//
//
//
//void setup() {
//  // put your setup code here, to run once:
//   // initialize all the pins
//  for (int i = 0; i < segSize; i++) {
//    pinMode(segments[i], OUTPUT);
//  }
//
//  Serial.begin(9600);
//
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
////  //aprins 1
////  digitalWrite(pinE, HIGH);
////  digitalWrite(pinF, HIGH);
////
////  delay(3000);
////  
////  digitalWrite(pinE, LOW);
////  digitalWrite(pinF, LOW);
////
////  digitalWrite(pinA, HIGH);
////  digitalWrite(pinB, HIGH);
////  digitalWrite(pinC, HIGH);
////
////  delay(3000);
////
////  digitalWrite(pinA, LOW);
////  digitalWrite(pinB, LOW);
////  digitalWrite(pinC, LOW);
//
//  digitalWrite(segments[index], state);
//  delay(500);
//  index++;
//  if (index  >= segSize) {
//    index = 0;
//    state = !state;
//  }
//
//}

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

bool dpState = LOW;
int index = 0;


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
}

void loop() {
  // turn all the pins on in order. It is a good exercise to see if you connected the wires properly
  displayNumber(index, dpState);
  index++;

  if(index > 9) {
    dpState = !dpState;
    index = 0;
  }
  delay(500);
}
