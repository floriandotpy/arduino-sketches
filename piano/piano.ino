#define SEQUENCE_MAX_LENGTH 4

// Pin assignment
int pinA = 2;
int pinB = 4;
int pinC = 6;
int pinD = 8;

int pinLedA = 3;
int pinLedB = 5;
int pinLedC = 7;
int pinLedD = 9;

int speakerOut = 10;

// used to code button sequences
enum Button { BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D };

// record the order of pressed buttons
int sequence_input[SEQUENCE_MAX_LENGTH];
int sequence_i = 0; // point to position which is to be filled next

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
int lastButtonPressed = -1;

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

void playSequence(int sequence[], int count)
{
  
  long d = 150000;
  int _tone;
  int led;
  
  for (int i = 0; i<count; i++) {
    
    switch (sequence[i])
    {
      case BUTTON_A: 
        _tone = toneA;
        led = pinLedA;
      break;
      case BUTTON_B: 
        _tone = toneB;
        led = pinLedB;
      break;
      case BUTTON_C: 
        _tone = toneC;
        led = pinLedC;
      break;
      case BUTTON_D: 
        _tone = toneD;
        led = pinLedD;
      break;
    }

    // light and sound
    digitalWrite(led, HIGH);
    playTone(_tone, d);
    digitalWrite(led, LOW);
  }
}

void hello()
{

  int sequence[] = { BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D };

  playSequence(sequence, 4);

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

void readButtons() 
{
  aDown = digitalRead(pinA);
  bDown = digitalRead(pinB);
  cDown = digitalRead(pinC);
  dDown = digitalRead(pinD);
}

void ledsOff() 
{
  digitalWrite(pinLedA, LOW);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinLedC, LOW);
  digitalWrite(pinLedD, LOW);
}

void loop() {

  // turn LEDs off by default
  ledsOff();
  
  // read button states
  readButtons();

  // assume button is still pressed. FIXME: this doesnt allow for same note twice
  int buttonPressed = lastButtonPressed;

  if (aDown) {
    digitalWrite(pinLedA, HIGH);
    playTone(toneA, toneA*toneDurationMultiplier);
    buttonPressed = BUTTON_A;
  }
  if (bDown) {
    digitalWrite(pinLedB, HIGH);
    playTone(toneB, toneB*toneDurationMultiplier);
    buttonPressed = BUTTON_B;
  }
  if (cDown) {
    digitalWrite(pinLedC, HIGH);
    playTone(toneC, toneC*toneDurationMultiplier);
    buttonPressed = BUTTON_C;
  }
  if (dDown) {
    digitalWrite(pinLedD, HIGH);
    playTone(toneD, toneD*toneDurationMultiplier);
    buttonPressed = BUTTON_D;
  }

  if (buttonPressed != lastButtonPressed) {
    // remember this button  
    sequence_input[sequence_i++] = buttonPressed;
    lastButtonPressed = buttonPressed;

    if (sequence_i == SEQUENCE_MAX_LENGTH) {

      // wait for buttons to be released
      while (aDown || bDown || cDown || dDown) {
        readButtons();
      }

      ledsOff();
    
      delay(100);
      
      // play sequence
      playSequence(sequence_input, SEQUENCE_MAX_LENGTH);
      
      // reset sequence collector
      sequence_i = 0;
    }
  }
  
}
