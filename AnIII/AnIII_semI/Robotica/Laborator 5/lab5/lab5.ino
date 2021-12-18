// Define Connections to 74HC595

// ST_CP
const int latchPin = 11;
// SH_CP
const int clockPin = 10;
// DS
const int dataPin = 12;

int digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};


const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

int segmentDigits[] = {
  segD1, segD2, segD3, segD4
};
  
const int segmentsCount = 4;

boolean registers[8];

void setup ()
{
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  
  for (int i = 0; i < segmentsCount; i++) {
    pinMode(segmentDigits[i], OUTPUT);
  }
  
  // put your main code here, to run repeatedly:
  digitalWrite(segmentDigits[0], LOW);
  digitalWrite(segmentDigits[1], LOW);
  digitalWrite(segmentDigits[2], LOW);
  digitalWrite(segmentDigits[3], LOW);
  Serial.begin(9600);
}
void loop()
{
  // Count from 0 to 15
  for (int num = 0; num < 10; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);

    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, digitArray[num]);
    Serial.println(num);
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);

    delay(1000);
  }
}
