#define SEQUENCE_MAX_LENGTH 4

// Pin assignment
int pinButton = 2;
int pinLedA = 8;
int pinLedB = 9;
int pinLedC = 10;
int pinLedD = 11;

// speed etc
int shortDelay = 200;
int longDelay = 500;

// which pattern to play?
int pattern = 0;
int countPattern = 4;

int lastState = LOW;

void ledOn(int ledNumber) {
  digitalWrite(ledNumber, HIGH);
}

void ledOff(int ledNumber) {
  digitalWrite(ledNumber, LOW);
}


// all one, all off
void pattern0() {
  ledsOn();
  delay(longDelay);
  ledsOff();
  delay(longDelay);
}

// blink a cross
void pattern1() {
  ledOn(pinLedA);
  ledOn(pinLedC);
  delay(longDelay);
  ledsOff();

  ledOn(pinLedB);
  ledOn(pinLedD);
  delay(longDelay);
  ledsOff();
}

// just round, one by one
void pattern2() {
  ledOn(pinLedA);
  delay(shortDelay);
  ledsOff();
  ledOn(pinLedB);
  delay(shortDelay);
  ledsOff();
  ledOn(pinLedC);
  delay(shortDelay);
  ledsOff();
  ledOn(pinLedD);
  delay(shortDelay);
  ledsOff();
}

// round: all on, one by one. then round: all off, one by one.
void pattern3() {
  
  // all on, one by one
  ledOn(pinLedA);
  delay(shortDelay);
  ledOn(pinLedB);
  delay(shortDelay);
  ledOn(pinLedC);
  delay(shortDelay);
  ledOn(pinLedD);
  
  delay(longDelay);

  // all off, one by one
  ledOff(pinLedA);
  delay(shortDelay);
  ledOff(pinLedB);
  delay(shortDelay);
  ledOff(pinLedC);
  delay(shortDelay);
  ledOff(pinLedD);
  
  delay(longDelay); 
}

void setup() {
  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);
  pinMode(pinLedC, OUTPUT);
  pinMode(pinLedD, OUTPUT);
}

void ledsOff() 
{
  digitalWrite(pinLedA, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedC, LOW);
  digitalWrite(pinLedD, LOW);
}

void ledsOn() 
{
  digitalWrite(pinLedA, HIGH);
  digitalWrite(pinLedB, HIGH);
  digitalWrite(pinLedC, HIGH);
  digitalWrite(pinLedD, HIGH);
}

void loop() {
  // should move to next pattern?
  int newState = digitalRead(pinButton);
  if ((newState != lastState)) { // button pressed?
    if (newState == HIGH) {
      pattern = (pattern+1) % countPattern; // next pattern!  
    }
    lastState = newState;
  }

  // play ze pattern
  switch(pattern) {
    case 0: pattern0(); break;
    case 1: pattern1(); break;
    case 2: pattern2(); break;
    case 3: pattern3(); break;
  }
}
