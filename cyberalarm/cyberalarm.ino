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

// state variables
unsigned long timer = 0;
int lastState = LOW;

void setLEDs(byte pattern) {
  digitalWrite(pinLedA, HIGH && (pattern & B0001));
  digitalWrite(pinLedB, HIGH && (pattern & B0010));
  digitalWrite(pinLedC, HIGH && (pattern & B0100));
  digitalWrite(pinLedD, HIGH && (pattern & B1000));
}


// all one, all off
byte pattern0(long timer) {
  int thisDuration = 1000;
  if (timer % thisDuration < 500) {
    return B1111; // all ON
  } else {
    return B0000; // all OFF
  }
}

// blink a cross
byte pattern1(long timer) {
  int thisDuration = 1000;
  if (timer % thisDuration < 500) {
    return B0101;
  } else {
    return B1010;
  }
}

// just round, one by one
byte pattern2(long timer) {
  int thisDuration = 2000;
  int thisRun = timer % thisDuration;
  if (thisRun < 500) {
    return B0001;
  } else if(thisRun < 1000) {
    return B0010;
  } else if(thisRun < 1500) {
    return B0100;
  } else {
    return B1000;
  }
}

// round: all on, one by one. then round: all off, one by one.
byte pattern3(long timer) {
  int thisDuration = 4000;
  int thisRun = timer % thisDuration;
  if (thisRun < 500) {
    return B0000;
  } else if(thisRun < 1000) {
    return B0001;
  } else if(thisRun < 1500) {
    return B0011;
  } else if(thisRun < 2000) {
    return B0111;
  } else if(thisRun < 2500) {
    return B1111;
  } else if(thisRun < 3000) {
    return B1110;
  } else if(thisRun < 3500) {
    return B1100;
  } else {
    return B1000;
  }
}

void setup() {
  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);
  pinMode(pinLedC, OUTPUT);
  pinMode(pinLedD, OUTPUT);
}

void loop() {

  timer = millis();
  
  // should move to next pattern?
  int newState = digitalRead(pinButton);
  if ((newState != lastState)) { // button pressed?
    if (newState == HIGH) {
      pattern = (pattern+1) % countPattern; // next pattern!  
      delay(100);
    }
    lastState = newState;
  }

  // play ze pattern
  byte bits;
  switch(pattern) {
    case 0: bits = pattern0(timer); break;
    case 1: bits = pattern1(timer); break;
    case 2: bits = pattern2(timer); break;
    case 3: bits = pattern3(timer); break;
  }

  setLEDs(bits);
}
