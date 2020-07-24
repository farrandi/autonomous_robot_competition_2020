#ifndef INIT_h
#define INIT_h
#endif

#include "Wire.h"
#include "Arduino.h"
#include <NewPing.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// Motor Pins
#define MOTOR_LF PA_3 //left
#define MOTOR_LB PA_2 //left
#define MOTOR_RF PB_8 //right
#define MOTOR_RB PB_9 //right

// Motor Parameters
#define MAX_MOTOR 65535
#define MOTOR_RATIO 0.7
#define FREQUENCY 1000

// For Sonar
#define TRIGGER_PIN PB_5
#define ECHO_PIN PB_4

// Sonar Parameters
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// For Claw Servo
#define servoPinBlue PA7

// For Arm Servo
#define servoPinGrey PA8

// Servo Parameters
#define maxAngleBlue 180
#define maxAngleGrey 120
#define armMaxAngle 100
#define closePos 0 // check that your servo is oriented this way - it may be the opposite
#define openPos (maxAngleBlue-1)
#define downPos 0
#define upPos 90

// Display Settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible

// IR Sensors
#define IR_leftA PA1
#define IR_leftB PA0
#define IR_rightA PB1
#define IR_rightB PB0

// Tape Sensors
#define TAPE_left PA_5
#define TAPE_right PA_4

// Control
#define SWITCH PB14
#define BUTTON PB13