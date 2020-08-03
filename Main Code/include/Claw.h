#ifndef Claw_h
#define Claw_h
#endif

#include "INIT.h"

class Claw
{
public:
    Claw();
    void setup();
    void openClaw();
    void closeClaw();
    void lowerClaw();
    void raiseClaw();
<<<<<<< HEAD

private:
	// int openPos = (clawMaxAngle-1);
	// int closePos = 0;
	// int downPos = 0
	// int upPos = 90;

    long distance = -1;
    int smallServoPos = -1;
    int bigServoPos = -1;
    static Servo smallServo;
    static Servo bigServo;
=======
    int readSmallServo();
    int readbigServo();
    void writeSmallServo(int pos);
    void writeBigServo(int pos);
    
>>>>>>> 7c132714873f53004ef8de7d758466cb71f25058
};