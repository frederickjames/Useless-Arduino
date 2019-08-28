/*
  Flipper.cpp - Library for moving the flipper around.
*/

#include "Arduino.h"
#include "Flipper.h"

Flipper::Flipper(byte pin,byte rest, byte flipped)
{
  Servo flipper;
  _rest = rest;
  _flipped = flipped;
  _range = (rest - flipped);
  flipper.attach(pin);
  _target = rest;
}

void Flipper::rest() {
  _target = _rest;
  _flipper.write(100);
}
void Flipper::flip() {
  _target = _flipped;
}

byte Flipper::getTarget() {
  return _target;
}

void Flipper::moveIt(byte p) {
  _flipper.write(p);
}
