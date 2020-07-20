#include "Arduino.h"
#include <Servo.h>

#define servoPin PA0
#define maxAngle 180
#define POT_IN PA_7


Servo myServo;
int pos = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  Serial.println("Moving forward...");
  for (i = 0; i<maxAngle-1; i++){
    myServo.write(i);
    delay(15);
  }
  Serial.println("Moving backwards...");
  for(i = maxAngle; i >0; i-=2){
    myServo.write(i);
    delay(15);
  }

  Serial.println("Pause...");
  delay(1000);
  
  /*
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    Serial.println(myServo.read());
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    Serial.println(myServo.read());

  }*/
}