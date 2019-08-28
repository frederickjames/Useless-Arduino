/*
  Flipper.cpp - Library for moving the flipper around.
*/

#include "Arduino.h"
#include "Flipper.h"
#include <Servo.h> 

Flipper::Flipper(int pin,int rest, int flipped)
{
  Servo Flipper;
  _range = (rest - flipped);
}

void moveIt();
void likeButton(int likes);
void peekOut();
void wiggle(int wiggles,int center);
void dontEven();
void ImWatchingYou();
