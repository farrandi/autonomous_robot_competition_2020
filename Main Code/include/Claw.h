#ifndef Claw_h
#define Claw_h
#endif

#include "INIT.h"

// For Sonar on Claw

// For Claw Servo

// For Arm Servo

class Claw
{
public:
    Claw();
    void openClaw();
    void closeClaw();
    void lowerClaw();
    void raiseClaw();

private:
    Servo smallServo;
    Servo bigServo;
	
	// int openPos = (clawMaxAngle-1);
	// int closePos = 0;
	// int downPos = 0
	// int upPos = 90;

    long distance = -1;
    int smallServoPos = -1;
    int bigServoPos = -1;
};