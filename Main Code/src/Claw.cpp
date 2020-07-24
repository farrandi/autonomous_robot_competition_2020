#include <Claw.h>

Claw::Claw(){
    blueServo.attach(BLUESERVO_PIN);
    greyServo.attach(GREYSERVO_PIN);
    NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  }

  void Claw::openClaw(){
	int blueServoPos = blueServo.read();
    for (int pos = blueServoPos; pos <= OPENPOS; pos++){
      blueServo.write(pos);
      delay(5);
    }
    return;
  }

  void Claw::closeClaw(){
    int blueServoPos = blueServo.read();
	if (blueServoPos != OPENPOS) {
      openClaw();
    }
    for (int pos = OPENPOS; pos >= CLOSEPOS; pos--) {
      blueServo.write(pos);
      delay(5);
    }
    return;
  }

  void Claw::lowerClaw() { 
    int greyServoPos = greyServo.read();
	for (int pos = greyServoPos; pos >= DOWNPOS; pos--) {
      greyServo.write(pos);
      delay(15);
    }
    return;
  }

  void Claw::raiseClaw() {
	int greyServoPos = greyServo.read();
    for (int pos = greyServoPos; pos <= UPPOS; pos++){
      greyServo.write(pos);
      delay(15);
    }
  }