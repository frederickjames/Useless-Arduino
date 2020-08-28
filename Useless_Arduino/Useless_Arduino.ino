#include <Servo.h> 
Servo servo_1; 
int pos = 0; 
int switchState; 
void setup() 
{ 
servo_1.attach(9); 
pinMode(11, INPUT); 
digitalWrite(11, HIGH); 
servo_1.write(102);
Serial.begin(9600);
} 
void loop(){ 
switchState = digitalRead(11);
Serial.println(switchState);
if(switchState==LOW) 
{ 
delay(50); 
servo_1.write(0); 
delay(300); 
for(pos = 0; pos < 102; pos+=2){ 
servo_1.write(pos); 
delay(5); 
} 
} 
delay(5); 
}
