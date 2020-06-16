#include <Arduino.h>

#define NUM_BITS 1024
#define Vin 3.3

#define POT_IN PA_7
#define MOTOR_1 PA_3
#define MOTOR_2 PA_2

void setup() {
  // put your setup code here, to run once:
  pinMode(POT_IN, INPUT);
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, o run repeatedly:
  float v_pot = analogRead(POT_IN);
  pwm_start(MOTOR_2, 1024, v_pot, RESOLUTION_10B_COMPARE_FORMAT);
  Serial.print("Duty Cycle:");
  Serial.print(v_pot/1024*100);
  Serial.println("%");
  delay(1000);
}