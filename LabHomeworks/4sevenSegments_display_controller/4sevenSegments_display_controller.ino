const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int pinD1 = 10;
const int pinD2 = 11;
const int pinD3 = 12;
const int pinD4 = 13;

const int segSize = 8;
const int digitSize = 4;
const int cardDigits = 10;
 
const int pinX = A0; 
const int pinY = A1; 
const int pinSW = A2;

int swValue;
int xValue = 0;
int yValue = 0;

int segments[segSize] = {
pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};  
int digitIds[digitSize] = {
pinD1, pinD2, pinD3, pinD4};

byte joyMoved = false;
const int minThreshold = 400;
const int maxThreshold = 600;

byte digitMatrix[cardDigits][segSize - 1] = {
// a b c d e f g
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

int onId = 0;
int digitId = 0;
int displayedNo[] = {0,0,0,0};

unsigned long prevBlink = 0;
int dpPhase = -1;

void setDigit(int id) {
  for (int index = 0; index < digitSize; index++) {
    if (index != id) {
      digitalWrite(digitIds[index], HIGH);
    }
    digitalWrite(digitIds[id], LOW);
  }
}

void displayNo(int digit, byte dp) {
  for (int index = 0; index < segSize - 1; index++) {
    digitalWrite(segments[index], digitMatrix[digit][index]);
  }
  digitalWrite(pinDP, dp);
}

void showNo(int dp) {
  while (digitId < digitSize) {
    setDigit(digitId);
    displayNo(displayedNo[digitId], dp== digitId);
    delay(5);
    digitId = digitId + 1;
  }
  digitId = 0;
}

void setup() {
  for(int index = 0; index < segSize; index++) {
    pinMode(segments[index], OUTPUT);
  }
  for(int index = 0; index < digitSize; index++) {
    pinMode(digitIds[index], OUTPUT);
    digitalWrite(digitIds[index], HIGH);
  }
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if ((millis() - prevBlink) > 150) {
    if(dpPhase == -1) {
      dpPhase = onId;
    }
    else {
      dpPhase = -1;
    }
    prevBlink = millis();
  }
  showNo(dpPhase);
  xValue = analogRead(pinX);
  swValue = digitalRead(pinSW);
  if (xValue > maxThreshold && joyMoved == false) {
    if (onId == digitSize - 1) {
      onId = 0;
    }else{
      onId = onId + 1;
    }
    joyMoved = true;
  }
  if (xValue < minThreshold && joyMoved == false) {
    if (onId == 0) {
      onId = digitSize - 1;
    }else{
      onId = onId - 1;
    }
    joyMoved = true;
  }
  if (xValue > minThreshold && xValue < maxThreshold) {
    joyMoved = false;
  }
  if (swValue == 0) {
    delay(300);
    swValue = 1;
    while (swValue == 1) {
      swValue = digitalRead(pinSW);
      showNo(onId);
      yValue = analogRead(pinY);
      if (yValue > maxThreshold && joyMoved == false) {
        if (displayedNo[onId] == cardDigits - 1) {
          displayedNo[onId] = 0;
        }else{
          displayedNo[onId] = displayedNo[onId] + 1;
        }
      joyMoved = true;
      }
      if (yValue < minThreshold && joyMoved == false) {
        if (displayedNo[onId] == 0) {
          displayedNo[onId] = cardDigits - 1;
        }else{
          displayedNo[onId] = displayedNo[onId] - 1;
        }
      joyMoved = true;
      }
      if (yValue > minThreshold && yValue < maxThreshold) {
        joyMoved = false;
      }
     }
     delay(300);
  }
}
