// declare all the joystick pins
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// joystick variables
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int minThreshold= 400;
int maxThreshold= 600;


const int dataPin = 12; //DS
const int latchPin = 11; //STCP
const int clockPin = 10; //SHCP

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int displayCount = 4;
int currentDisplay = displayCount - 1;

int digitArray[11] = {
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
  B00000001  // DP 
};

// the values displayed on the display
int valuesToDisplay[] = {
  0, 0, 0, 0
};

// variable used to lock the display currently in use
bool lockDisplay = false;

bool timerStarted = false;
const int blinkInterval = 500;
unsigned long int blinkTimer = 0;

// timers for the button
const int debounceInterval = 200;
unsigned long lastDebounceTime = 0;


void setup() {
  
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), checkSw, FALLING);

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (timerStarted == false) {
    blinkTimer = millis(); 
    timerStarted = !timerStarted;
  }
  
  writeNumber();
  
  readJoystick();

  if (lockDisplay) {
    checkYValues();
  }
  else {
    checkXValues();
  } 
}

void readJoystick() {
  yValue = analogRead(pinY);  
  xValue = analogRead(pinX);
}

void checkSw() {
  // trying to eliminate the possible noise by waiting a few miliseconds before doing something
  if (millis() - lastDebounceTime > debounceInterval) {
    lockDisplay = !lockDisplay;
  }
  
  lastDebounceTime = millis();
}

// function that helps with changing between the displays
void checkXValues() {
  if(xValue > maxThreshold && joyMoved == false) {
    joyMoved = true; 
    currentDisplay--;
    
    if(currentDisplay < 0) {
      currentDisplay = 3;
    }    
  }

  if(xValue < minThreshold && joyMoved == false) {
    joyMoved = true; 
    currentDisplay++;
    
    if(currentDisplay > 3) {
      currentDisplay = 0;
    }    
  }

  if (minThreshold <= xValue && xValue <= maxThreshold) {
  joyMoved = false;
 }

}

// function that helps with changing the digit on the display
void checkYValues() {
  if(yValue > maxThreshold && joyMoved == false) {
    joyMoved = true; 
    valuesToDisplay[currentDisplay]--;
    
    if(valuesToDisplay[currentDisplay] < 0) {
      valuesToDisplay[currentDisplay] = 9;
    }    
  }

  if(yValue < minThreshold && joyMoved == false) {
    joyMoved = true; 
    valuesToDisplay[currentDisplay]++;
    
    if(valuesToDisplay[currentDisplay] > 9) {
      valuesToDisplay[currentDisplay] = 0;
    }    
  }

  if (minThreshold <= yValue && yValue <= maxThreshold) {
    joyMoved = false;
 }

}

void writeNumber() {
  int digit;
  int displayDigit = 0;
  
  for (int i = 0; i < 4; i++) {
    digit = valuesToDisplay[i];
    displayDigit = i;
    
    showDigit(displayDigit); 

      
    if (displayDigit == currentDisplay) {
      // if the display is locked, the point doesn't blink
      if (!lockDisplay) {
        // show a blinking decimal point for the current display
        if(millis() - blinkTimer > blinkInterval) {
          writeReg(digitArray[digit] + 1);
          blinkTimer = millis();
        }
        else {
           writeReg(digitArray[digit]);      
        }
      }
      else {
        writeReg(digitArray[digit] + 1);
      }
      
    }
    else {
       writeReg(digitArray[digit]);
    }
   
    delay(5);
  }
    
}

void showDigit(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeReg(int digit) {
  //STCP in LOW
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  
  digitalWrite(latchPin, HIGH);
}
