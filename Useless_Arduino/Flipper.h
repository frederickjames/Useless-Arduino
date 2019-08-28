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
    Flipper(byte rest, byte flipped);
    void setPin(byte pin);
    void setDelay(int delay);             //independantly change the speed
    void setMove(byte target,int delay);  //where am I going

    byte getPos();                        //where am I?

    void justGo(byte b);
    void moveIt();
    
    void flipOut(int delay);
    void rest(int delay);
  private:
    byte _rest;                       //position when hiding
    byte _flipped;                    //position for flipping the switch
    byte _position;                   //where I am
    byte _target;                     //this is where I'm going next
    int _delay;                       //hoe long I wait between moves
    byte _steps;                      //how much I move each time
    bool _havingFun;                  //doing the fun stuff
    Servo _servo;                     //this is what I control
};

#endif
