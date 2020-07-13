#include <Arduino.h>

#define POT_IN PA_7
#define MOTOR_1F PA_2
#define MOTOR_1B PA_1
#define MOTOR_2F PB_8
#define MOTOR_2B PB_9

void setup() {
  // put your setup code here, to run once:
  pinMode(POT_IN, INPUT);
  pinMode(MOTOR_1F, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(MOTOR_2F, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);
  pinMode(A7, INPUT_PULLDOWN);
}

void loop() {
  // put your main code here, o run repeatedly:
  while(digitalRead(A7) == HIGH){
  
  pwm_start(MOTOR_1F, 1000, 32768, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2F, 1000, 32768, RESOLUTION_16B_COMPARE_FORMAT);
  delay(10000);
  pwm_start(MOTOR_1F, 1000, 0, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2F, 1000, 0, RESOLUTION_16B_COMPARE_FORMAT);

  pwm_start(MOTOR_1B, 1000, 32768, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2B, 1000, 32768, RESOLUTION_16B_COMPARE_FORMAT);
  delay(5000);
  pwm_start(MOTOR_1B, 1000, 0, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_2B, 1000, 0, RESOLUTION_16B_COMPARE_FORMAT);
  }
}