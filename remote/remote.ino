#include <IRremote.h>
IRsend irsend;

const int ledPin = 9;

// Samsung remote IT codes.
// Source: http://arduinostuff.blogspot.de/2011/06/samsung-remote-ir-codes.html

// volume up
const unsigned int S_vup[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,1500,700,1550,650};

// volume down
const unsigned int S_vdown[68]={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,400,700,400,700,450,700,400,700,400,700,400,700,1550,700,400,700,1500,700,1500,700,1550,700,1500,700};
/************************************************/
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop()
{
  // TODO
}

