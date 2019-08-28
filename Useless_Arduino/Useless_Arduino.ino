#include "Flipper.h"

#define pos0 135
//hiding position (flipper at rest)                   DO NOT SET ABOVE 180
#define pos1 5   
//flipping position (where it actualtes the switch)   DO NOT SET BELOW 0
#define steps = 2  
//how much to move by each loop

Flipper flipper(pos0,pos1);       //does not move faster than lightning :(
byte switchState;                 //If the switch on or off?
byte lastSwitchState;             //Switch state end of last loop
byte servoPOS;                    //this is the servos current position
int moveSpeed;                    //used to set a delay between move steps (lower is faster)
//byte moveType = 0;                //0 for resetting, 1 for flipping
unsigned long currentMillis = 0;  //this is how long the machine has been alive
unsigned long lastFlip = 0;       //the last time the switch was flipped (used to determine idle users)
byte rando;                       //using this guy a lot so might as well initialize it once.


void setup() {
  Serial.begin(9600);     //only do this if you're looking for bugs.
  pinMode(10, INPUT); 
  digitalWrite(10, HIGH); 
  flipper.setPin(9);
} 

void loop(){
//Serial.println(flipper.getTarget());
//switchState = digitalRead(10);
//currentMillis = millis();
/*
if (switchState = LOW) {
  flipper.flipOut(0);
}*/
flipper.setMove(25,5);

flipper.moveIt();


lastSwitchState = switchState;
} //end loop()

bool checkSwitch() {
  if (lastSwitchState == switchState) {
    return 0;
  } else {
    return 1;
  }
}

//de bugs, de bugs!
void writeSerial(String msg,byte dir,int loc, int sp, int st) {
  Serial.println("===============================");
  Serial.println(msg);
  Serial.println(dir);
  Serial.println(loc);
  Serial.println(sp);
  Serial.println(st);
  Serial.println("===============================");
}
