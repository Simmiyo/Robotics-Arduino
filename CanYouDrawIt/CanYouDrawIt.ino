#include "LedControl.h"
#include <EEPROM.h>
#include "EEPROMAnything.h"
#include <LiquidCrystal.h>

LedControl lc = LedControl(12,11,10,2);

int level = 1;
int contrast = 60;

int indexMenu = 0;
int menuPage = 1;
int pagesNo = 6;
unsigned int indexSettings = 1;
unsigned long score = 0;
unsigned int startingLevelValue = 1;
unsigned int infoIndex = 0;
 
const unsigned int cardAlpha = 26;
const char alpha[cardAlpha] = {'A','B','C','D','E','F','G','H','I',
  'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const unsigned int cardName = 3;
unsigned int letterNo = 0;
unsigned int Name[cardName] = {0, 0, 0};
char playerName[cardName + 1];
struct player {
  unsigned long score;
  char Name[cardName + 1];
}; 
player currentPlayer;
player highScorePlayer1;
player highScorePlayer2;
player highScorePlayer3;
const byte numberOfHighScorePlayers = 3;
int highScoreLevel = 0;
byte highScorePageIndex = 0;
int playerSize = sizeof(player);

unsigned long prevAnimation = 0;
int animDuration = 3000;
byte animationState = 0;

const int maxPointsNo = 64;
int pointsNo;
int randRow;
int randCol;

const int RS = 13;
const int E = 9;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
const int V0 = 6;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

const int pinX = A0;
const int pinY = A1;
const int pinSW = 8;
int xValue = 0;
int yValue = 0;
int swValue = 1;
byte joyMovedX = 0;
byte joyMovedY = 0;
const int minThreshold = 150;
const int maxThreshold = 950;

int currentRow = 7;
int currentCol = 7;
int previousRow = 0;
int previousCol = 0;

byte buttonPressed = 1;
byte previousPressed = 1;
unsigned long prevSwChange = 0;
unsigned int debounceDuration = 60;
byte buttonPressedGame = 1;
byte previousPressedGame = 1;
unsigned long prevSwChangeGame = 0;
unsigned int debounceDurationGame = 60;

const byte matrixSize = 8;

unsigned long previousBlink = 0;
int blinkInterval = 35;
byte blinkState = 1;
unsigned long previousBlinkNp = 0;
int blinkIntervalNp = 60;
byte blinkStateNp = 1;
unsigned int lives = 3;

unsigned long previousTime = 0;
unsigned int catchTime = 10000;
const unsigned int maxCatch = 10000;
const unsigned int minCatch = 1500;
unsigned int changeColInterval = 250;
const unsigned int maxInterval = 250;
const unsigned int minInterval = 50; 

byte animationMatrix1[matrixSize][matrixSize] = {
  {1, 0, 0, 0, 1, 0, 0, 0},
  {0, 1, 0, 1, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 0, 1, 0},
  {1, 1, 1, 0, 1, 0, 1, 0},
  {0, 0, 1, 1, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1, 0, 0},
  {1, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0} 
};

byte animationMatrix2[matrixSize][matrixSize] = {
  {0, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0} 
};

byte drawingMatrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
}; 

byte displayedMatrix1[matrixSize][matrixSize] = {
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {1, 0, 1, 0, 0, 1, 0, 1},
  {0, 1, 0, 1, 1, 0, 1, 0} 
};

byte displayedMatrix2[matrixSize][matrixSize] = {
  {0, 1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 0, 0, 1, 0},
  {1, 1, 1, 1, 0, 1, 1, 0},
  {0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1} 
};

byte displayedMatrix3[matrixSize][matrixSize] = {
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {1, 1, 0, 0, 0, 0, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0} 
};

byte displayedMatrix4[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0} 
};


byte displayedMatrix5[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 1, 1, 0, 0},
  {1, 1, 0, 1, 0, 0, 1, 0},
  {1, 0, 1, 0, 0, 0, 0, 1},
  {1, 1, 0, 1, 0, 0, 1, 0},
  {1, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0} 
};

byte displayedMatrix6[matrixSize][matrixSize] = {
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0} 
};

byte displayedMatrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0} 
};

struct points {
  byte x;
  byte y;
};

points drawnPoints[matrixSize*matrixSize] = {};
int numberOfPoints = 0;

points drawPoints[matrixSize*matrixSize] = {};
int numberOfDrawPoints = 0;

points notDrawPoints[matrixSize*matrixSize] = {};
int numberOfNotDrawPoints = 0;

const int maxNumberOfFalsePoints = 4;
const int minNumberOfFalsePoints = 1;
int numberOfFalsePoints = 0;
points falsePoints[maxNumberOfFalsePoints];
points truePoint;

int falseYValue = 0;

byte checkIfDrawnPoint(int xCoord, int yCoord, int pointsNo) {
  for(int i = 0; i < pointsNo; i++) {
    if (drawnPoints[i].x == xCoord && drawnPoints[i].y == yCoord) {
      return 1;
    }
  }
  return 0;
}

byte checkIfTrueOrFalsePoints(int xCoord, int yCoord, int pointsNo) {
  if (truePoint.x == xCoord && truePoint.y == yCoord) {
    return 1;
  } else {
      for(int i = 0; i < pointsNo; i++) {
        if (falsePoints[i].x == xCoord && falsePoints[i].y == yCoord) {
          return 1;
        }
      }
  }
  return 0;
}

void moveJoystick(int xValue, int yValue) {
  previousCol = currentCol;
  previousRow = currentRow;
  if (xValue <= minThreshold && joyMovedX == false) {
    if (currentCol == 0) {
      currentCol = matrixSize - 1;
    } else {   
        currentCol--;         
    }
    joyMovedX = true;
  }
  else if (xValue >= maxThreshold && joyMovedX == false) {
      if (currentCol == matrixSize - 1) {
        currentCol = 0;
      } else {   
          currentCol++;         
      }
      joyMovedX = true;
  }
  else if (xValue < maxThreshold && xValue > minThreshold) {
    joyMovedX = false;
  }
  if (yValue >= maxThreshold && joyMovedY == false) {
    if (currentRow == matrixSize - 1) {
      currentRow = 0;
    } else {   
        currentRow++;         
    }
    joyMovedY = true;
  }
  else if (yValue <= minThreshold && joyMovedY == false) {
    if (currentRow == 0) {
      currentRow = matrixSize - 1;
    } else {   
        currentRow--;         
    }
    joyMovedY = true;
  }
  else if (yValue < maxThreshold && yValue > minThreshold) {
     joyMovedY = false;
  }
}

void displayTheMatrix(int lvl){
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      switch(lvl) {
        case 1:
          lc.setLed(0, col, row, displayedMatrix1[row][col]);
          break;
        case 2:
          lc.setLed(0, col, row, displayedMatrix2[row][col]);
          break;
        case 3:
          lc.setLed(0, col, row, displayedMatrix3[row][col]);
          break;
        case 4:
          lc.setLed(0, col, row, displayedMatrix4[row][col]);
          break;
        case 5:
          lc.setLed(0, col, row, displayedMatrix5[row][col]);
          break;
        case 6:
          lc.setLed(0, col, row, displayedMatrix6[row][col]);
          break;
        default:
          lc.setLed(0, col, row, displayedMatrix[row][col]);
          break;
        }
        lc.setLed(1, matrixSize - 1 - col, matrixSize - 1 - row, drawingMatrix[row][col]);
    }
  }
}

void cursorBlink() {
  if((millis() - previousBlink) > blinkInterval) {
    previousBlink = millis();
    blinkState = !blinkState;
  }
}

void newPointsBlink() {
  if((millis() - previousBlinkNp) > blinkIntervalNp) {
    previousBlinkNp = millis();
    blinkStateNp = !blinkStateNp;
  }
  drawingMatrix[truePoint.x][truePoint.y] = blinkStateNp;
  for (int i = 0; i < numberOfFalsePoints; i++) {
    drawingMatrix[falsePoints[i].x][falsePoints[i].y] = blinkStateNp;
  }
}

void registerPoint(int storedRow, int storedCol, points pointsRegister[], int &pointsNumber) {
  points p;
  p.x = storedRow;
  p.y = storedCol;
  pointsRegister[pointsNumber] = p;
  pointsNumber++;
}

int getDrawPoints(byte drawnMatrix[][matrixSize]) {
  points p;
  for(int row = 0; row < matrixSize; row++) {
    for(int col = 0; col < matrixSize; col++) {
       if (drawnMatrix[row][col] == 1) {
          registerPoint(row, col, drawPoints, numberOfDrawPoints);
       }
    }
  }
}

int getNotDrawPoints(byte drawnMatrix[][matrixSize]) {
  points p;
  for(int row = 0; row < matrixSize; row++) {
    for(int col = 0; col < matrixSize; col++) {
      if (drawnMatrix[row][col] == 0) {
        registerPoint(row, col, notDrawPoints, numberOfNotDrawPoints);
      }
    }
  }
}

void eliminatePoint(int Position, points arrayOfPoints[], int &pointsNumber) {
  for(int i = Position; i < pointsNumber - 1; i++) {
    arrayOfPoints[i] = arrayOfPoints[i + 1]; 
  }
  pointsNumber--;
}

points generateRandomPoint() {
  points p;
  p.x = random(matrixSize);
  p.y = random(matrixSize);
}

points generateRandomDrawPoint() {
  int i = random(numberOfDrawPoints);
  points p;
  p = drawPoints[i];
  eliminatePoint(i, drawPoints, numberOfDrawPoints);
  return p;
}

points generateRandomNotDrawPoint() {
  int i = random(numberOfNotDrawPoints);
  points p;
  p = notDrawPoints[i];
  eliminatePoint(i, notDrawPoints, numberOfNotDrawPoints);
  return p;
}

void generateFalsePoints(int number) {
  for(int i = 0; i < number; i++) {
    falsePoints[i] = generateRandomNotDrawPoint();
  }
}

void generateRandomMatrix() {
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      displayedMatrix[matrixSize][matrixSize] = 0;
    }
  }
  pointsNo = random(maxPointsNo);
  for (int i = 0; i < pointsNo; i++) {
    randRow = random(matrixSize);
    randCol = random(matrixSize);
    displayedMatrix[randRow][randCol] = 1;
  }
}

void showProgress() {
  lcd.setCursor(0,0);
  lcd.print("Level:");
  lcd.setCursor(7,0);
  lcd.print(level);
  lcd.setCursor(0,1);
  lcd.print("Score:");
  lcd.setCursor(7,1);
  lcd.print(score);
}

void newGame(int row, int col, int lvl) {
  for (int r = 0; r < matrixSize; r++) {
    for (int c = 0; c < matrixSize; c++) {
      drawingMatrix[r][c] = 0;
    }   
  }
  numberOfPoints = 0;
  numberOfDrawPoints = 0;
  numberOfNotDrawPoints = 0;
  if (lives > 0) {
      if (lvl == 1) {
        currentCol = col;
        currentRow = row;
        getDrawPoints(displayedMatrix1); 
        Serial.println(numberOfDrawPoints);
      } else if (lvl == 2) {
        int i = random(numberOfDrawPoints);
        points p = drawPoints[i];
        currentCol = p.x;
        currentRow = p.y;
        getDrawPoints(displayedMatrix2); 
      } else if (lvl == 3) {
          getDrawPoints(displayedMatrix3);
          truePoint = generateRandomDrawPoint();
          drawingMatrix[truePoint.x][truePoint.y] = 1;
          previousTime = millis();
      } else if (lvl == 4) {
          numberOfNotDrawPoints = 0;
          getDrawPoints(displayedMatrix4);
          getNotDrawPoints(displayedMatrix4);
          drawingMatrix[truePoint.x][truePoint.y] = drawingMatrix[falsePoints[0].x][falsePoints[0].y] = 0;
          truePoint = generateRandomDrawPoint();
          generateFalsePoints(1);
          drawingMatrix[truePoint.x][truePoint.y] = drawingMatrix[falsePoints[0].x][falsePoints[0].y] = 1;
          previousTime = millis();
      } else if (lvl == 5) {
          numberOfNotDrawPoints = 0;
          getNotDrawPoints(displayedMatrix5);
          numberOfDrawPoints = matrixSize * matrixSize - numberOfNotDrawPoints;
          truePoint = generateRandomNotDrawPoint();
          currentRow = truePoint.x;
          currentCol = truePoint.y;
          drawingMatrix[currentRow][currentCol] = 1;
          previousTime = millis();
      } else if (lvl == 6) {
          getDrawPoints(displayedMatrix6);
          numberOfPoints = 0;
          previousTime = millis();
      } else {
          if (lvl % 2 == 1) {
            catchTime = maxCatch - 10 * level;
            if(catchTime < minCatch) {
              catchTime = minCatch;
            }
            numberOfNotDrawPoints = 0;
            numberOfFalsePoints = random(minNumberOfFalsePoints, maxNumberOfFalsePoints);
            getDrawPoints(displayedMatrix);
            getNotDrawPoints(displayedMatrix);
            drawingMatrix[truePoint.x][truePoint.y] = drawingMatrix[falsePoints[0].x][falsePoints[0].y] = 0;
            truePoint = generateRandomDrawPoint();
            generateFalsePoints(numberOfFalsePoints);
            drawingMatrix[truePoint.x][truePoint.y] = 1;
            for(int i = 0; i < numberOfFalsePoints; i++) {
              drawingMatrix[falsePoints[i].x][falsePoints[i].y] = 1;
            }
            previousTime = millis();
          } else {
              getDrawPoints(displayedMatrix);
              numberOfPoints = 0;
              previousTime = millis();
          }
      }
      level = lvl;
  } else {
       player highScorePlayers[numberOfHighScorePlayers];
                    for(int i = 0; i < numberOfHighScorePlayers; i++) {
                        if (i == 0) {
                           EEPROM_readAnything(0, highScorePlayers[i]);
                        } else {
                           EEPROM_readAnything(i * playerSize + 1, highScorePlayers[i]);
                        }
                        Serial.println(score);
                        Serial.println(highScorePlayers[i].score);
                        if (highScorePlayers[i].score < score) {
                           strcpy(currentPlayer.Name, playerName);
                           currentPlayer.score = score;
                           if (i == 0) {
                                EEPROM_writeAnything(0, currentPlayer);
                           } else {
                                EEPROM_writeAnything(i * playerSize + 1, currentPlayer); 
                           }
                           highScoreLevel = i + 1;
                           break;
                        }
                     }
                     for(int i = highScoreLevel; i < numberOfHighScorePlayers; i++) {
                         EEPROM_readAnything(i * playerSize + 1, highScorePlayers[i]);
                         EEPROM_writeAnything(i * playerSize + 1, highScorePlayers[i - 1]);
                     }
                     score = 0;
                     level = 1;
  }
}

void setup() {
  level = 1;
  score = 0;
  newGame(0,0,level);
  lc.shutdown(0,false);
  lc.setIntensity(0,2);
  lc.clearDisplay(0);
  lc.shutdown(1,false);
  lc.setIntensity(1,2);
  lc.clearDisplay(1);
  lcd.begin(16, 2);
  randomSeed(analogRead(A5));
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(V0, OUTPUT);
  analogWrite(V0, contrast);
  Serial.begin(9600);
  previousTime = millis();
  generateRandomMatrix();
  for(int i = 0; i < cardName; ++i) {
    playerName[i] = 'A';
  }
  strcpy(currentPlayer.Name, playerName);
  //currentPlayer.score = 3;
  //EEPROM_writeAnything(0, currentPlayer);
  //currentPlayer.score = 2;
  //EEPROM_writeAnything(playerSize + 1, currentPlayer);
  //currentPlayer.score = 1;
  //EEPROM_writeAnything(2 * playerSize+ 1, currentPlayer);
}

void loop() {
  analogWrite(V0, contrast);
  swValue = digitalRead(pinSW);
  if (swValue != previousPressed) {
    prevSwChange = millis();
  }
  if ((millis() - prevSwChange) > debounceDuration && swValue != buttonPressed) {
    buttonPressed = swValue;
  }
  previousPressed = swValue;
  if (indexMenu == 0) {
    if ((millis() - prevAnimation) > animDuration) {
      animationState = !animationState;
      prevAnimation = millis();
    }
    if (animationState == 0) {
      for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
          lc.setLed(0, col, row, animationMatrix1[row][col]);
          lc.setLed(1, matrixSize - 1 - col, matrixSize - 1 - row, animationMatrix1[row][col]);
        }
      }
    } else {
        for (int row = 0; row < matrixSize; row++) {
          for (int col = 0; col < matrixSize; col++) {
            lc.setLed(0, col, row, animationMatrix2[row][col]);
            lc.setLed(1, matrixSize - 1 - col, matrixSize - 1 - row, animationMatrix2[row][col]);
          }
        }
    }
    lcd.setCursor(0,0);
    lcd.print("Can you draw it?");
    lcd.setCursor(4,1);
    lcd.print("> Play");
    if (buttonPressed == 0 && indexMenu == 0) {
      indexMenu = 1;
      previousPressed = 1;
      buttonPressed = 1;
    }
  } else if (indexMenu == 1) {
      delay(20);
      xValue = analogRead(pinX);
      switch(menuPage) {
        case 1:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("> Start Game");
          lcd.setCursor(2,1);
          lcd.print("High Score");
          if (xValue < minThreshold && joyMovedX == false) {
            menuPage++;
            joyMovedX = true;
          }
          if (xValue > maxThreshold && joyMovedX == false) {
            menuPage = 8;
            joyMovedX = true;
          }  
          if (xValue > minThreshold && xValue < maxThreshold) {
            joyMovedX = false;
          }
          if(buttonPressed == 0) {
            lcd.clear();
            indexMenu = 2;
            swValue = 1;
            previousPressed = 1;
            score = 0;
            level = startingLevelValue;
            lives = 1;
            newGame(0, 0, 1);
          }
          break;
        case 2:
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("Start Game");
          lcd.setCursor(0,1);
          lcd.print("> High Score");
          if (xValue < minThreshold && joyMovedX == false) {
            menuPage++;
            joyMovedX = true;
          }
          if (xValue > maxThreshold && joyMovedX == false) {
            menuPage--;
            joyMovedX = true;
          }  
          if (xValue > minThreshold && xValue < maxThreshold) {
            joyMovedX = false;
          }
          if(buttonPressed == 0) {
            lcd.clear();
            indexMenu = 3;
            buttonPressed = 1;
            highScorePageIndex = 0;
            previousPressed = 1;
          }
          break;
        case 3:
           lcd.clear();
           lcd.setCursor(2,0);
           lcd.print("High Score");
           lcd.setCursor(0,1);
           lcd.print("> Settings");
           if (xValue < minThreshold && joyMovedX == false) {
             menuPage = menuPage + 2;
             joyMovedX = true;
           }
           if (xValue > maxThreshold && joyMovedX == false) {
             menuPage++;
             joyMovedX = true;
           }  
           if (xValue > minThreshold && xValue < maxThreshold) {
             joyMovedX = false;
           }
           if(buttonPressed == 0) {
             lcd.clear();
             indexMenu = 4;
             buttonPressed = 1;
             previousPressed = 1;
             indexSettings = 1;
           }
           break;
         case 4:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("> High Score");
            lcd.setCursor(2,1);
            lcd.print("Settings");
            if (xValue < minThreshold && joyMovedX == false) {
              menuPage--;
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              menuPage = menuPage - 3;
              joyMovedX = true;
            }  
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            if(buttonPressed == 0) {
              lcd.clear();
              indexMenu = 3;
              highScorePageIndex = 0;
              buttonPressed = 1;
              previousPressed = 1;
            }
            break;
          case 5:
            lcd.clear();
            lcd.setCursor(2,0);
            lcd.print("Settings");
            lcd.setCursor(0,1);
            lcd.print("> Info");
            if (xValue < minThreshold && joyMovedX == false) {
              menuPage += 3;
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              menuPage++;
              joyMovedX = true;
            }  
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            if(buttonPressed == 0) {
              lcd.clear();
              indexMenu = 5;
              infoIndex = 0;
              buttonPressed = 1;
              previousPressed = 1;
            }
            break;
           case 6:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("> Settings");
            lcd.setCursor(2,1);
            lcd.print("Info");
            if (xValue < minThreshold && joyMovedX == false) {
              menuPage--;
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              menuPage -= 2;
              joyMovedX = true;
            }  
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            if(buttonPressed == 0) {
              lcd.clear();
              indexMenu = 4;
              buttonPressed = 1;
              previousPressed = 1;
              indexSettings = 1;
            }
            break;
            case 7:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("> Info");
            lcd.setCursor(2,1);
            lcd.print("exit");
            if (xValue < minThreshold && joyMovedX == false) {
              menuPage++;
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              menuPage--;
              joyMovedX = true;
            }  
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            if(buttonPressed == 0) {
              lcd.clear();
              indexMenu = 5;
              infoIndex = 0;
              buttonPressed = 1;
              previousPressed = 1;
              indexSettings = 1;
            }
            break;
            case 8:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("  Info");
            lcd.setCursor(2,1);
            lcd.print(">exit");
            if (xValue < minThreshold && joyMovedX == false) {
              menuPage = 1;
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              menuPage--;
              joyMovedX = true;
            }  
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            if(buttonPressed == 0) {
              lcd.clear();
              indexMenu = 0;
              buttonPressed = 1;
              previousPressed = 1;
              indexSettings = 1;
            }
            break;
        }
      }else if (indexMenu == 2) {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  swValue = digitalRead(pinSW);
  switch(level) {
    case 1:
      moveJoystick(xValue, yValue);
      if (swValue != previousPressedGame) {
        prevSwChangeGame = millis();
      }
      cursorBlink();
      if (!checkIfDrawnPoint(previousRow, previousCol, numberOfPoints)) {
        drawingMatrix[previousRow][previousCol] = 0;
      } else {
        drawingMatrix[previousRow][previousCol] = 1;
      }
      drawingMatrix[currentRow][currentCol] = blinkState;
      if ((millis() - prevSwChangeGame) > debounceDurationGame) {
        if (swValue != buttonPressedGame) {
          buttonPressedGame = swValue;
          if (buttonPressedGame == LOW) {
            if (displayedMatrix1[currentRow][currentCol] == 0) {
              //Serial.println(score);   
              lives--;
              newGame(0,0,1);
              Serial.print("GAME OVER!");
              if(lives == 0) {
                  Serial.println(score);            
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
            } else {
                drawingMatrix[currentRow][currentCol] = 1;
                registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
                score = score + 10 * level;
                if (numberOfPoints == numberOfDrawPoints) {
                  newGame(0,0,2);
                  Serial.println("GAME WON!");
                  lives++;
                }
            }
          }
        }
      }
      previousPressedGame = swValue;
      break;
    case 2:
      moveJoystick(xValue, yValue);
      if (displayedMatrix2[currentRow][currentCol] == 0) {
        newGame(previousRow, previousCol, 2);
        Serial.println("GAME OVER!");
        lives--; 
        if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
      } else {
        cursorBlink();
        if (checkIfDrawnPoint(previousRow, previousCol, numberOfPoints)) {
           drawingMatrix[previousRow][previousCol] = 1;
        } else {
           registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
           score = score + 10 * level;
           if (numberOfPoints == numberOfDrawPoints) {
             newGame(previousRow, previousCol, 3);
             Serial.println("GAME WON!");
             lives++;
          }
        }
        drawingMatrix[previousRow][previousCol] = 1;
        drawingMatrix[currentRow][currentCol] = blinkState;
      }
      break;
    case 3:
      if ((millis() - previousTime) <= catchTime) {
        moveJoystick(xValue, yValue);  
        if (swValue != previousPressedGame) {
          prevSwChangeGame = millis();
        }
        cursorBlink();
        if (!checkIfDrawnPoint(previousRow, previousCol, numberOfPoints) && !checkIfTrueOrFalsePoints(previousRow, previousCol, numberOfFalsePoints)) {
          drawingMatrix[previousRow][previousCol] = 0;
        } else {
            drawingMatrix[previousRow][previousCol] = 1;
        }
        drawingMatrix[currentRow][currentCol] = blinkState;
        if ((millis() - prevSwChangeGame) > debounceDurationGame) {
          if (swValue != buttonPressedGame) {
            buttonPressedGame = swValue;
            if (buttonPressedGame == LOW) {
              if (currentRow != truePoint.x || currentCol != truePoint.y) {
                newGame(0, 0, 3);
                Serial.println("GAME OVER!");
                lives--;
                if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
              } else {
                  if (numberOfDrawPoints > 0) {
                    drawingMatrix[currentRow][currentCol] = 1;
                    registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
                    score = score + 10 * level;
                    truePoint = generateRandomDrawPoint();
                    drawingMatrix[truePoint.x][truePoint.y] = 1;
                    previousTime = millis();
                    } else {
                        newGame(0, 0, 4);
                        Serial.println("GAME WON!");
                        lives++;
                    }                    
              }
            }
          }
        }
        previousPressedGame = swValue;
      } else {
          newGame(0, 0, 3);
          Serial.println("GAME OVER!");
          lives--;
          if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
      }
      break;
    case 4:
      numberOfFalsePoints = 1;
      if ((millis() - previousTime) <= catchTime) {
        moveJoystick(xValue, yValue);  
        if (swValue != previousPressed) {
          prevSwChangeGame = millis();
        }
        cursorBlink();
        if (!checkIfDrawnPoint(previousRow, previousCol, numberOfPoints) && !checkIfTrueOrFalsePoints(previousRow, previousCol, numberOfFalsePoints)) {
          drawingMatrix[previousRow][previousCol] = 0;
        } else {
            drawingMatrix[previousRow][previousCol] = 1;
        }
        drawingMatrix[currentRow][currentCol] = blinkState;
        if ((millis() - prevSwChangeGame) > debounceDurationGame) {
          if (swValue != buttonPressedGame) {
            buttonPressedGame = swValue;
            if (buttonPressedGame == LOW) {
              if (currentRow != truePoint.x || currentCol != truePoint.y) {
                newGame(0, 0, 4);
                Serial.println("GAME OVER!");
                lives--;
                if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
              } else {
                  drawingMatrix[falsePoints[0].x][falsePoints[0].y] = 0;
                  if (numberOfDrawPoints > 0) {
                    drawingMatrix[currentRow][currentCol] = 1;
                    registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
                    score = score + 10 * level;
                    truePoint = generateRandomDrawPoint();
                    generateFalsePoints(numberOfFalsePoints);
                    drawingMatrix[truePoint.x][truePoint.y] = drawingMatrix[falsePoints[0].x][falsePoints[0].y] = 1;
                    previousTime = millis();
                  } else {
                      newGame(0, 0, 5);
                      Serial.println("GAME WON!");
                      lives++;
                  }
              }
            }
          }
        }
        previousPressedGame = swValue;
      } else {
          newGame(0, 0, 4);
          Serial.println("GAME OVER!");
          lives--;
          if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
      }     
      break;
    case 5:
      if ((millis() - previousTime) <= catchTime) {
        moveJoystick(xValue, yValue);  
        if (swValue != previousPressedGame) {
          prevSwChangeGame = millis();
        }
        cursorBlink();
        if (!checkIfDrawnPoint(previousRow, previousCol, numberOfPoints)) {
          drawingMatrix[previousRow][previousCol] = 0;
        } else {
          drawingMatrix[previousRow][previousCol] = 1;
        }
        drawingMatrix[currentRow][currentCol] = blinkState;
        if ((millis() - prevSwChangeGame) > debounceDurationGame) {
          if (swValue != buttonPressedGame) {
            buttonPressedGame = swValue;
            if (buttonPressedGame == LOW) {
              if (displayedMatrix5[currentRow][currentCol] == 0 || checkIfDrawnPoint(previousRow, previousCol, numberOfPoints)) {
                newGame(0, 0, 5);
                Serial.println("GAME OVER!");
                lives--;
                if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
              } else {
                  Serial.println(numberOfDrawPoints);
                  if (numberOfDrawPoints > 1) {
                    drawingMatrix[currentRow][currentCol] = 1;
                    registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
                    score = score + 10 * level;
                    numberOfDrawPoints--;
                    truePoint = generateRandomNotDrawPoint();
                    currentRow = truePoint.x;
                    currentCol = truePoint.y;
                    drawingMatrix[currentRow][currentCol] = 1;
                    previousTime = millis();
                  } else {
                      newGame(0, 0, 6);
                      drawingMatrix[currentRow][currentCol] = 1;
                      Serial.println("GAME WON!");
                      lives++;
                  }
              }
            }
          }
        }
        previousPressedGame = swValue;
      } else {
          newGame(0, 0, 5);
          Serial.println("GAME OVER!");
          lives--;
          if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
      }
      break;
    case 6:
      if ((millis() - previousTime) > changeColInterval) {
        if (falseYValue == maxThreshold) {
          falseYValue = 500;
        } else {
            falseYValue = maxThreshold;
        }
        previousTime = millis();
      }
      moveJoystick(xValue, falseYValue);
      if (swValue != previousPressedGame) {
        prevSwChangeGame = millis();
      }
      cursorBlink();
      if (!checkIfDrawnPoint(previousRow, previousCol, numberOfPoints)) {
        drawingMatrix[previousRow][previousCol] = 0;
      } else {
          drawingMatrix[previousRow][previousCol] = 1;
      }
      drawingMatrix[currentRow][currentCol] = blinkState;
      if ((millis() - prevSwChangeGame) > debounceDurationGame) {
        if (swValue != buttonPressedGame) {
          buttonPressedGame = swValue;
          if (buttonPressedGame == LOW) {
            if (displayedMatrix6[currentRow][currentCol] == 0) {
              newGame(0, 0, 6);
              Serial.println("GAME  OVER!");
              lives--;
            } else {
                drawingMatrix[currentRow][currentCol] = 1;
                registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
                score = score + 10 * level;
                if (numberOfPoints == numberOfDrawPoints) {
                  newGame(0, 0, 7);
                  Serial.println("GAME WON!");
                  lives++;
                }
            }
          }
        }
      }
      previousPressedGame = swValue;
      break;
    default:
      if (level % 2 == 1) {
        if ((millis() - previousTime) <= catchTime) {
          moveJoystick(xValue, yValue);  
          if (swValue != previousPressedGame) {
            prevSwChangeGame = millis();
          }
          cursorBlink();
          newPointsBlink();
          if (!checkIfDrawnPoint(previousRow, previousCol, numberOfPoints) && !checkIfTrueOrFalsePoints(previousRow, previousCol, numberOfFalsePoints)) {
            drawingMatrix[previousRow][previousCol] = 0;
          } else if (checkIfTrueOrFalsePoints(previousRow, previousCol, numberOfFalsePoints)) {
              drawingMatrix[previousRow][previousCol] = blinkStateNp;
          } else {
              drawingMatrix[previousRow][previousCol] = 1;
          }
          drawingMatrix[currentRow][currentCol] = blinkState;
          if ((millis() - prevSwChangeGame) > debounceDurationGame) {
            if (swValue != buttonPressedGame) {
              buttonPressedGame = swValue;
              if (buttonPressedGame == LOW) {
                if (currentRow != truePoint.x || currentCol != truePoint.y) {
                  newGame(0, 0, level);
                  Serial.println("GAME OVER!");
                  lives--;
                  if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
                } else {
                    for (int i = 0; i < numberOfFalsePoints; i++) {
                      drawingMatrix[falsePoints[i].x][falsePoints[i].y] = 0;
                    }
                    if (numberOfDrawPoints > 0) {
                      drawingMatrix[currentRow][currentCol] = 1;
                      registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
                      score = score + 10 * level;
                      truePoint = generateRandomDrawPoint();
                      generateFalsePoints(numberOfFalsePoints);
                      previousTime = millis();
                    } else {
                        generateRandomMatrix();
                        newGame(0, 0, level + 1);
                        Serial.println("GAME WON!");
                        lives++;
                    }
                }
              }
            }
          }
          previousPressedGame = swValue;
        } else {
            newGame(0, 0, level);
            Serial.println("GAME OVER!");
            lives--;
            if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
        }     
      } else {
          changeColInterval = maxInterval - 3 * level;
          if (changeColInterval < minInterval) {
            changeColInterval = minInterval;
          }
          if ((millis() - previousTime) > changeColInterval) {
            if (falseYValue == maxThreshold) {
              falseYValue = 500;
            } else {
                falseYValue = maxThreshold;
            }
            previousTime = millis();
          }
          moveJoystick(xValue, falseYValue);
          if (swValue != previousPressedGame) {
            prevSwChangeGame = millis();
          }
          cursorBlink();
          if (!checkIfDrawnPoint(previousRow, previousCol, numberOfPoints)) {
            drawingMatrix[previousRow][previousCol] = 0;
          } else {
              drawingMatrix[previousRow][previousCol] = 1;
          }
          drawingMatrix[currentRow][currentCol] = blinkState;
          if ((millis() - prevSwChangeGame) > debounceDurationGame) {
            if (swValue != buttonPressedGame) {
              buttonPressedGame = swValue;
              if (buttonPressedGame == LOW) {
                if (displayedMatrix[currentRow][currentCol] == 0) {
                  newGame(0, 0, level);
                  Serial.println("GAME  OVER!");
                  lives--;
                  if(lives == 0) {
                  indexMenu = 1;
                  previousPressed = 1;
                  buttonPressed = 1;
              }
                } else {
                    drawingMatrix[currentRow][currentCol] = 1;
                    registerPoint(currentRow, currentCol, drawnPoints, numberOfPoints);
                    score = score + 10 * level;
                    if (numberOfPoints == numberOfDrawPoints) {
                      newGame(0, 0, level + 1);
                      Serial.println("GAME WON!");
                      lives++;
                    }
                }
              }
            }
          }
          previousPressedGame = swValue;
      }
    }
  showProgress();       
  displayTheMatrix(level);
      } else if (indexMenu == 3) {
          delay(20);
           xValue = analogRead(pinX);
           Serial.println(xValue);
           if (xValue > maxThreshold && !joyMovedX) {
                 Serial.println("DA");
                 if (highScorePageIndex == 1) {
                   highScorePageIndex = 0;
                 } else {
                   highScorePageIndex = 1;
                 }
                 joyMovedX = 1;
          } else  if (xValue < minThreshold && !joyMovedX) {
                 if (highScorePageIndex == 0) {
                   highScorePageIndex = 1;
                 } else {
                   highScorePageIndex = 0;
                 }
                 joyMovedX= 1;
         } else if (xValue < maxThreshold && xValue > minThreshold && joyMovedX){
                 joyMovedX = 0;
         }
         Serial.println(highScorePageIndex);
         if (highScorePageIndex == 0) {
               EEPROM_readAnything(0, highScorePlayer1);
               EEPROM_readAnything(playerSize + 1, highScorePlayer2);
               lcd.clear();
               lcd.setCursor(2,0);
               lcd.print(highScorePlayer1.Name);
               lcd.setCursor(6,0);
               lcd.print(highScorePlayer1.score);
               lcd.setCursor(2,1);
               lcd.print(highScorePlayer2.Name);
               lcd.setCursor(6,1);
               lcd.print(highScorePlayer2.score);
         } else {
               EEPROM_readAnything(2 * playerSize + 1, highScorePlayer3);
               lcd.clear();
               lcd.setCursor(2,0);
               lcd.print(highScorePlayer3.Name);
               lcd.setCursor(6,0);
               lcd.print(highScorePlayer3.score);
               lcd.setCursor(1,1);
               lcd.print("Press to exit.");
               if (buttonPressed == 0) {
                  menuPage = 3;
                  indexMenu = 1;
                  buttonPressed = 1;
                  previousPressed = 1;             
              }
         }
          } else if (indexMenu == 4) {
            xValue = analogRead(pinX);
            yValue = analogRead(pinY);
            delay(50);
            switch(indexSettings) {
              case 1:
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("> Contrast:");
                lcd.setCursor(11,0);
                lcd.print(contrast);
                lcd.setCursor(2,1);
                lcd.print("Name:");
                lcd.setCursor(8,1);
                lcd.print(playerName);
                if (yValue < minThreshold && joyMovedY == false) {
                  contrast++;
                  joyMovedY = true;
                }
                if (yValue > maxThreshold && joyMovedY == false) {
                  contrast--;
                  joyMovedY = true;
                }
                if (yValue > minThreshold && yValue < maxThreshold) {
                  joyMovedY = false;
                }
                if (buttonPressed == 0) {
                  lcd.clear();
                  indexSettings = 2;
                  buttonPressed = 1;
                  previousPressed = 1;
                }
                break;
              case 2:
                lcd.clear();
                lcd.setCursor(2,0);
                lcd.print("Start lvl:");
                lcd.setCursor(13,0);
                lcd.print(startingLevelValue);
                lcd.setCursor(0,1);
                lcd.print("> Name:");
                lcd.setCursor(8,1);
                lcd.print(playerName);
                if (yValue > maxThreshold && joyMovedY == false) {
                  if (letterNo == cardName - 1) {
                    letterNo = 0;
                  }else{
                    letterNo++;
                  }   
                  joyMovedY = true;
                }
                if (yValue < minThreshold && joyMovedY == false) {
                  if (letterNo == 0) {
                    letterNo = cardName - 1;
                  }else{
                    letterNo--;
                  }
                  joyMovedY = true;
                }
                if (yValue < maxThreshold && yValue > minThreshold){
                  joyMovedY = false;
                }

                if (xValue < minThreshold && joyMovedX == false) {
                  if (Name[letterNo] == cardAlpha - 1) {
                    Name[letterNo] = 0;
                  }else{
                    Name[letterNo]++;
                  }
                  joyMovedX = true;
                }
                if (xValue > maxThreshold  && joyMovedX == false) {
                  if (Name[letterNo] == 0) {
                    Name[letterNo] = cardAlpha - 1;
                  }else{
                    Name[letterNo]--;
                  }
                  joyMovedX = true;
                }
                if (xValue < maxThreshold && xValue > minThreshold) {
                  joyMovedX  = false;
                }
                for(int i = 0; i < cardName; ++i) {
                    playerName[i] = alpha[Name[i]];
                }
                if (buttonPressed == 0) {
                  buttonPressed = 1;
                  previousPressed = 1;
                  indexSettings = 3;
                }
                break;
              case 3:
                lcd.clear();
                lcd.setCursor(2,0);
                lcd.print("Name:");
                lcd.setCursor(8,0);
                lcd.print(playerName);
                lcd.setCursor(0,1);
                lcd.print("> back");
                if (buttonPressed == 0) {
                  indexMenu = 1;
                  buttonPressed = 1;
                  menuPage = 3;
                  previousPressed = 1;
                }
                break;
            }
          } else if (indexMenu == 5) {
          delay(50);
          lcd.clear();
          xValue = analogRead(pinX);
          if (xValue > maxThreshold && !joyMovedX) {
                 if (infoIndex == 2) {
                   infoIndex = 0;
                 } else {
                   infoIndex++;
                 }
                 joyMovedX = 1;
         } else  if (xValue < minThreshold && !joyMovedX) {
                 if (infoIndex == 0) {
                   infoIndex = 2;
                 } else {
                   infoIndex--;
                 }
                 joyMovedX = 1;
         } else if (xValue < maxThreshold && xValue > minThreshold  && joyMovedX){
                 joyMovedX = 0;
         }
          if (infoIndex == 0) {
              lcd.setCursor(0,0);
              lcd.print("Developer:");
              lcd.setCursor(0,1);
              lcd.print("POP SIMONA");
          } else if (infoIndex == 1) {
              lcd.setCursor(0,0);
              lcd.print("github.com/Simmiyo/");
              lcd.setCursor(0,1);
              lcd.print("Robotics-Arduino");
          } else {
              lcd.setCursor(0,0);
              lcd.print("Can you draw it?");
              lcd.setCursor(0,1);
              lcd.print("Press to exit.");
              if (buttonPressed == 0) {
                  indexMenu = 1;
                  buttonPressed = 1;
                  menuPage = 5;
                  previousPressed = 1;
              }  
      }
  }
}
