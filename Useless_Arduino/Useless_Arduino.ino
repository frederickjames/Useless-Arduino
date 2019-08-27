#include <Servo.h> 

//hiding position
const int pos0 = 145; //DO NOT SET ABOVE 180
//flipping position
const int pos1 =0;   //DO NOT SET BELOW 0
//how much to move by each loop
const int steps = 2;

Servo flipper;
byte switchState;
int servoPOS;
int moveSpeed;
byte movement = 0;
unsigned long currentMillis = 0;
unsigned long lastFlip = 0;

void setup() { 
  flipper.attach(9); 
  pinMode(10, INPUT); 
  digitalWrite(10, HIGH); 
  flipper.write(pos0);
  Serial.begin(9600);
} 

void loop(){ 
switchState = digitalRead(10);
servoPOS = flipper.read();
currentMillis = millis();

//low, not flipping - get flipping
if (switchState == LOW && movement != 1 && servoPOS > ((pos1+pos0)/2)) {
  delay(300);
  movement = 1;
  moveSpeed = setDelay(round(random(0,90)));
  moveIt(movement,servoPOS,moveSpeed,steps);
}
//low, flipping - keep flipping
if(switchState == LOW && movement == 1 && servoPOS > pos1)  {
  moveIt(movement,servoPOS,moveSpeed,steps);
}
if (switchState == LOW && movement != 1 && servoPOS <= ((pos1+pos0)/2)) {
  moveSpeed = 0;
  moveIt(movement,servoPOS,moveSpeed,steps);
}
//high, not moving or resetting - reset if needed
if (switchState == HIGH && movement != 0) {
  delay(300);
  movement = 0;
  moveSpeed = setDelay(round(random(0,100)));
  moveIt(movement,servoPOS,moveSpeed,steps);
  lastFlip = currentMillis;
}
//high, resetting - keep going
if(switchState == HIGH && movement == 0 && servoPOS < pos0)  {
  moveIt(movement,servoPOS,moveSpeed,steps);
}

if (servoPOS = pos0 && ((currentMillis - lastFlip) > 5000) && lastFlip > 0) {
  int rando = round(random(1,100));
  Serial.println(rando);
  if (rando <= 20) {
    likeButton(rando%10);
    lastFlip = currentMillis;
  }
  if (rando > 20 && rando <= 40) {
    peek();
    lastFlip = currentMillis;
  }
  lastFlip = currentMillis;
}

}

int setDelay(int r) {
  if (r < 70) {
    return 0;
  } else if (r < 80) {
    return 10;
  } else if (r < 92) {
    return 25;
  } else if (r >= 92) {
    return 250;
  } else {
    return 0;
  }
}
void moveIt(byte dir,int loc, int sp, int st) {
  if (sp > 0) {
    delay(sp);
  }
  if (dir == 0) { //move to reset
    flipper.write(min((loc+st),pos0)); //don't go past pos0
  }
  if (dir == 1) { //move to flip
    flipper.write(max((loc-10),pos1)); //don't go past pos-
  }
}
void likeButton(int likes) {
  int i = 0;
  for (i=0;i<likes;i++) {
    flipper.write(pos1);
    delay(300);
    flipper.write(pos0);
    delay(300);
  }
}
void peek() {
  flipper.write(pos0-35);
  delay(1500);
  flipper.write(pos0);
}
void writeSerial(String msg,byte dir,int loc, int sp, int st) {
  Serial.println("===============================");
  Serial.println(msg);
  Serial.println(dir);
  Serial.println(loc);
  Serial.println(sp);
  Serial.println(st);
  Serial.println("===============================");
}
