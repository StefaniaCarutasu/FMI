const int pushButton = 2;
bool buttonStateCurrent = LOW;
bool buttonStateLast = LOW;

const int ledPin = 12;
bool ledState = LOW;

int counter = 0;

bool reading = LOW;
bool lastReading = LOW;

int lastDebounceTimer = 0;
const int debounceInterval = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  /* LEDUL STA APRINS CAT E BUTONUL APRINS
   * buttonState = digitalRead(pushButton);
   * ledState = !buttonState;

   * digitalWrite(ledPin, ledState);
   * Serial.println(buttonState);
  */
  
//  //Apasarea de buton aprinde si stinge butonul
//  buttonStateCurrent = digitalRead(pushButton);
//  if(buttonStateCurrent != buttonStateLast && buttonStateCurrent == LOW) {
//    ledState = !ledState;
//  }
// 
//  digitalWrite(ledPin, ledState);
//  buttonStateLast = buttonStateCurrent;

  reading = digitalRead(pushButton);
 
  if(reading != lastReading) {
    lastDebounceTimer = millis(); 
  }

  if(millis() - lastDebounceTimer > debounceInterval) {
    if(reading != buttonStateCurrent) {
      buttonStateCurrent = reading;
      if(buttonStateCurrent == HIGH){
        ledState = !ledState;
      }
    }
    
    digitalWrite(ledPin, ledState);
  }

  
  lastReading = reading;
  
}
