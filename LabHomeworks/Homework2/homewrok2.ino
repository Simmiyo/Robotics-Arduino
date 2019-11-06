const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int potPinR = A0;
const int potPinG = A1;
const int potPinB = A2;

int potValueR = 0;
int redValue = 0;
int potValueG = 0;
int greenValue = 0;
int potValueB = 0;
int blueValue = 0;

void setup() {
  pinMode(potPinR, INPUT);
  pinMode(potPinG, INPUT);
  pinMode(potPinB, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValueR = analogRead(potPinR);
  potValueG = analogRead(potPinG);
  potValueB = analogRead(potPinB);
  Serial.println(potValueG);
  redValue = map(potValueR, 0, 1023, 0, 255);
  greenValue = map(potValueG, 0, 1023, 0, 255);
  blueValue = map(potValueB, 0, 1023, 0, 255);
  setColor(redValue, greenValue, blueValue);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
