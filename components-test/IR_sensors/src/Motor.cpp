#include <Motor.h>

/* Empty Constructor for Motor class that sets up the defined pins for output. */
Motor::Motor(){
    pinMode(MOTOR_LF, OUTPUT);
    pinMode(MOTOR_LB, OUTPUT);
    pinMode(MOTOR_RF, OUTPUT);
    pinMode(MOTOR_RB, OUTPUT);
}

/* Makes robot drive forward at a speed 
 * @param: int speed, from 1-10, speed of motor is MAX_MOTOR*speed/11
 */
void Motor::drive_forward(int speed){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LF, FREQUENCY, (4+(speed*0.6))/11*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, (4+(speed*0.6))/11*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot drive backward at a speed 
 * @param: int speed, from 1-10, speed of motor is MAX_MOTOR*speed/11
 */
void Motor::drive_backward(int speed){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LB, FREQUENCY, (4+(speed*0.6))/11*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, (4+(speed*0.6))/11*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate clockwise (right)*/
void Motor::drive_cw(){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LF, FREQUENCY, TURNING_SPEED, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, TURNING_SPEED, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate counter-clockwise (left)*/
void Motor::drive_ccw(){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LB, FREQUENCY, TURNING_SPEED, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, TURNING_SPEED, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Stops both motors*/
void Motor::stop(){
    pwm_start(MOTOR_LF, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_LB, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RB, 0,0,RESOLUTION_16B_COMPARE_FORMAT);
}

void Motor::random_turn(){
  int action = random(0,2);

  if (action == 0){
    this->stop();
    this->drive_ccw();
    delay(random(1,500));
  } else if (action == 1){
    this->stop();
    this->drive_cw();
    delay(random(1,500));
  } else if (action == 2){
    this->stop();
    this->drive_backward(10);
  }
}