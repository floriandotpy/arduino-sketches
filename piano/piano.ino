int pinA = 4;
int pinB = 5;
int pinC = 6;
int pinD = 7;

int speakerOut = 9;

// TONES  ==========================================
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

int pause = 10;
// Set overall tempo
long tempo = 30000;

int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

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

  pinMode(speakerOut, OUTPUT);

  //Serial.begin(9600);
}


// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone(int tone_, long duration) {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {
 
      digitalWrite(speakerOut, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += tone_;
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }
  }                                
}



void loop() {
  
 // playTone(3830, 432000);
 // delayMicroseconds(500);
  //return;
  
  int tone_ = R; // mute by default
  int beat = 8;
  long duration = beat * tempo;

  // read button states
  aDown = digitalRead(pinA);
  bDown = digitalRead(pinB);
  cDown = digitalRead(pinC);
  dDown = digitalRead(pinD);

  if (aDown) {
    tone_ = toneA;
  }
  if (bDown) {
    tone_ = toneB;
  }
  if (cDown) {
    tone_ = toneC;
  }
  if (dDown) {
    tone_ = toneD;
  }

  playTone(tone_, tone_*8);

}
