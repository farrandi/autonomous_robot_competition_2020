#include <Motor.h>

/* Empty Constructor for Motor class that sets up the defined pins for output. */
Motor::Motor(){
    pinMode(MOTOR_1F, OUTPUT);
    pinMode(MOTOR_1B, OUTPUT);
    pinMode(MOTOR_2F, OUTPUT);
    pinMode(MOTOR_2B, OUTPUT);
}

/* Constructor for Motor class that sets up parameters as pins for output.
 * @param: PinName left_f is pin name reference for the forward left motor PWM signal,
 * likewise for the remaining pins
 */
Motor::Motor(PinName left_f, PinName left_b, PinName right_f, PinName right_b){
    pinMode(left_f, OUTPUT);
    pinMode(left_b, OUTPUT);
    pinMode(right_f, OUTPUT);
    pinMode(right_b, OUTPUT);
}

/* Makes robot drive forward at a speed 
 * @param: int speed, from 1-10, speed of motor is MAX_MOTOR*speed/11
 */
void Motor::drive_forward(int speed){
  pwm_start(MOTOR_1B, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2B, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  delay(50);
  pwm_start(MOTOR_1F, FREQUENCY, speed * MAX_MOTOR/11, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2F, FREQUENCY, speed * MAX_MOTOR/11, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot drive backward at a speed 
 * @param: int speed, from 1-10, speed of motor is MAX_MOTOR*speed/11
 */
void Motor::drive_backward(int speed){
  pwm_start(MOTOR_1F, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2F, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  delay(50);
  pwm_start(MOTOR_1B, FREQUENCY, speed * MAX_MOTOR/11, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2B, FREQUENCY, speed * MAX_MOTOR/11, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate clockwise (right)*/
void Motor::drive_cw(){
  pwm_start(MOTOR_1B, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2F, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  delay(50);
  pwm_start(MOTOR_1F, FREQUENCY, MAX_MOTOR/2, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2B, FREQUENCY, MAX_MOTOR/2, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate counter-clockwise (left)*/
void Motor::drive_ccw(){
  pwm_start(MOTOR_1F, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2B, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  delay(50);
  pwm_start(MOTOR_1B, FREQUENCY, MAX_MOTOR/2, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2F, FREQUENCY, MAX_MOTOR/2, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Stops both motors*/
void Motor::stop(){
    pwm_start(MOTOR_1F, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_1B, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_2F, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_2B, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
}