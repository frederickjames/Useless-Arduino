#include "Flipper.h"
#include <Servo.h>


#define pos0 135
//hiding position (flipper at rest)                   DO NOT SET ABOVE 180
#define pos1 5   
//flipping position (where it actualtes the switch)   DO NOT SET BELOW 0
#define steps 2  
//how much to move by each loop
#define idleTime = 6000

Flipper flipper(pos0,pos1);       //does not move faster than lightning :(
byte switchState;                 //If the switch on or off?
byte lastSwitchState;             //Switch state end of last loop
byte servoPOS;                    //this is the servos current position
int moveSpeed;                    //used to set a delay between move steps (lower is faster)
unsigned long currentMillis = 0;  //this is how long the machine has been alive
unsigned long startIdle = 0;      //idle time counted from right now
byte rando;                       //using this guy a lot so might as well initialize it once.


void setup() {
  Serial.begin(9600);     //only do this if you're looking for bugs.
  pinMode(10, INPUT); 
  digitalWrite(10, HIGH); 
  flipper.setPin(9);
} 

void loop(){
switchState = digitalRead(10);
currentMillis = millis();

//if (lastSwitchState != switchState) {
  if (switchState == LOW) {
    flipper.flipOut(15000);
  }
  if (switchState == HIGH) {
    flipper.rest(0);
  }
//}

flipper.moveIt(&currentMillis);
//flipper.dataDump();


lastSwitchState = switchState;
Serial.println(lastSwitchState);
Serial.println(switchState);
}
/*******************************************
***     END LOOP     ***
*******************************************/

bool checkSwitch() {
  if (lastSwitchState == switchState) {
    return 0;
  } else {
    return 1;
  }
}
int randomSpeed() {
  byte speeds[10] = {0,10,20,20,20,50,50,250,50,0};
//  int speeds[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};
  int r = round(random(0,10));
  //Serial.println(r);
  return speeds[r];  
}
