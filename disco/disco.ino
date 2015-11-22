/*
  BINARY DISCO 
  /o/ ...  \o/ ... \o\ 
  
  WHAT IS THIS
  3 blinking LEDs: a binary counter.
  
  CIRCUIT
  Connect 3 LEDs to pins 2, 3 and 4. 
  Don't forget necessary resistors.
  I used three 220 Ohm resistors, one\
  for each LED.
  
 */

int ledA = 2;
int ledB = 3;
int ledC = 4;

// count up
int counter = 0;

// how many ms to sleep between each count
int sleep = 300;

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(ledA, OUTPUT);     
  pinMode(ledB, OUTPUT);     
  pinMode(ledC, OUTPUT);   
}

// the loop routine runs over and over again forever:
void loop() {
  
  // determine values for binary clock digits
  int valA = counter & 1;
  int valB = (counter & 2) >> 1;
  int valC = (counter & 4) >> 2;
  
  // update LEDs according to digits
  digitalWrite(ledA, valA == 1 ? HIGH : LOW);   
  digitalWrite(ledB, valB == 1 ? HIGH : LOW);
  digitalWrite(ledC, valC == 1 ? HIGH : LOW);

  counter++;

  delay(sleep);
}
