#include <Arduino.h>
#include <Wire.h>
#include <Motor.h>
#include <Adafruit_SSD1306.h>

Motor motor;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define IR_leftA PB1
#define IR_leftB PB0
#define IR_rightA PA1
#define IR_rightB PA0

#define SWITCH A7

#define Analog_MAX 1023
#define IR_OFFSET 10

volatile int threshold = 100;
volatile float left_high = 0;
volatile float left_low = 0;
volatile float right_high = 0;
volatile float right_low = 0;

volatile float right = 0;
volatile float left = 0;

void disp_setup();
void disp_reset();

void setup() {
  pinMode(IR_leftA, INPUT);
  pinMode(IR_leftB, INPUT);
  pinMode(IR_rightA, INPUT);
  pinMode(IR_rightB, INPUT);
  disp_setup();
  Serial.begin(9600);
  pinMode(SWITCH, INPUT_PULLDOWN);
}

void loop() {
  /*
  // H-bridge debugging code:
  if(digitalRead(SWITCH)==HIGH){
    motor.drive_forward(6);
    disp_reset();
    Serial.println("Driving forward...");
    display.println("Moving forward...");
    display.display();
  } else {
    motor.drive_backward(6);
    disp_reset();
    Serial.println("Driving backward...");
    display.println("Moving backward...");
    display.display();
  }*/
  
  
  /*
  //Motor testing code:
  disp_reset();
  
  motor.drive_forward(10);
  display.println("Driving forward...");
  display.display();
  delay(2000);

  motor.drive_backward(10);
  disp_reset();
  display.println("Driving backward...");
  display.display();
  delay(2000);

  motor.drive_cw();
  disp_reset();
  display.println("Turning CW...");
  display.display();
  delay(3000);
  
  motor.drive_ccw();
  disp_reset();
  display.println("Turning CW...");
  display.display();
  delay(3000);
  } else{
    motor.stop();
    disp_reset();
    display.println("OFF");
    display.display();
  }*/

  
  //IR Sensor code
  disp_reset();
  left_high = analogRead(IR_leftA);
  left_low = analogRead(IR_leftB);
  right_high = analogRead(IR_rightA);
  right_low = analogRead(IR_rightB);
  
  display.print("B1: ");
  display.println(left_high);
  display.print("B0: ");
  display.println(left_low);

  display.print("A1: ");
  display.println(right_high);
  display.print("A0: ");
  display.println(right_low);
  
  if (left_high > Analog_MAX){
    left = left_low;
  } else {
    left = left_high;
  }

  if (right_high > Analog_MAX){
    right = right_low;
  } else {
    right = right_high;
  }
  display.display();

  
  if (digitalRead(SWITCH)){
    if (abs(left-right)<15&&(left>0&&right>0)){
      display.println("Driving forward...");
      motor.drive_forward(10);
    }
    else if (left > right){
      display.println("Turning counter...");
      motor.drive_ccw();
    } else if (right > left){
      display.println("Turning Clockwise...");
      motor.drive_cw();
    } else{
      motor.drive_ccw();
      delay(1000);
    }
    display.display();
  } else{
    motor.stop();
  }

    /*if (left > IR_OFFSET || right > IR_OFFSET){
      if (left > right){
        display.println("Turning counter...");
        motor.drive_ccw();
      } else if (right > left) {
        display.println("Turning clockwise...");
        motor.drive_cw();
      } else if (abs(left-right) > 20){
        display.println("Driving forward...");
        motor.drive_forward(5);
      }
    } else {
      motor.random_turn();
      display.println("Not detecting signal...");
      motor.drive_forward(8);
    }
  } else {
    motor.stop();
    display.println("OFF...");
  }

  display.display();*/
}


void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void disp_reset(){
  delay(300);
  display.clearDisplay();
  display.setCursor(0,0);
}