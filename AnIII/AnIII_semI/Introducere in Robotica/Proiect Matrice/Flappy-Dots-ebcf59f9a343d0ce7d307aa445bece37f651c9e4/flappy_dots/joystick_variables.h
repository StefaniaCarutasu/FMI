// joystick variables
const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

int xValue = 0;
int yValue = 0;

bool joyMoved = false;

#define minThreshold 400
#define maxThreshold 700

// timers for the button
const int debounceInterval = 250;
volatile unsigned long long lastDebounceTime = 0;
