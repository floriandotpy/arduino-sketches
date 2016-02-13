int pinA = 2;
int pinB = 4;
int pinC = 6;
int pinD = 8;

int pinLedA = 3;
int pinLedB = 5;
int pinLedC = 7;
int pinLedD = 9;

int speakerOut = 10;

// Tones
int  c = 3830;    // 261 Hz 
int  d = 3400;    // 294 Hz 
int  e = 3038;    // 329 Hz 
int  f = 2864;    // 349 Hz 
int  g = 2550;    // 392 Hz 
int  a = 2272;    // 440 Hz 
int  b = 2028;    // 493 Hz 
int  C = 1912;    // 523 Hz 
int  D = d / 2;
int  E = e / 2;
int  F = f / 2;
int  G = g / 2;
int  A = a / 2;
int  B = b / 2;

// Define a special note, 'R', to represent a rest
int  R = 0;

// button tone assignment
int toneA = C;
int toneB = D;
int toneC = E;
int toneD = F;

// each tone is played several times
int toneDurationMultiplier = 4;

// input states
int aDown = 0;
int bDown = 0;
int cDown = 0;
int dDown = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
  pinMode(pinD, INPUT);

  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);
  pinMode(pinLedC, OUTPUT);
  pinMode(pinLedD, OUTPUT);

  pinMode(speakerOut, OUTPUT);

  hello();
}

void hello()
{
  long d = 200000;

  digitalWrite(pinLedA, HIGH);
  playTone(toneA, d);
  digitalWrite(pinLedA, LOW);

  digitalWrite(pinLedB, HIGH);
  playTone(toneB, d);
  digitalWrite(pinLedB, LOW);

  digitalWrite(pinLedC, HIGH);
  playTone(toneC, d);
  digitalWrite(pinLedC, LOW);

  digitalWrite(pinLedD, HIGH);
  playTone(toneD, d);
  digitalWrite(pinLedD, LOW);

  delay(100);

  digitalWrite(pinLedA, HIGH);
  digitalWrite(pinLedB, HIGH);
  digitalWrite(pinLedC, HIGH);
  digitalWrite(pinLedD, HIGH);

  delay(100);

  digitalWrite(pinLedA, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedC, LOW);
  digitalWrite(pinLedD, LOW);
}

// Pulse the speaker to play a tone for a particular duration
void playTone(int tone_, long duration) {
  
  long elapsed_time = 0;
  
  //  played less long than 'duration', pulse speaker HIGH and LOW
  while (elapsed_time < duration) {

    digitalWrite(speakerOut, HIGH);
    delayMicroseconds(tone_ / 2);

    // DOWN
    digitalWrite(speakerOut, LOW);
    delayMicroseconds(tone_ / 2);

    elapsed_time += tone_;
  }           
}

void loop() {

  // turn LEDs off by default
  digitalWrite(pinLedA, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedC, LOW);
  digitalWrite(pinLedD, LOW);

  // read button states
  aDown = digitalRead(pinA);
  bDown = digitalRead(pinB);
  cDown = digitalRead(pinC);
  dDown = digitalRead(pinD);

  if (aDown) {
    digitalWrite(pinLedA, HIGH);
    playTone(toneA, toneA*toneDurationMultiplier);
  }
  if (bDown) {
    digitalWrite(pinLedB, HIGH);
    playTone(toneB, toneB*toneDurationMultiplier);
  }
  if (cDown) {
    digitalWrite(pinLedC, HIGH);
    playTone(toneC, toneC*toneDurationMultiplier);
  }
  if (dDown) {
    digitalWrite(pinLedD, HIGH);
    playTone(toneD, toneD*toneDurationMultiplier);
  }
}
