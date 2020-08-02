#include <Claw.h>

Claw::Claw(){
    this->smallServo.attach(SMALLSERVO_PIN);
    this->bigServo.attach(BIGSERVO_PIN);
  }

  void Claw::openClaw(){
	int smallServoPos = this->smallServo.read();
    for (int pos = smallServoPos; pos <= OPENPOS; pos++){
      this->smallServo.write(pos);
      delay(5);
    }
    return;
  }

  void Claw::closeClaw(){
    int smallServoPos = this->smallServo.read();
	if (smallServoPos != OPENPOS) {
      openClaw();
    }
    for (int pos = OPENPOS; pos >= CLOSEPOS; pos--) {
      this->smallServo.write(pos);
      delay(5);
    }
    return;
  }

  void Claw::lowerClaw() { 
    int bigServoPos = this->bigServo.read();
	for (int pos = bigServoPos; pos >= DOWNPOS; pos--) {
      this->bigServo.write(pos);
      delay(15);
    }
    return;
  }

  void Claw::raiseClaw() {
	int bigServoPos = this->bigServo.read();
    for (int pos = bigServoPos; pos <= UPPOS; pos++){
      this->bigServo.write(pos);
      delay(15);
    }
  }

  int Claw::readSmallServo(){
    return this->smallServo.read();
  }

  int Claw::readbigServo(){
    return this->bigServo.read();
  }

  void Claw::writeSmallServo(int pos){
    this->smallServo.write(pos);
  }

  void Claw::writeBigServo(int pos){
    this->bigServo.write(pos);
  }