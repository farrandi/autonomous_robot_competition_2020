#include <Claw.h>

Servo smallServo;
Servo bigServo;

Claw::Claw(){
<<<<<<< HEAD
    smallServo.attach(SMALLSERVO_PIN);
    bigServo.attach(BIGSERVO_PIN);
}

void Claw::openClaw(){
=======

  }

void Claw::setup(){
  smallServo.attach(SMALLSERVO_PIN);
  bigServo.attach(BIGSERVO_PIN);
  bigServo.write(DOWNPOS);
  return;
}

  void Claw::openClaw(){
>>>>>>> 7c132714873f53004ef8de7d758466cb71f25058
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

  int Claw::readSmallServo(){
    return smallServo.read();
  }

  int Claw::readbigServo(){
    return bigServo.read();
  }

  void Claw::writeSmallServo(int pos){
    smallServo.write(pos);
  }

  void Claw::writeBigServo(int pos){
    bigServo.write(pos);
  }