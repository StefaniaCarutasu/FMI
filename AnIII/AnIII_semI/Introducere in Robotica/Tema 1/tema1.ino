
const int ledPinB = 9;
const int ledPinG = 10;
const int ledPinR = 11;

const int potPinB = A0;
const int potPinG = A1;
const int potPinR = A2;

float potValueB = 0;
float potValueG = 0;
float potValueR = 0;

float brightnessB = 0;
float brightnessG = 0;
float brightnessR = 0;

float maxAnalogValue = 1023.0;
float maxVoltageValue = 255.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(potPinB, INPUT);
  pinMode(potPinG, INPUT);
  pinMode(potPinR, INPUT);

  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValueB = analogRead(potPinB);
  potValueG = analogRead(potPinG);
  potValueR = analogRead(potPinR);

  brightnessB  =  map(potValueB,  0,  maxAnalogValue,  0,  maxVoltageValue);
  brightnessG  =  map(potValueG,  0,  maxAnalogValue,  0,  maxVoltageValue);
  brightnessR  =  map(potValueR,  0,  maxAnalogValue,  0,  maxVoltageValue);;

  analogWrite(ledPinB, brightnessB);
  analogWrite(ledPinG, brightnessG);
  analogWrite(ledPinR, brightnessR);
}
