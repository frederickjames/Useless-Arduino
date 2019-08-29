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

void Flipper::flipOut(int s) {
  setMove(_flipped, s);
}

void Flipper::rest(int s) {
  setMove(_rest, s);
}

void Flipper::moveIt() {
  _target = constrain(_target,_flipped,_rest);
  Serial.println(_position);
  Serial.println(_target);
  if (_position < _target) {
    _position += _steps;
    _position = constrain(_position,_flipped,_rest);
    _servo.write(_position);
    delay(_speed);
  } else if (_position > _target) {
    _position -= _steps;
    _position = constrain(_position,_flipped,_rest);
    _servo.write(_position);
    //delay(0);
  }
}/*
void Flipper::moveIt(byte dir,int loc, int sp, int st) {
  if (sp > 0) {
    delay(sp);
  }
  if (dir == 0) { //moving to rest
    flipper.write(min((loc+st),pos0)); //don't go past pos0
  }
  if (dir == 1) { //moving to flip
    flipper.write(max((loc-10),pos1)); //don't go past pos-
  }
}
/*
void Flipper::moveIt(byte dir,int loc, int sp, int st) {
  if (sp > 0) {
    delay(sp);
  }
  if (dir == 0) { //moving to rest
    flipper.write(min((loc+st),pos0)); //don't go past pos0
  }
  if (dir == 1) { //moving to flip
    flipper.write(max((loc-10),pos1)); //don't go past pos-
  }
}
*/
/**************************************
 *   THE FUN STUFF
 **************************************/
//Dance time?
/*
void wiggle(byte wiggles,byte center) {
  byte i = 0;
  for (i=0;i<wiggles;i++) {
    flipOut(center+3);
    delay(75);
    flipOut(center-3);
    delay(75);
  }
  rest();    //you're drunk, flipper, go home
}
*/
void Flipper::watchingYou(byte _speed) {
  justGo(_rest-((_rest-_flipped)/2));
  setMove(_rest,_speed);
}
