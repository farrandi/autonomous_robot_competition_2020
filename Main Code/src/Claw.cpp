#include <Claw.h>

Claw::Claw(){
    blueServo.attach(servoPinBlue);
    greyServo.attach(servoPinGrey);
    NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  }

  void Claw::openClaw(){
	int blueServoPos = blueServo.read();
    for (int pos = blueServoPos; pos <= openPos; pos++){
      blueServo.write(pos);
      delay(5);
    }
    return;
  }

  void Claw::closeClaw(){
    int blueServoPos = blueServo.read();
	if (blueServoPos!=openPos) {
      openClaw();
    }
    for (int pos = openPos; pos >= closePos; pos--) {
      blueServo.write(pos);
      delay(5);
    }
    return;
  }

  void Claw::lowerClaw() { 
    int greyServoPos = greyServo.read();
	for (int pos = greyServoPos; pos >= downPos; pos--) {
      greyServo.write(pos);
      delay(15);
    }
    return;
  }

  void Claw::raiseClaw() {
	int greyServoPos = greyServo.read();
    for (int pos = greyServoPos; pos <= upPos; pos++){
      greyServo.write(pos);
      delay(15);
    }
  }