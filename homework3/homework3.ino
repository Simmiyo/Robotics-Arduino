 #include "pitches.h"

int melody[] = {
  NOTE_A6, NOTE_A6,NOTE_B6, NOTE_G6, NOTE_A6,0, NOTE_B6, NOTE_C7, NOTE_B6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7, NOTE_B6, NOTE_A6, NOTE_G6, NOTE_A6};

int noteDurations[] = {
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };

const int passiveBuzzerPin = A0;
const int activeBuzzerPin = 11;
const int threshold = 1;
const int buzzerDelay = 5000;
const int buttonPin = 2;

int knockValue = 0;
unsigned int previousKnockState = 0;
unsigned int msCounter = 0;
int buttonState = 0;
int thisNote = 0;
char phase = 'b'; // b = before, a = after

void setup() {
  pinMode(passiveBuzzerPin, INPUT);
  pinMode(activeBuzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  knockValue = analogRead(passiveBuzzerPin);
  buttonState = digitalRead(buttonPin);
  if (phase == 'b' && knockValue >= threshold) {
    previousKnockState = millis();
    Serial.println("Knock!");
    phase = 'a';
  }
  if (phase == 'a') {
     msCounter = millis() - previousKnockState;
     if ( msCounter > buzzerDelay) {
       int noteDuration = 1000/noteDurations[thisNote];
       tone(activeBuzzerPin, melody[thisNote],noteDuration);
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);
       noTone(activeBuzzerPin);
       thisNote = thisNote + 1;
       if (thisNote == 16) {
         thisNote = 0;
       }
       if (buttonState == 0) {
         noTone(activeBuzzerPin);
         thisNote = 0;
         phase = 'b';
       }
    }
  }
  //Serial.println(buttonState);
}
