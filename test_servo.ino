#include <Servo.h>
#include "IRremote.h"

Servo servo;
int pos = 0;
int incomingByte = 0;

IRrecv irrecv(8);
decode_results results;

#define KEY_0   0xFF6897
#define KEY_1   0xFF30CF
#define KEY_2   0xFF18E7
#define KEY_3   0xFF7A85
#define KEY_4   0xFF10EF
#define KEY_5   0xFF38C7
#define KEY_6   0xFF5AA5
#define KEY_7   0xFF42BD
#define KEY_8   0xFF4AB5
#define KEY_9   0xFF52AD
#define KEY_ACT 0xFFC23D

void new_pos(int);
void act();
void only_servo();

void setup()
{
  Serial.begin(9600);
  
  servo.attach(9);

  irrecv.enableIRIn();
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    switch (results.value) {
    case KEY_0:
      new_pos(0);
      break;

    case KEY_1:
      new_pos(1);
      break;

    case KEY_2:
      new_pos(2);
      break;

    case KEY_3:
      new_pos(3);
      break;

    case KEY_4:
      new_pos(4);
      break;

    case KEY_5:
      new_pos(5);
      break;

    case KEY_6:
      new_pos(6);
      break;

    case KEY_7:
      new_pos(7);
      break;

    case KEY_8:
      new_pos(8);
      break;

    case KEY_9:
      new_pos(9);
      break;

    case KEY_ACT:
      act();
      break;

    default:
      break;
    }

    irrecv.resume();
  }
}

void only_servo()
{
  if (Serial.available() > 0) {
    incomingByte = Serial.read() - 48;

    if (incomingByte >= 0 and incomingByte < 10) {
      pos = pos * 10 + incomingByte;
    } else {
      if (pos >= 1 and pos <= 180) {
        
        Serial.print("move: ");
        Serial.println(pos, DEC);
        
        servo.write(pos);
      }
      
      pos=0;
    }
  }
}

void new_pos(int number)
{
  pos = pos * 10 + number;

  Serial.print("new pos: ");
  Serial.println(pos, DEC);
}

void act()
{
  if (pos >= 0 and pos <= 180) {
        
    Serial.print("move: ");
    Serial.println(pos, DEC);
    
    servo.write(pos);
  }

  pos = 0;
}
