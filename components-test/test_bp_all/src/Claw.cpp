#include <Claw.h>

Servo smallServo;
Servo bigServo;

Claw::Claw()
{
  smallServo.attach(SMALLSERVO_PIN);
  bigServo.attach(BIGSERVO_PIN);
}

void Claw::openClaw()
{
  int smallServoPos = smallServo.read();
  for (int pos = smallServoPos; pos <= OPENPOS; pos++)
  {
    smallServo.write(pos);
    delay(5);
  }
}

void Claw::closeClaw()
{
  int smallServoPos = smallServo.read();
  if (smallServoPos != OPENPOS)
  {
    openClaw();
  }
  for (int pos = OPENPOS; pos >= CLOSEPOS; pos--)
  {
    smallServo.write(pos);
    delay(5);
  }
}

void Claw::lowerClaw()
{
  int bigServoPos = bigServo.read();
  for (int pos = bigServoPos; pos >= DOWNPOS; pos--)
  {
    bigServo.write(pos);
    delay(15);
  }
}

void Claw::raiseClaw()
{
  int bigServoPos = bigServo.read();
  for (int pos = bigServoPos; pos <= UPPOS; pos++)
  {
    bigServo.write(pos);
    delay(15);
  }
}

int Claw::readSmallServo()
{
  return smallServo.read();
}

int Claw::readbigServo()
{
  return bigServo.read();
}

void Claw::writeSmallServo(int pos)
{
  smallServo.write(pos);
}

void Claw::writeBigServo(int pos)
{
  bigServo.write(pos);
}