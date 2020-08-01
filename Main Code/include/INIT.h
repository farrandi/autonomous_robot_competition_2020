#ifndef INIT_h
#define INIT_h
#endif

#include "Wire.h"
#include "Arduino.h"
#include <NewPing.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

//BLUEPILL OUTPUTS//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Motor Pins
#define MOTOR_LF PB_8 //left
#define MOTOR_LB PB_9 //left
#define MOTOR_RF PA_3 //right
#define MOTOR_RB PA_2 //right

// Motor Parameters
#define MAX_MOTOR 65535
#define MOTOR_RATIO 0.85 //Ratio of Right:Left
#define FREQUENCY 1000

// Sonar Parameters
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// For Claw Servo
#define SMALLSERVO_PIN PA7

// For Arm Servo
#define BIGSERVO_PIN PA8

// Servo Parameters
#define MAXANGLE_BLUE 180
#define MAXANGLE_GREY 120
#define CLOSEPOS 0 // check that your servo is oriented this way - it may be the opposite
#define OPENPOS (MAXANGLE_BLUE-1)
#define DOWNPOS 0
#define UPPOS 90

// Display Settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // This display does not have a reset pin accessible


//BLUEPILL INPUTS//////////////////////////////////////////////////////////////////////////////////////////////////////////

// For Sonar
#define TRIGGER_PIN PB_5
#define ECHO_PIN PB_4

// IR Sensors
#define IR_LA PB_1
#define IR_LB PB_0
#define IR_RA PA_1
#define IR_RB PA_0

// Tape Sensors
#define TAPE_L PA_5
#define TAPE_R PA_4

// Control
#define SWITCH PB14
#define BUTTON PB13