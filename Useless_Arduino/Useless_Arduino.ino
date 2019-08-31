#include <Servo.h>


#define pos0 135
//hiding position (flipper at rest)                   DO NOT SET ABOVE 180
#define pos1 5   
//flipping position (where it actualtes the switch)   DO NOT SET BELOW 0
#define steps 2  
//how much to move by each loop
#define idleTime = 6000

Servo flipper;                    //does not move faster than lightning :(
byte switchState;                 //If the switch on or off?
int currentPosition;
byte servoPOS;                    //this is the servos current position
int moveSpeed;                    //used to set a delay between move steps (lower is faster)
unsigned long currentMillis = 0;  //this is how long the machine has been alive
unsigned long startIdle = 0;      //idle time counted from right now
byte rando;                       //using this guy a lot so might as well initialize it once.
byte _rest = 135;                 //position when hiding
byte _flipped = 5;                //position for flipping the switch
byte _steps = 2;                      //how much I move each time
unsigned long _startMillis;       //start counting the time
byte _waitTime;                   //hoe long before I do something
byte _target;                     //this is where I'm going next
byte _currentAction;              //this is what I am doing (I should haave a table for this)



void setup() {
  Serial.begin(9600);     //only do this if you're looking for bugs.
  pinMode(10, INPUT); 
  digitalWrite(10, HIGH); 
  flipper.attach(9);
  flipper.write(_rest);
  _target = (rest);
} 

void loop(){
switchState = digitalRead(10);
currentMillis = millis();
currentPosition = flipper.read();

if (switchState == LOW) {
  flipOut(1500,&currentPosition);
}
if (switchState == HIGH) {
  rest(1,&currentPosition);
}

//justGo(_rest,&flipper);

moveIt(&currentMillis,&flipper);
//flipper.dataDump();
}
/*******************************************
***     END LOOP     ***
*******************************************/

int randomSpeed() {
  byte speeds[10] = {0,10,20,20,20,50,50,250,50,0};
//  int speeds[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};
  int r = round(random(0,10));
  //Serial.println(r);
  return speeds[r];  
}

//Sets the next move if I'm flipping out
void flipOut(int t,int *cPos) {
  if (cPos > _flipped) {
    _target = cPos - _steps;     //will handle going beyond _flipped in moveIt()
    _startMillis = millis();
    _waitTime = t;
  } else {
    _currentAction = 0;
  }
}

//Sets the next move if I'm going to rest
void rest(int t,int *cPos) {
  if (&cPos < _rest) {
    _target = cPos + _steps;     //will handle going beyond _flipped in moveIt()
    _startMillis = millis();
    _waitTime = t;
  } else {
    _currentAction = 0;
  }
}

//move fast to a place
void justGo(int t, Servo *servo) {
  _target = constrain(t, _flipped, _rest);
  servo->write(_target);
}

void moveIt(unsigned long *cMillis, Servo *servo) {
  if ((cMillis - _startMillis) >= _waitTime) {
    //do stuff
    servo->write(constrain(_target,_flipped, _rest));
    _startMillis = millis();
  }
}


/***************************************************
_target table

00 -  nothing (go rest I guess?)
01 -  flipout
02 -  rest
03 -  smash
04 -  wiggle

***************************************************/
