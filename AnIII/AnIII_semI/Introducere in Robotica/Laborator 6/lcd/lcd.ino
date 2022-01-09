#include<LiquidCrystal.h>
#include<EEPROM.h>

const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

const int trigPin = 9;
const int echoPin = 10;

String incomingString;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

long duration = 0;
int distance = 0;
int maxDistance = 0;
int reading = 0;

int incomingByte = 0;
char incomingChar;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello, world!");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  Serial.println(EEPROM.read(1));

  //EEPROM.update(1, 90);

}

void loop() {
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  duration = pulseIn(echoPin, HIGH);
//
//  reading = duration * 0.034 / 2;
//
//  if (reading < 50) {
//    distance = reading;
//
//    if (distance > maxDistance) {
//      maxDistance = distance;
//    }
//  }
//
////  Serial.print("Distance: ");
////  Serial.println(distance);
//
//  EEPROM.update(0, maxDistance);

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    incomingChar = (char)incomingByte;

    if (incomingChar != '\n') {
      incomingString += incomingChar;
    }
    else {
      Serial.println(incomingString);
      incomingString = "";
    }
    
//    Serial.print("Received: ");
//    Serial.println(incomingChar);  //DEC, BIN, OCT
  }


}
