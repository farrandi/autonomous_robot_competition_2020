#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#define MOTOR_1F PA_2 //left
#define MOTOR_1B PA_1 //left
#define MOTOR_2F PB_8 //right
#define MOTOR_2B PB_9 //right
#define MAX_MOTOR 65535

#define FREQUENCY 1000

class Motor
{
public:
    // Drives motors forward
    void drive_forward(int speed);

    // Drives motors backwards
    void drive_backward(int speed);

    //
    void drive_cw();
    void drive_ccw();
    void stop();
}