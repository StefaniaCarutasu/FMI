#include "system_states.h";
#include "joystick_variables.h";
#include "lcd_variables.h";
#include "matrix_variables.h";
#include "menu_variables.h";
#include "game_variables.h";

#include "highscore.h";
#include "buzzer_variables.h"

void setup() {
  //Serial.begin(9600);
  pinMode(V0, OUTPUT);

  //EEPROM.update(lcd_contrast_address, 50);
  analogWrite(V0, EEPROM.read(lcd_contrast_address));

  pinMode(A, OUTPUT);
  analogWrite(A,  EEPROM.read(lcd_brightness_address));

  lcd.createChar(0, downArrowByte);
  lcd.createChar(1, upArrowByte);
  lcd.createChar(2, rightArrowByte);

  lcd.begin(16, 2);

  // setup matrix
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, EEPROM.read(matrix_brightness_address)); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen

  // joystick setup
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), handleInterrupt, FALLING);

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  noTone(buzzerPin);
  playMusic = EEPROM.read(musicChoiceAddress);

  getHighScores();

}

void loop() {
  readJoystick();

  if (SYSTEM_STATE == OPENING_SCREEN) {
    displayGreeting();
  }
  else if (SYSTEM_STATE == MENU_SCREEN) {
    if (playMusic) {
      if (millis() - lastTone > toneInterval) {
        if (note == songLength) {
          note = 0;
        }
        playMelody();
        lastTone = millis();
      }
    }

    switchMenues();
  }
  else if (SYSTEM_STATE == START_GAME_SCREEN) {
    displayStartGameMessage();
    initialliseGame();
  }
  else if (SYSTEM_STATE == IN_GAME_SCREEN) {
    gameLogic();
  }
  else if (SYSTEM_STATE == GAME_WON_SCREEN) {
    finishedGameScreen(gameWonMessage);
  }
  else if (SYSTEM_STATE == GAME_LOST_SCREEN) {
    playDeathPitch();
    displayXAnimation();
    finishedGameScreen(gameLostMessage);
  }
  else if (SYSTEM_STATE == NAME_UPDATE_SCREEN) {
    navigateName();
  }
}

void readJoystick() {
  yValue = analogRead(pinY);
  xValue = analogRead(pinX);
}

void handleInterrupt() {
  unsigned long long current = millis();
  if (current - lastDebounceTime > debounceInterval) {
    lastDebounceTime = current;
    checkSw();
  }
}

void checkSw() {
  if (SYSTEM_STATE == MENU_SCREEN ) {
    if (lastDisplayedMenu == "LCD Constrast") {
      setLCDContrast(currentItem);
    }
    else if (lastDisplayedMenu == "LCD Bright.") {
      setLCDBrightness(currentItem);
    }
    else if (lastDisplayedMenu == "Mat. Bright.") {
      setMatrixBrightness(currentItem);
    }
    if (currentItem == "Reset Scores") {
      resetScores();
    }
    else if (currentItem == "Sound Off") {
      playMusic = 0;
      settings[4] = "Sound On";
      EEPROM.update(musicChoiceAddress, playMusic);
    }
    else if (currentItem == "Sound On") {
      playMusic = 1;
      settings[4] = "Sound Off";
      EEPROM.update(musicChoiceAddress, playMusic);
    }
    lcd.clear();
    lastDisplayedMenu = currentMenuToDisplay;
    currentMenuToDisplay = currentItem;
    changedMenu = !changedMenu;
    resetMenuVariables();
  }
  else if (SYSTEM_STATE == NAME_UPDATE_SCREEN) {
    if (currentRow == 0) {
      lockedLetter = !lockedLetter;
      currentLetter = playerName[currentLetterPosition];
    }
    else {
      setName();
    }
  }
}

void displayGreeting() {
  displayInitialAnimation();
  int initialPos;
  initialPos = (displayCols - sizeof(greetingMessage)) / 2;
  lcd.setCursor(initialPos, 0);
  lcd.print(greetingMessage);
  delay(5000);
  lcd.clear();

  SYSTEM_STATE = MENU_SCREEN;
}

void resetMenuVariables() {
  currentMenuItem = 0;
  currentRow = 0;
  displayedItems[0] = 0;
  displayedItems[1] = 1;
}

String scrollLCDLeft(String toBeDisplayed) {
  String result;
  String StrProcess = toBeDisplayed;
  //String StrProcess = "              " + toBeDisplayed + "               ";
  result = StrProcess.substring(L1, L11);
  L1++;
  L11++;
  if (L1 > StrProcess.length()) {
    L1 = 14;
    L11 = 0;
  }

  return result;
}

void displayStartGameMessage() {
  lcd.clear();
  int initialPos;
  initialPos = (displayCols - sizeof(gameStartedMessage)) / 2;
  lcd.setCursor(initialPos, 0);
  lcd.print(gameStartedMessage);
  delay(5000);
  lcd.clear();
}

void switchMenues() {
  navigateMainMenu();
  if (currentMenuToDisplay == "High Scores") {
    // dispay the high scores menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }
    displayMenu(scores);
  }
  else if (currentMenuToDisplay == "Settings") {
    // dispay the settings menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }
    displayMenu(settings);
  }
  else if (currentMenuToDisplay == "About") {
    // dispay the about menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }
    displayMenu(about);
  }
  else if (currentMenuToDisplay == "Start Game") {
    // start the game
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      lcd.clear();
      changedMenu = !changedMenu;
    }
    SYSTEM_STATE = START_GAME_SCREEN;
  }
  else if (currentMenuToDisplay == "LCD Constrast") {
    // dispay the settings menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }
    displayMenu(contrasts);
  }
  else if (currentMenuToDisplay == "LCD Bright.") {
    // dispay the settings menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }

    displayMenu(contrasts);
  }
  else if (currentMenuToDisplay == "Mat. Bright.") {
    // dispay the settings menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }
    displayMenu(contrasts);
  }
  else if (currentMenuToDisplay == "Back") {
    // display the main menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }
    currentMenuToDisplay = "Main";
    displayMenu(mainMenuItems);
  }
  else {
    // display the main menu
    if (changedMenu) {
      lastDisplayedMenu = currentMenuToDisplay;
      changedMenu = !changedMenu;
      lcd.clear();
    }

    currentMenuToDisplay = "Main";
    displayMenu(mainMenuItems);
  }
}

void navigateMainMenu() {
  // go upwards
  if (yValue > maxThreshold && joyMoved == false) {
    lcd.clear();
    joyMoved = true;

    if (currentRow == 1) {
      currentRow = 0;
      currentMenuItem -= 1;
    }
    else {
      if (currentMenuItem != 0) {
        currentRow = 1 - currentRow;
        displayedItems[0] -= 1;
        displayedItems[1] -= 1;
      }
    }
  }

  if (yValue < minThreshold && joyMoved == false) {
    lcd.clear();
    joyMoved = true;

    if (currentRow == 0) {
      currentRow = 1;
      currentMenuItem += 1;
    }
    else {
      int noOfItems;
      if (currentMenuToDisplay == "Settings") {
        noOfItems = 6;
      }
      else {
        noOfItems = 4;
      }
      if (currentMenuItem != noOfItems - 1) {
        currentRow = 1 - currentRow;
        displayedItems[0] += 1;
        displayedItems[1] += 1;
      }
    }
  }

  if (minThreshold <= yValue && yValue <= maxThreshold) {
    joyMoved = false;
  }
}

void displayMenu(String menu[]) {
  String top = menu[displayedItems[0]];
  String bottom = menu[displayedItems[1]];
  // display the items in the menu that are indicated by the array
  lcd.setCursor(0, 0);
  if (currentRow == 0) {
    lcd.write(rightArrow);
    lcd.setCursor(1, 0);
    currentItem = top;
  }
  if (top.length() > 14) {
    lcd.print(scrollLCDLeft(top));
    delay(350);
  }
  else {
    lcd.print(top);
  }

  lcd.setCursor(0, 1);
  if (currentRow == 1) {
    lcd.write(rightArrow);
    lcd.setCursor(1, 1);
    currentItem = bottom;
  }

  if (bottom.length() > 14) {
    lcd.print(scrollLCDLeft(bottom));
    delay(350);
  }
  else {
    lcd.print(bottom);
  }
  // if i am on the last item of the menu, i display the arrow pointing upwards
  if (displayedItems[1] == 3) {
    lcd.setCursor(15, 0);
    lcd.write(upArrow);
  }
  // if i am on the first item of the menu, i display the arrow pointing downwards
  else if (displayedItems[0] == 0) {
    lcd.setCursor(15, 1);
    lcd.write(downArrow);
  }
  // i display both arrows to show the player that they can go either way
  else {
    lcd.setCursor(15, 0);
    lcd.write(upArrow);
    lcd.setCursor(15, 1);
    lcd.write(downArrow);
  }
}

void setLCDContrast(String contrast) {
  int contrastValue;

  if (contrast == "Low") {
    contrastValue = constrastValues[0];

  }
  else if (contrast == "Medium") {
    contrastValue = constrastValues[1];

  }
  else if (contrast == "High") {
    contrastValue = constrastValues[2];
  }

  analogWrite(V0, contrastValue);
  EEPROM.update(lcd_contrast_address, contrastValue);

  lcd.clear();
  currentMenuToDisplay = "Settings";
}

void setLCDBrightness(String brightness) {
  int brightnessValue;

  if (brightness == "Low") {
    brightnessValue = brightnessLCDValues[0];
  }
  else if (brightness == "Medium") {
    brightnessValue = brightnessLCDValues[1];
  }
  else if (brightness == "High") {
    brightnessValue = brightnessLCDValues[2];
  }

  analogWrite(A, brightnessValue);
  EEPROM.update(lcd_brightness_address, brightnessValue);

  lcd.clear();
  currentMenuToDisplay = "Settings";

}

void setMatrixBrightness(String brightness) {
  int brightnessValue;

  if (brightness == "Low") {
    brightnessValue = brightnessMatrixValues[0];
  }
  else if (brightness == "Medium") {
    brightnessValue = brightnessMatrixValues[1];
  }
  else if (brightness == "High") {
    brightnessValue = brightnessMatrixValues[2];
  }

  lc.setIntensity(0, brightnessMatrixValues[2]);
  EEPROM.update(matrix_brightness_address, brightnessValue);

  lcd.clear();
  currentMenuToDisplay = "Settings";
}

// game logic functions

void gameLogic() {
  //updateByteMatrix();
  displayCurrentLevel();
  if (generated == 0) {
    generateObstacle();
    generated = 1;
  }
  moveObstacle();
  moveBird();
  autoDecreaseBird();
  if (matrixChanged == true) {
    // matrix display logic
    updateMatrix();
    matrixChanged = false;
  }
}


void initialliseGame() {
  lc.clearDisplay(0);
  SYSTEM_STATE = IN_GAME_SCREEN;
  matrix[currentBirdPosition[0][0]][currentBirdPosition[0][1]] = 1;
  matrix[currentBirdPosition[1][0]][currentBirdPosition[1][1]] = 1;
  lcd.clear();
}

void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, matrix[row][col]);
    }
  }
}

void displayInitialAnimation() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, birdAnimationMatrix[row][col]);
    }
  }
}

void displayTrophyAnimation() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, trophyAnimationMatrix[row][col]);
    }
  }
}

void displayXAnimation() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, xAnimationMatrix[row][col]);
    }
  }
}

void copyBirdPosition() {
  for (int i = 0; i < maxBirdSize; i++) {
    for (int j = 0; j < maxBirdSize; j++) {
      lastBirdPosition[i][j] = currentBirdPosition[i][j];
    }
  }
}

void updateBirdMatrix() {

  matrix[lastBirdPosition[0][0]][lastBirdPosition[0][1]] = 0;
  matrix[lastBirdPosition[1][0]][lastBirdPosition[1][1]] = 0;

  matrix[currentBirdPosition[0][0]][currentBirdPosition[0][1]] = 1;
  matrix[currentBirdPosition[1][0]][currentBirdPosition[1][1]] = 1;
}

void moveBird() {
  readJoystick();

  copyBirdPosition();

  if (yValue > maxThreshold && joyMoved == false) {
    joyMoved = true;
    lastMoved = millis();
    if (currentBirdPosition[1][0] > 0) {
      birdMoved = 1;
      currentBirdPosition[1][0]--;
      currentBirdPosition[0][0]--;

      if (playMusic) {
        playMoveUpPitch();
      }
    }
  }

  if (yValue < minThreshold && joyMoved == false) {
    joyMoved = true;
    lastMoved = millis();
    if (currentBirdPosition[0][0] < matrixSize - 1) {
      birdMoved = 1;
      currentBirdPosition[1][0]++;
      currentBirdPosition[0][0]++;

      if (playMusic) {
        playMoveDownPitch();
      }
    }
  }

  if (minThreshold <= yValue && yValue <= maxThreshold) {
    joyMoved = false;
  }
  if (birdMoved == 1) {
    birdMoved = 0;
    matrixChanged = true;
    updateBirdMatrix();
  }

}

void autoDecreaseBird() {
  if (millis() - lastMoved > decreaseInterval) {
    copyBirdPosition();
    currentBirdPosition[1][0]++;
    currentBirdPosition[0][0]++;

    if (playMusic) {
      playMoveDownPitch();
    }

    if (currentBirdPosition[0][0] == 7) {
      SYSTEM_STATE = GAME_LOST_SCREEN;
    }
    lastMoved = millis();

    matrixChanged = true;
    updateBirdMatrix();
  }
}

void generateObstacle() {
  matrixChanged = true;
  obstacleColumn = 7;
  int spaceStart = random(0, 5);
  for (int i = 0; i < spaceStart; i++) {
    obstacle[i] = 1;
  }
  for (int i = spaceStart + 3; i < matrixSize; i++) {
    obstacle[i] = 1;
  }
  for (int i = 0; i < matrixSize; i++) {
    matrix[i][obstacleColumn] = obstacle[i];
  }
}


// shifts de obstacle up (shifts the space the bird can fly through)
void shiftUp() {
  int o = obstacle[0];
  if (obstacle[0] == 0) {
    o = 1;
    obstacle[3] = 1;
  }
  for (int i = 0; i < matrixSize - 2; i++) {
    obstacle[i] = obstacle[i + 1];
  }
  obstacle[matrixSize - 1] = o;
}

// shifts de obstacle down (shifts the space the bird can fly through)
void shiftDown() {
  int o = obstacle[matrixSize - 1];
  if (obstacle[matrixSize - 1] == 0) {
    o = 1;
    obstacle[4] = 1;
  }
  for (int i = matrixSize - 1; i > 1; i--) {
    obstacle[i] = obstacle[i - 1];
  }
  obstacle[0] = o;
}

void moveObstacle() {
  if (millis() - lastMovedObstacle > moveObstacleInterval) {
    // it's time to move the obstacle one column towards the bird
    matrixChanged = true;

    if (obstacleColumn == 1) {
      if (obstacle[currentBirdPosition[1][0]] == 1) {
        SYSTEM_STATE = GAME_LOST_SCREEN;
      }
      for (int i = 0; i < matrixSize; i++) {
        if (i != currentBirdPosition[1][0]) {
          matrix[i][obstacleColumn] = 0;
        }
      }
      obstacleColumn--;
      for (int i = 0; i < matrixSize; i++) {
        if (obstacleColumn != 0 && obstacleColumn != 1) {
          matrix[i][obstacleColumn] = obstacle[i];
        }
        else {
          if (i != currentBirdPosition[0][0] && i != currentBirdPosition[1][0]) {
            matrix[i][obstacleColumn] = obstacle[i];
          }
        }

      }
      if (level > 4) {
        if (level % 2) {
          if (obstacleColumn % 2) {
            shiftUp();
          }
          else {
            shiftDown();
          }
        }
        else {
          if (obstacleColumn % 2) {
            shiftDown();
          }
          else {
            shiftUp();

          }
        }

      }
    }
    else if (obstacleColumn == 0) {
      if (obstacle[currentBirdPosition[0][0]] == 1) {
        SYSTEM_STATE = GAME_LOST_SCREEN;
      }
      for (int i = 0; i < matrixSize; i++) {
        if (i != currentBirdPosition[0][0]) {
          matrix[i][obstacleColumn] = 0;
        }
      }
      obstacleColumn--;

    }
    else {
      for (int i = 0; i < matrixSize; i++) {
        matrix[i][obstacleColumn] = 0;
      }
      obstacleColumn--;
      if (obstacleColumn > -1) {
        for (int i = 0; i < matrixSize; i++) {
          if (obstacleColumn != 0 && obstacleColumn != 1) {
            matrix[i][obstacleColumn] = obstacle[i];
          }
          else {
            if (i != currentBirdPosition[0][0] && i != currentBirdPosition[1][0]) {
              matrix[i][obstacleColumn] = obstacle[i];
            }
          }

        }
        if (level > 4) {
          if (level % 2) {
            if (obstacleColumn % 2) {
              shiftUp();
            }
            else {
              shiftDown();
            }
          }
          else {
            if (obstacleColumn % 2) {
              shiftDown();
            }
            else {
              shiftUp();

            }
          }

        }

      }
      else {
        // the bird avoided the obstacle
        for (int i = 0; i < matrixSize; i++) {
          obstacle[i] = 0;
          matrix[i][obstacleColumn] = 0;
        }
        score += 1;
        if (score == 50) {
          SYSTEM_STATE = GAME_WON_SCREEN;
        }
        else if (score == changeLevelScore + 5) {
          changeLevelScore = score;
          level += 1;
          if (level <= 4) {
            moveObstacleInterval -= 100;
          }

        }
        generateObstacle();
      }
    }

    lastMovedObstacle = millis();
  }
}

void displayCurrentLevel() {
  if (score != previousScore) {
    previousScore = score;
    lcd.clear();
  }
  if (level != previousLevel) {
    previousLevel = level;
    lcd.clear();
  }
  String displayCurrentLevel = displayLevel + " " + String(level);
  lcd.setCursor(0, 0);
  lcd.print(displayCurrentLevel);

  String displayCurrentScore = displayScore + " " + String(score);
  lcd.setCursor(0, 1);
  lcd.print(displayCurrentScore);

}

void finishedGameScreen(String message) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(message);

  enterName = true;
  currentRow = 0;
  delay(5000);

  lcd.clear();

  displayEndGameStatistics();
}

void displayCongrats() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(congratulationMessage);

  lcd.setCursor(0, 1);
  lcd.print(newHighscoreMessage);

  delay(3000);

  lcd.clear();
}

void displayEndGameStatistics() {

  lcd.setCursor(0, 0);
  lcd.print(statisticsMessage);

  lcd.setCursor(0, 1);

  String statistics = displayLevel + level + "; " + displayScore + score;
  if (statistics.length() > 16) {
    lcd.print(scrollLCDLeft(statistics));
    delay(350);
  }
  else {
    lcd.print(statistics);
  }

  delay(5000);
  lcd.clear();

  int compareResult = compareScores(score);
  if ( compareResult > -1) {
    displayTrophyAnimation();
    displayCongrats();
    SYSTEM_STATE = NAME_UPDATE_SCREEN;
    enterName = true;
    currentRow = 0;
    joyMoved = false;
  }
  else {
    resetGame();
  }
}

void enterPlayerName() {

  if (changedName) {
    lcd.clear();
    changedName = false;
  }

  if (currentRow == 1) {
    lcd.setCursor(0, 1);
    lcd.write(rightArrow);
    lcd.setCursor(1, 1);
    lcd.print(setCurrentName);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print(setCurrentName);
  }

  if (currentRow == 0) {
    lcd.setCursor(0, 0);
    lcd.write(rightArrow);

    lcd.setCursor(1, 0);
    lcd.print("Name: ");
    lcd.setCursor(7, 0);
    for (int i = 0; i < 3; i++) {
      lcd.print(alphabet[playerName[i]]);
    }
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Name: ");
    lcd.setCursor(6, 0);
    for (int i = 0; i < 3; i++) {
      lcd.print(alphabet[playerName[i]]);
    }
  }
}

void navigateName() {
  if (lockedLetter) {
    // if the joystick was moved up-down
    if (yValue < minThreshold && joyMoved == false) {
      joyMoved = !joyMoved;
      currentLetter--;
      if (currentLetter < 0) {
        currentLetter = alphabetLength - 1;
      }

      playerName[currentLetterPosition] = currentLetter;

      changedName = true;
    }
    if (yValue > maxThreshold && joyMoved == false) {
      joyMoved = !joyMoved;
      currentLetter++;
      if (currentLetter == alphabetLength) {
        currentLetter = 0;
      }
      playerName[currentLetterPosition] = currentLetter;

      changedName = true;
    }

  }
  else {
    // up-down motion means changing the row
    if (yValue < minThreshold && joyMoved == false) {
      if (joyMoved == false) {
        joyMoved = !joyMoved;
      }
      if (currentRow == 0) {
        currentRow = 1;
      }
      changedName = true;
    }
    if (yValue > maxThreshold && joyMoved == false) {
      if (joyMoved == false) {
        joyMoved = !joyMoved;
      }
      if (currentRow == 1) {
        currentRow = 0;
      }
      changedName = true;
    }

    // left-right motion means change the letter updated
    if (xValue < minThreshold && joyMoved == false) {
      if (joyMoved == false) {
        joyMoved = !joyMoved;
      }
      currentLetterPosition--;

      if (currentLetterPosition < 0) {
        currentLetterPosition = 2;
      }
    }

    if (xValue > maxThreshold && joyMoved == false) {
      if (joyMoved == false) {
        joyMoved = !joyMoved;
      }

      currentLetterPosition++;

      if (currentLetterPosition == 3) {
        currentLetterPosition = 0;
      }
    }
  }

  enterPlayerName();

  if (minThreshold <= yValue && yValue <= maxThreshold) {
    joyMoved = false;
  }
}

void setName() {
  for (int i = 0; i < 3; i++) {
    newName += alphabet[playerName[i]];
  }
  int newRank = compareScores(score);
  shiftScores(newName, score, newRank);
  updateEEPROM();
  resetGame();
}

void resetGame() {

  SYSTEM_STATE = MENU_SCREEN;
  score = 0;
  previousScore = 0;
  changeLevelScore = 0;

  currentMenuToDisplay = "Main";
  lastDisplayedMenu = "Main";
  currentItem = "";

  getHighScores();

  resetMenuVariables();
  resetMatrix();
  resetObstacle();
  resetBird();
  displayInitialAnimation();
}

void resetBird() {
  currentBirdPosition[0][0] = 3;
  currentBirdPosition[0][1] = 0;

  currentBirdPosition[1][0] = 2;
  currentBirdPosition[1][1] = 1;
}

void resetObstacle() {
  obstacleColumn = 7;
  moveObstacleInterval = 1000;
  generated = 0;
  for (int i = 0; i < matrixSize; i++) {
    obstacle[i] = 0;
  }
}

void resetPlayerName() {
  for (int i = 0; i < 3; i++) {
    playerName[i] = 0;
  }

  changedName = true;

  currentLetterPosition = 0;
  currentLetter = 0;

  lockedLetter = false;
}

void resetMatrix() {
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      matrix[i][j] = 0;
    }
  }
}
