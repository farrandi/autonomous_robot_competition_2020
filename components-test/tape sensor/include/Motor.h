#ifndef Motor_h
#define Motor_h
#endif

#include "Arduino.h"

#define MOTOR_LF PA_3 //left
#define MOTOR_LB PA_2 //left
#define MOTOR_RF PB_8 //right
#define MOTOR_RB PB_9 //right
#define MAX_MOTOR 65535
#define MOTOR_RATIO 1

#define TURNING_SPEED MAX_MOTOR/3*2
#define FREQUENCY 1000

class Motor{
    public:
        // Constructors
        Motor();
        Motor(PinName left_f, PinName left_b, PinName right_f, PinName right_b);

        // Drives motors forward
        void drive_forward(int speed);

        // Drives motors backwards
        void drive_backward(int speed);

        //
        void drive_cw();
        void drive_ccw();
        void stop();

        void random_turn();
};