#ifndef INIT_h
#define INIT_h
#endif

/* MAIN HEADER FILE
** - Includes ALL pin variables
** - Includes all other header files
** - 
*/

#include "Wire.h"
#include "Arduino.h"
#include <Adafruit_SSD1306.h>
#include <Ultrasonic.h>

#define TRUE 1
#define FALSE 0


/* NOTE
** Pin notation:
** Use underscore for analog (?)
*/

//BLUEPILL OUTPUTS//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Motor Pins
#define MOTOR_LF PB_8 //left
#define MOTOR_LB PB_9 //left
#define MOTOR_RF PA_3 //right
#define MOTOR_RB PA_2 //right

// Motor Parameters
#define MAX_MOTOR 65535
#define MOTOR_RATIO 0.9    //Ratio of Right:Left
#define FREQUENCY 500
#define TURN_SPEED 0.7

// Sonar Parameters
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// For Claw Servo
#define SMALLSERVO_PIN PA_7

// For Arm Servo
#define BIGSERVO_PIN PA_8

// Servo Parameters
#define MAXANGLE_SMALL 180
#define MAXANGLE_BIG 120
#define CLOSEPOS 0// check that your servo is oriented this way - it may be the opposite
#define OPENPOS 180
#define DOWNPOS 0
#define UPPOS 50
#define SPEED_SMALL 3
#define SPEED_BIG 1

// Display Settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // This display does not have a reset pin accessible


//BLUEPILL INPUTS//////////////////////////////////////////////////////////////////////////////////////////////////////////

// For Sonar
#define TRIGGER_PIN PB5
#define ECHO_PIN PB4
#define TIMEOUT 15000UL
#define NEAR 100 //cm
    
// IR Sensors
#define IR_LA PB1
#define IR_LB PB0
#define IR_RA PA1
#define IR_RB PA0
#define IR_NOISE 250
#define IR_BIN 1000
#define ANALOG_MAX 1023
 

// Tape Sensors
#define TAPE_L PA5
#define TAPE_R PA4
#define NONE 0
#define T_LEFT 1
#define T_RIGHT 2
#define T_BOTH 3
#define P_LEFT 4
#define P_RIGHT 5
#define P_BOTH 6
#define UPPER_THRES 900 // the "highest" value for floor, "lowest" for tape
#define LOWER_THRES 300 // the "highest" value for paper

// Pins and Buttons
#define SWITCH PB13
#define BUTTON PB14
