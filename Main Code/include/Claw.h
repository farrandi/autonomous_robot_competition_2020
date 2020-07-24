#ifndef Claw_h
#define Claw_h
#endif

#include "INIT.h"

// For Sonar on Claw
#define TRIGGER_PIN PB_5
#define ECHO_PIN PB_4
#define MAX_DISTANCE 320

// For Claw Servo
#define servoClawPin PA7
#define clawMaxAngle 120
#define clawSpeed 2

// For Arm Servo
#define servoArmPin PA8
#define armMaxAngle 100

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

    long distance = -1;
    int blueServoPos = -1;
    int greyServoPos = -1;
};