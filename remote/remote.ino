#include <IRremote.h>
IRsend irsend;

const int led_ir_pin = 3;
const int led_control_pin = 4;
const int button_pin = 7;

int last_action = 0;
int wait = 1000;


// Samsung remote IT codes.
// Source: http://arduinostuff.blogspot.de/2011/06/samsung-remote-ir-codes.html

// volume up
unsigned int S_vup[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,1500,700,1550,650};

// volume down
unsigned int S_vdown[68]={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,400,700,400,700,450,700,400,700,400,700,400,700,1550,700,400,700,1500,700,1500,700,1550,700,1500,700};
/************************************************/

// power on/off
unsigned int S_pwr[68]={4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};

void setup()
{
  Serial.begin(9600);
  pinMode(led_ir_pin, OUTPUT);
  pinMode(led_control_pin, OUTPUT);
  pinMode(button_pin, INPUT);
}

void loop()
{
  if(digitalRead(button_pin) == HIGH && last_action+wait <  millis()) {
    Serial.println("button...");
    led_on();
    last_action = millis();
    power();
  } else if (last_action+wait <  millis()) {
    led_off();
  }
  
}

void led_on()
{
  digitalWrite(led_control_pin, HIGH);
}

void led_off()
{
  digitalWrite(led_control_pin, LOW);
}

void volume_up()
{
  Serial.println("Volume up");
  irsend.sendRaw(S_vup, 68, 38);
}

void volume_down()
{
  Serial.println("Volume down");
  irsend.sendRaw(S_vdown, 68, 38);
}

void power()
{
  Serial.println("Power");
  irsend.sendRaw(S_pwr, 68, 38);
//  irsend.sendSamsung()
}
