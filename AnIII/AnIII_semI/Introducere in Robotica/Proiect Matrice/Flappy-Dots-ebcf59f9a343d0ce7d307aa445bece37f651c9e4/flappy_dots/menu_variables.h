#include "messages.h";

#define Back "Back"

// Main menu items
String mainMenuItems[] = {
  "Start Game",
  "High Scores",
  "Settings",
  "About"
};

String currentMenuToDisplay = "Main";
String lastDisplayedMenu = "Main";
String currentItem = "";

int currentMenuItem = 0;
int currentRow = 0;
int displayedItems[2] = {0, 1};

bool changedMenu = false;

// Submenues items
String settings[] = {
  "LCD Constrast",
  "LCD Bright.",
  "Mat. Bright.",
  "Reset Scores",
  "Sound Off",
  Back
};

String contrasts[] = {"Low", "Medium", "High", "Back"};
int constrastValues[] = {30, 50, 70};

int brightnessLCDValues[] = {128, 140, 152};
int brightnessMatrixValues[] = {2, 5, 8};

// About menu
#define owner "Carutasu Stefania"
#define githubRepo "https://github.com/StefaniaCarutasu/Flappy-Dots"

String about[] = {
  greetingMessage,
  owner,
  githubRepo,
  Back
};
