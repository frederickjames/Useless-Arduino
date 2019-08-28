/*
  Flipper.cpp - Library for moving the flipper around.
*/

#include "Arduino.h"
#include "Flipper.h"

Flipper::Flipper(byte rest, byte flipped)
{
  _rest = constrain(rest,0,180);
  _flipped = constrain(flipped,0,180);
  _steps = 2;
  _servo.write(_rest);
  Serial.println(_rest);
  Serial.println(_flipped);
}

void Flipper::setPin(byte pin) {
  _servo.attach(pin);
}
void Flipper::setDelay(int delay) {
  _delay = delay;
}
void Flipper::setMove(byte target,int delay) {
  _target = target;
  _delay = delay;
}

void Flipper::justGo(byte pos) {
  byte p = constrain(pos,_flipped,_rest);
  _servo.write(p);
}
void Flipper::moveIt() {
  byte angle = _servo.read();
  if (angle != _target) {  //if not there yet
      if (angle < _target) {
        angle = (angle + _steps);
      } else if (angle > _target) {
        angle = (angle - _steps);
      }
      delay(delay);
      _servo.write(angle);
  }  
}

void Flipper::flipOut(int delay) {
  setMove(_flipped,delay);
}
void Flipper::rest(int delay) {
  setMove(_rest,delay);
}
