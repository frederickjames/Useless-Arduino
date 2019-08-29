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
  //setup
    Flipper(byte rest, byte flipped);
    void setPin(byte pin);
    void dataDump();
  //information
    byte getPos();                        //where am I?
    int getSpeed();
  //basic function
    void setMove(byte t,int s);       //where I am going
    void setDelay(int s);             //independantly change the speed
    void justGo(byte t);
    void flipOut(int s);
    void rest(int s);
    void moveIt();                    //moves to the desired _target with _speed

  //fun things at rest
    void peak(int duration);
    void watchingYou(byte _speed);   //come out half way then retract slowly.
    
  //fun things while returning to rest
    void dontEven();        //pause during rest movement

  //fun things at any time
    void smash();
    void wiggle();

/*
each action should have a refrence. the main loop will reference that
action and will continue it unless there is an interruption detected (switch change)
Each action should check for a switch change and act accordingly
Each Action should have a next action (some dynamic some static)
*/  
    
  private:
  //setup
    Servo _servo;                     //this is what I control
    byte _rest;                       //position when hiding
    byte _flipped;                    //position for flipping the switch
    byte _steps;                      //how much I move each time
  //information
    bool _havingFun;                  //doing the fun stuff   ????
    byte _position;                   //where I am
  //basic function
    byte _target;                     //this is where I'm going next
    byte _speed;                      //how long I wait between moves (lower = faster travel)
  //fun Stuff
    
    
};

#endif
