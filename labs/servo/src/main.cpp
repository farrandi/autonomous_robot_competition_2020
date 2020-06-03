#include "Arduino.h"
#include <Servo.h>

#define servoPin PA0
#define maxAngle 120

Servo myServo;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Moving forward...");
  for (i = 0; i<maxAngle; i++){
    myServo.write(i);
    delay(15);
  }

  delay(1000);

  Serial.println("Moving backwards...");
  for(i = maxAngle; i >0; i-=2){
    myServo.write(i);
    delay(15);
  }

  Serial.println("Pause...");
  delay(1000);
}