#include <Arduino.h>
#include <Servo.h>

Servo servo_1; 
int pos = 140; 
int switchState; 
void setup() 
{ 
servo_1.attach(9); 
pinMode(10, INPUT); 
digitalWrite(10, HIGH); 
servo_1.write(0);
Serial.begin(9600);
} 
void loop(){ 
switchState = digitalRead(10);
Serial.print("switch State:   ");
Serial.println(switchState);

if(switchState==LOW) 
{ 
  delay(500);  
  for(pos = 0; pos < 180; pos+=2){ 
    servo_1.write(pos);
    Serial.println(servo_1.read());
    delay(5); 
  } 
} /*else {
  servo_1.write(0);
}*/
servo_1.write(0);
delay(5); 
}
