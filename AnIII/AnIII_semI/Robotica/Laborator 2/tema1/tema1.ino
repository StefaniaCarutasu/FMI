
const int ledPin9 = 9;
const int ledPin10 = 10;
const int ledPin11 = 11;

const int potPin0 = A0;
const int potPin1 = A1;
const int potPin2 = A2;

float potValue0 = 0;
float potValue1 = 0;
float potValue2 = 0;

float brightness0 = 0;
float brightness1 = 0;
float brightness2 = 0;

float maxAnalogValue = 1023.0;
float maxVoltageValue = 255.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin0, INPUT);
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);

  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
  pinMode(ledPin11, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue0 = analogRead(potPin0);
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);

  brightness0  =  map(potValue0,  0,  maxAnalogValue,  0,  maxVoltageValue);
  brightness1  =  map(potValue1,  0,  maxAnalogValue,  0,  maxVoltageValue);
  brightness2  =  map(potValue2,  0,  maxAnalogValue,  0,  maxVoltageValue);;

  analogWrite(ledPin9, brightness0);
  analogWrite(ledPin10, brightness1);
  analogWrite(ledPin11, brightness2);
}
