/*
  Flipper.cpp - Library for moving the flipper around.
*/

#include "Arduino.h"
#include "Flipper.h"

/**************************************
 *   SETUP
 **************************************/
Flipper::Flipper(byte rest, byte flipped)
{
  _rest = constrain(rest, 0, 180);
  _flipped = constrain(flipped, 0, 180);
  _steps = 2;
  _target = _rest;
  _servo.write(_rest);
}

void Flipper::setPin(byte pin) {
  _servo.attach(pin);
  _position = _servo.read();
}

void Flipper::dataDump() {
  Serial.println("**********");
/*Serial.println("_rest: " + _rest);
  Serial.println(strcat("_flipped: ",_flipped));
  Serial.println("_steps: " + _steps);
  Serial.println("_position: " + _position);
  Serial.println("_target: " + _target);
  Serial.println("_speed: " + _speed);*/
  Serial.println(_rest);
  Serial.println(_flipped);
  Serial.println(_steps);
  Serial.println(_position);
  Serial.println(_target);
  Serial.println(_speed);
  Serial.println("**********");
}
/**************************************
 *   INFORMATION
 **************************************/
byte Flipper::getPos() {
  _position = _servo.read();
  return _position;
}

int Flipper::getSpeed() {
  return _speed;
}

/**************************************
 *   BASIC FUNCTION
 **************************************/
void Flipper::setMove(byte t, int s) {
  _target = constrain(t,_flipped,_rest);
  _speed = s;
}
void Flipper::setDelay(int s) {
  _speed = s;
}

void Flipper::justGo(byte t) {
  _target = constrain(t, _flipped, _rest);
  _servo.write(_target);
}

void Flipper::flipOut(byte t) {
  cPos = _servo.read;
  if (cPos < _flipped) {
    _target = cPos - _steps
  }
}

void Flipper::rest(int s) {
  
}

void Flipper::moveIt(unsigned long *cMillis) {
  if ((cMillis - _startMillis) >= _nextMillis) {
    //do stuff
    _servo.write(constrain(_target,_flipped, _rest));
    _startMillis = millis();
  }
}

/**************************************
 *   THE FUN STUFF
 **************************************/
