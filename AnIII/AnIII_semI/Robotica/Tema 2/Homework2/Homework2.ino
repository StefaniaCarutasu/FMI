//button
const int pushButton = 2; 
bool reading = LOW;
bool lastReading = LOW;

bool currentButtonState = LOW;
bool lastButtonState = LOW;


//leds for people semaphore 
const int peopleLedPinGreen = 13;
const int peopleLedPinRed = 12;

bool peopleGreenState = LOW;
bool peopleRedState = HIGH;


//leds for cars semaphore
const int carsLedPinGreen = 8;
const int carsLedPinYellow = 7;
const int carsLedPinRed = 4;

bool carsGreenState = HIGH;
bool carsYellowState = LOW;
bool carsRedState = LOW;


//buzzer
const int buzzerPin = 11;
int buzzerTone = 5500;
int toneDuration = 10;

//time constants
const int greenToYellowCars = 10000;
const int yellowToRedCars = 13000;
const int buzzingInterval = 13000;
const int startBlinkInterval = 26000;
const int greenToRedInterval = 31000;
const int blinkingInterval = 500;

const int buzzingIntervalShort = 100;
const int buzzingIntervalLong = 500;


//timers
unsigned int buttonTimer = 0;
unsigned int carsTimer = 0;
unsigned int peopleTimer = 0;
unsigned int blinkingTimer = 0;
unsigned int buzzingTimerLong = 0;
unsigned int buzzingTimerShort = 0;

int lastDebounceTime = 0;
const int debounceInterval = 50;

bool loopStarted = false;

void setup() {
  // put your setup code here, to run once:
  
  //mode for the button
  pinMode(pushButton, INPUT_PULLUP);

  //modes for leds
  pinMode(peopleLedPinGreen, OUTPUT);
  pinMode(peopleLedPinRed, OUTPUT);
  
  pinMode(carsLedPinGreen, OUTPUT);
  pinMode(carsLedPinYellow, OUTPUT);
  pinMode(carsLedPinRed, OUTPUT);

  //mode for the buzzer
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
}


void writeStates(){
  //people
  digitalWrite(peopleLedPinGreen, peopleGreenState);
  digitalWrite(peopleLedPinRed, peopleRedState);

  //cars
  digitalWrite(carsLedPinGreen, carsGreenState);
  digitalWrite(carsLedPinYellow, carsYellowState);
  digitalWrite(carsLedPinRed, carsRedState);
}

void peopleSemaphoreLoop() {
  
  //it is time to make it red for people and green for cars
  if(millis() - peopleTimer > greenToRedInterval) {
    carsGreenState = HIGH;
    peopleRedState = HIGH;

    carsRedState = LOW;
    peopleGreenState = LOW;

    loopStarted = false;
  }

  else if(millis() - peopleTimer > startBlinkInterval) {
    
    if(millis() -  blinkingTimer > blinkingInterval){
      Serial.println(millis() - peopleTimer - blinkingTimer);
      peopleGreenState = !peopleGreenState;
      blinkingTimer = millis();
    }

    if(millis() - buzzingTimerLong > buzzingIntervalShort) {
      tone(buzzerPin, buzzerTone, toneDuration);
      buzzingTimerLong = millis();
    }
  }
   else if(millis() - peopleTimer > buzzingInterval) {
    if(millis() - buzzingTimerShort > buzzingIntervalLong) {
      tone(buzzerPin, buzzerTone, toneDuration);
      buzzingTimerShort = millis();
    }
    //tone(buzzerPin, buzzerTone, toneDuration);
    //buzzingTimer = millis();
  }
}

void carsSemaphoreLoop() {

  if(carsGreenState == HIGH && carsYellowState == LOW) {
     carsGreenState = LOW;
     carsYellowState = HIGH;
  }  

  if(millis() - carsTimer > yellowToRedCars) {
    if(carsYellowState == HIGH && carsRedState == LOW) {
      carsYellowState = LOW;
      carsRedState = HIGH; 
      
      peopleGreenState = HIGH;
      peopleRedState = LOW;
    }
    peopleSemaphoreLoop();
  }
  
}

void checkButton() {

  reading = digitalRead(pushButton);
 
  if(reading != lastReading) {
    lastDebounceTime = millis(); 
  }

  if(millis() - lastDebounceTime > debounceInterval) {
    if(reading != currentButtonState) {
      currentButtonState = reading;
      if(currentButtonState == LOW && loopStarted == false){
        buttonTimer = millis();   
        carsTimer = millis();   
        peopleTimer = millis(); 
        loopStarted = true; 
      } 
    }
  }

  if (millis() - buttonTimer > greenToYellowCars && loopStarted) {
      carsSemaphoreLoop();
  }

  
  lastReading = reading;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  writeStates();
  
  checkButton();

}
