#ifndef Claw_h
#define Claw_h
#endif

#include "INIT.h"

// For Sonar on Claw
#define TRIGGER_PIN PB5
#define ECHO_PIN PB4
#define MAX_DISTANCE 320

// For Claw Servo
#define servoClawPin PA7
#define clawMaxAngle 180
#define clawSpeed 2

// For Arm Servo
#define servoArmPin PA8
#define armMaxAngle 120

class Claw
{
public:
    Claw();
    void openClaw(int blueServoPos);
    void closeClaw(int blueServoPos);
    void lowerClaw(int greyServoPos);
    void raiseClaw(int greyServoPos);

private:
    Servo blueServo;
    Servo greyServo;
	
	int openPos = (clawMaxAngle-1);
	int closePos = 0;
	int downPos = 0;
	int upPos = 90;

    long distance = -1;
    int blueServoPos = -1;
    int greyServoPos = -1;
};