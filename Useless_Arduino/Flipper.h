/*
  Flipper.h - Library for moving the flipper around.
*/
#ifndef Flipper_h
#define Flipper_h

#include "Arduino.h"

class Flipper
{
  public:
    Flipper(int pin,int rest, int flipped);
    void moveIt(int pos);                       //Just go to that position
    void moveIt(int pos, int delay);            //Wait, then go to that position
    void moveIt(int pos, int delay, int steps)
    void flip()
    void rest()
    void likeButton(int likes);
    void peekOut();
    void wiggle(int wiggles,int center);
    void dontEven();
    void ImWatchingYou();
  private:
    int _range;
    int _pin;
};

#endif
