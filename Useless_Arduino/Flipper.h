/*
  Flipper.h - Library for moving the flipper around.
*/
#ifndef Flipper_h
#define Flipper_h

#include "Arduino.h"
#include <Servo.h>

class Flipper
{
  public:
    Flipper(byte pin,byte rest, byte flipped);
    void moveIt(byte p);                       //Just go to that position
    void moveIt(byte pos, int stepDelay);            //Wait, then go to that position
    void moveIt(byte pos, int stepDelay, byte steps);
    void flip();  //go to flipped (sets target to flipped)
    void rest();  //go to rest (sets target to rest)
    byte getTarget();
    int currentPos();
  private:
    byte _rest;
    byte _flipped;
    byte _range;
    byte _target;
    Servo _flipper;
};

#endif
