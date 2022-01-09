int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;

int motorSpeed = 0;
bool reverse = true;


void setup() {
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

}

void loop() {
  setMotor(motorSpeed, reverse);

}

void setMotor(int motorSpeed, bool reverse) {
  analogWrite(enablePin, motorSpeed);
  digitalWrite(in1Pin, reverse);
  digitalWrite(in2Pin, !reverse);
}
