#include <Claw.h>
#include <INIT.h>

Claw::Claw(){
    smallServo.attach(SMALLSERVO_PIN);
    bigServo.attach(BIGSERVO_PIN);
}

void Claw::openClaw(){
	int smallServoPos = smallServo.read();
    for (int pos = smallServoPos; pos <= OPENPOS; pos++){
      smallServo.write(pos);
      delay(5);
    }
    return;
  }

 void Claw::closeClaw(){
  int smallServoPos = smallServo.read();
	if (smallServoPos != OPENPOS) {
      openClaw();
    }
    for (int pos = OPENPOS; pos >= CLOSEPOS; pos--) {
      smallServo.write(pos);
      delay(5);
    }
    return;
  }

void Claw::lowerClaw() { 
    int bigServoPos = bigServo.read();
	for (int pos = bigServoPos; pos >= DOWNPOS; pos--) {
      bigServo.write(pos);
      delay(15);
    }
    return;
  }

void Claw::raiseClaw() {
	int bigServoPos = bigServo.read();
    for (int pos = bigServoPos; pos <= UPPOS; pos++){
      bigServo.write(pos);
      delay(15);
    }
  }