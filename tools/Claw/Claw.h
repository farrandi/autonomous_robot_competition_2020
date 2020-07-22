#ifndef Claw_h
#define Claw_h

#include "Arduino.h"
#include "Servo.h"

// For Claw Servo
#define servoClawPin PA7
#define clawMaxAngle 120
#define clawSpeed 2

// For Arm Servo
#define servoArmPin PA8
#define armMaxAngle 100

Class Claw(){
    public:
        Claw();
        void open(int speed);
        void close(int speed);
        void open();
        void close();
    private:
        Servo clawServo;
        Servo armServo;
        volatile int position;
};