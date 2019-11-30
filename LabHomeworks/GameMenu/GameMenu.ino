#include <LiquidCrystal.h>
#include <EEPROM.h>

const int RS = 12;
const int E = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
const int pinX = A0;
const int pinY = A1;
const int pinSW = 10;

byte joyMovedX = false;
byte joyMovedY = false;
const int minThreshold = 400;
const int maxThreshold = 600;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

int xValue;
int yValue;
int swValue;

int indexMenu = 0;
int menuPage = 1;
int pagesNo = 6;

unsigned long prevTime = 0;
unsigned int interval = 80;
byte prevState = 1;
byte buttonState = 1;

unsigned long beginLevelTime = 0;
unsigned long beginGameTime = 0;
unsigned int levelDuration = 5000;
unsigned int gameDuration = 10000;
unsigned int startingLevelValue = 0;
unsigned int score = 0;
unsigned int lives = 3;
byte pageIdWinGame = 1;

unsigned int indexSettings = 1;
unsigned int finalLvl = 3;
unsigned int level;

const unsigned int cardAlpha = 26;
const char alpha[cardAlpha] = {'A','B','C','D','E','F','G','H','I',
  'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const unsigned int cardName = 3;
unsigned int letterNo = 0;
unsigned int Name[cardName] = {0, 0, 0};
String playerName;
struct player {
  unsigned int score;
  String Name;
}; 
player bestPlayer;
player highScorePlayer;


void setup() {
  lcd.begin(16, 2);
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
  playerName.reserve(cardName);
  for(int i = 0; i < cardName; ++i) {
        playerName.concat('A');
  }
}

void loop() {
  swValue = digitalRead(pinSW);
  if (swValue != prevState) {
    prevTime = millis();
  }
  if ((millis() - prevTime) > interval && swValue != buttonState) {
    buttonState = swValue;
  }
  prevState = swValue;
  if (indexMenu == 0) {
    lcd.setCursor(3,0);
    lcd.print("Main Menu:");
    lcd.setCursor(0,1);
    lcd.print("press the button");
    if (buttonState == 0 && indexMenu == 0) {
      indexMenu = 1;
      prevState = 1;
      buttonState = 1;
    }
  }else if (indexMenu == 1) {
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
            menuPage = pagesNo;
            joyMovedX = true;
          }  
          if (xValue > minThreshold && xValue < maxThreshold) {
            joyMovedX = false;
          }
          if(buttonState == 0) {
            lcd.clear();
            indexMenu = 2;
            swValue = 1;
            prevState = 1;
            score = 0;
            level = startingLevelValue;
            pageIdWinGame = 1;
            beginLevelTime = millis();
            beginGameTime = millis();
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
          if(buttonState == 0) {
            lcd.clear();
            indexMenu = 3;
            buttonState = 1;
            prevState = 1;
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
           if(buttonState == 0) {
             lcd.clear();
             indexMenu = 4;
             buttonState = 1;
             prevState = 1;
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
            if(buttonState == 0) {
              lcd.clear();
              indexMenu = 3;
              buttonState = 1;
              prevState = 1;
            }
            break;
          case 5:
            lcd.clear();
            lcd.setCursor(2,0);
            lcd.print("Settings");
            lcd.setCursor(0,1);
            lcd.print("> exit");
            if (xValue < minThreshold && joyMovedX == false) {
              menuPage = 1;
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              menuPage++;
              joyMovedX = true;
            }  
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            if(buttonState == 0) {
              lcd.clear();
              indexMenu = 0;
              buttonState = 1;
              prevState = 1;
            }
            break;
          case 6:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("> Settings");
            lcd.setCursor(2,1);
            lcd.print("exit");
            if (xValue < minThreshold && joyMovedX == false) {
              menuPage--;
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              menuPage = menuPage - 2;
              joyMovedX = true;
            }  
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            if(buttonState == 0) {
              lcd.clear();
              indexMenu = 4;
              buttonState = 1;
              prevState = 1;
              indexSettings = 1;
            }
            break;
        }
      }else if (indexMenu == 2) {
          xValue = analogRead(pinX);
          if ((millis() - beginLevelTime) > levelDuration) {
            level++;
            score = score + 3 * level;
            beginLevelTime = millis();
          }
          if ((millis() - beginGameTime) > gameDuration) {
            if (xValue < minThreshold && joyMovedX == false) {
              if (pageIdWinGame == 3) {
                pageIdWinGame = 1;
              }else{
                pageIdWinGame++;
              }
              joyMovedX = true;
            }
            if (xValue > maxThreshold && joyMovedX == false) {
              if (pageIdWinGame == 1) {
                pageIdWinGame = 3;
              }else{
                pageIdWinGame--;
              }
              joyMovedX = true;
            }
            if (xValue > minThreshold && xValue < maxThreshold) {
              joyMovedX = false;
            }
            delay(50);
            if (pageIdWinGame == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print ("Congratulations!");
              lcd.setCursor(0,1);
              lcd.print ("You finished the");
            }else{
              if (pageIdWinGame == 2) {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print ("You finished the");
                lcd.setCursor(0,1);
                lcd.print ("game. Press the");
              }else{
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print ("game. Press the");
                lcd.setCursor(0,1);
                lcd.print ("button to exit!");
                if (buttonState == 0) {
                  indexMenu = 1;
                  pageIdWinGame = 0;
                  buttonState = 1;
                  prevState = 1;
                  EEPROM.get(0, highScorePlayer);
                  if (score > highScorePlayer.score) {
                      bestPlayer.Name = playerName;
                      bestPlayer.score = score;
                      EEPROM.put(0, bestPlayer);
                  }
                }
              }
            }
          }else{
            delay(50);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Lives:");
            lcd.setCursor(6,0);
            lcd.print(lives);
            lcd.setCursor(8,0);
            lcd.print("Level:");
            lcd.setCursor(14,0);
            lcd.print(level);
            lcd.setCursor(5,1);
            lcd.print("Score:");
            lcd.setCursor(13,1);
            lcd.print(score);
          }
          }else if (indexMenu == 3) {
            delay(20);
            EEPROM.get(0, highScorePlayer);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("HighScore:");
            lcd.setCursor(10,0);
            lcd.print(highScorePlayer.score);
            lcd.setCursor(13,0);
            lcd.print(highScorePlayer.Name);
            lcd.setCursor(0,1);
            lcd.print("> back");
            if (buttonState == 0) {
              lcd.clear();
              indexMenu = 1;
              menuPage = 2;
              buttonState = 1;
              prevState = 1;
            }
          }else if (indexMenu == 4) {
            xValue = analogRead(pinX);
            yValue = analogRead(pinY);
            delay(50);
            switch(indexSettings) {
              case 1:
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("> Start lvl:");
                lcd.setCursor(13,0);
                lcd.print(startingLevelValue);
                lcd.setCursor(2,1);
                lcd.print("Name:");
                lcd.setCursor(8,1);
                lcd.print(playerName);
                if (yValue < minThreshold && joyMovedY == false) {
                  if (startingLevelValue == finalLvl) {
                    startingLevelValue = 0;
                  }else{
                    startingLevelValue++;
                  }
                  joyMovedY = true;
                }
                if (yValue > maxThreshold && joyMovedY == false) {
                  if (startingLevelValue == 0) {
                    startingLevelValue = finalLvl;
                  }else{
                    startingLevelValue--;
                  }
                  joyMovedY = true;
                }
                if (yValue > minThreshold && yValue < maxThreshold) {
                  joyMovedY = false;
                }
                if (buttonState == 0) {
                  lcd.clear();
                  indexSettings = 2;
                  buttonState = 1;
                  prevState = 1;
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
                if (buttonState == 0) {
                  buttonState = 1;
                  prevState = 1;
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
                if (buttonState == 0) {
                  indexMenu = 1;
                  buttonState = 1;
                  menuPage = 3;
                  prevState = 1;
                }
                break;
            }
          }
}
