#ifndef Claw_h
#define Claw_h
#endif

#include <INIT.h>

class Claw
{
public:
    Claw();
    void setup();
    void openClaw();
    void closeClaw();
    void lowerClaw();
    void raiseClaw();
    int readSmallServo();
    int readbigServo();
    void writeSmallServo(int pos);
    void writeBigServo(int pos);
    
};