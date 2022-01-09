#include <Servo.h>
int servoPin = 9;

int angle = 0;

Servo myServo;

void setup() {
  myServo.attach(servoPin);
}

void loop() {
  
  for (angle = 0; angle < 180; angle++) {
    myServo.write(angle);
    delay(15);
  }
  
  for (angle = 180; angle > 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
