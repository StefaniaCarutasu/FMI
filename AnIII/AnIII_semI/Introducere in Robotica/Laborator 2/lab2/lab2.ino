// #define LED_PIN 13

const int ledPin = 11; 
/*
          //ledul
int interval = 1000;            //intervalul la care se schimba starea
unsigned int lastChanged = 0;  //momentul la care a fost schimbat ultima data
//bool ledState = LOW;          //starea ledului
int brightness = 0;
int amount = 5;*/

const int potPin = A0;

float voltage = 0;

float potValue = 0;

void setup() {
  // put your setup code here, to run once:
  //pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
   * Aprinderea treptata a unui led
  brightness += amount;
  analogWrite(ledPin, brightness);
  
  unsigned int elapsedTime = millis();
  if(brightness >= 255 || brightness <= 0) {
    amount = -amount;
  }
 
  delay(30);
  unsigned int elapsedTime = millis();

  //Aprinderea si stingerea unui led la un interval de timp
  if(elapsedTime - lastChanged > interval) {
    ledState = !ledState;

    digitalWrite(ledPin, ledState);
    lastChanged = elapsedTime;
  }
   * nu este recomandata folosirea de delay
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);*/

  //Citirea valorii de la potentiometru
  potValue = analogRead(potPin);
  voltage = potValue * 5.0 / 1023.0;
  Serial.println(voltage);
  potValue = potValue / 4;
  analogWrite(ledPin, potValue);
  
}
