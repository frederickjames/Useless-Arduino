#include <Servo.h> 

//hiding position (flipper at rest)
const int pos0 = 135; //DO NOT SET ABOVE 180
//flipping position (where it actualtes the switch)
const int pos1 = 5;   //DO NOT SET BELOW 0
//how much to move by each loop
const int steps = 2;

Servo flipper;                    //does not move faster than lightning :(
byte switchState;                 //If the switch on or off?
int servoPOS;                     //this is the servos current position
int moveSpeed;                    //used to set a delay between move steps (lower is faster)
byte moveType = 0;                //0 for resetting, 1 for flipping
unsigned long currentMillis = 0;  //this is how long the machine has been alive
unsigned long lastFlip = 0;       //the last time the switch was flipped (used to determine idle users)
int rando;                        //using this guy a lot so might as well initialize it once.


void setup() { 
  flipper.attach(9); 
  pinMode(10, INPUT); 
  digitalWrite(10, HIGH); 
  flipper.write(pos0);
//  Serial.begin(9600);           //only do this if you're looking for bugs.
} 

void loop(){ 
switchState = digitalRead(10);
servoPOS = flipper.read();
currentMillis = millis();

//low, not flipping - get flipping
if (switchState == LOW && moveType != 1) {
  if (servoPOS <= (pos1+pos0)/2) {  //move a little bit away from the switch before hitting it
    wiggle(7,servoPOS+5);
    moveSpeed = 0;
    moveIt(moveType,servoPOS,moveSpeed,steps);
    rando = round(random(0,10));
    if (rando < 5) {
      likeButton(rando);
    }
  } else {
    delay(300);     //a little pause to make it look like I'm thinking about it
    moveType = 1;
    moveSpeed = setDelay(round(random(10,100)));
    moveIt(moveType,servoPOS,moveSpeed,steps);
  }
}

//low, flipping - keep flipping
if(switchState == LOW && moveType == 1 && servoPOS > pos1)  {
  moveIt(moveType,servoPOS,moveSpeed,steps);
}

//high, not moving or resetting - reset if needed
if (switchState == HIGH && moveType != 0) {
  delay(300);     //hey, watcha doing wo my switch?
  moveType = 0;
  moveSpeed = setDelay(round(random(0,100)));
  moveIt(moveType,servoPOS,moveSpeed,steps);
  lastFlip = currentMillis;
}
//high, resetting - keep going
if(switchState == HIGH && moveType == 0 && servoPOS < pos0)  {
  moveIt(moveType,servoPOS,moveSpeed,steps);
}

//Sitting at rest, let's haave some fun
if (servoPOS = pos0 && (currentMillis - lastFlip) >= 6000 && lastFlip > 0) {
  rando = round(random(0,100));
  if (rando <20) {
    peekOut();
    lastFlip = currentMillis;
  } else if (rando >= 20 && rando <30) {
    wiggle(7,(pos0-pos1)/2);
    lastFlip = currentMillis;
  }
}


} //end loop()


/************************************************************************
 * functions for moving the flipper
 ***********************************************************************/
//move the flipper a little bit
void moveIt(byte dir,int loc, int sp, int st) {
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
//a table for determining the speed based on random input

int setDelay(int r) {
  if (r < 4) {
    return 250;
  } else if (r < 18) {
    return 50;
  } else if (r < 30) {
    return 25;
  } else if (r < 50) {
    return 10;
  } else {
    return 0;
  }
}

/************************************************************************
 * The next two functions are only so I don't have to remember if I need
 * to add or subtract the offset when going directly to a position
 * relative to rest or flipped out.
 * Also has logic to make sure the offset does not move it greater than
 * the bounds of pos0 and pos1
 ***********************************************************************/
//move the flipper to flipping position
//offset is how many degrees away from the full flipping position
void flipOut(int offset = 0) {
  //move directly to the smaller of the upper bound or the desired position
  flipper.write(min(pos1+offset,pos0));
}
//move the flipper to resting/hiding position
//offset is how many degrees away from the full hiding position
void rest(int offset = 0) {
  //move directly to the higher of the lower bound or the desired position
  flipper.write(max(pos0-offset,pos1));
}

/************************************************************************
 * the fun stuff
 ***********************************************************************/
//smash it!
void likeButton(int likes) {
  int i = 0;
  for (i=0;i<likes;i++) {
    flipOut();
    delay(300);
    rest(25);
    delay(300);
  }
  rest();    //you've made your point, go rest
}

//You looking at my switch?
void peekOut() {
  rest(round(random(5,25)));
  delay(1500);
  rest(0);
}

//Dance time?
void wiggle(int wiggles,int center) {
  int i = 0;
  for (i=0;i<wiggles;i++) {
    flipOut(center+3);
    delay(75);
    flipOut(center-3);
    delay(75);
  }
  rest();    //you're drunk, flipper, go home
}

void dontEven() {
  //pasue during return
}

void ImWatchingYou() {
  //come out 3/4 then go back slowly
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
