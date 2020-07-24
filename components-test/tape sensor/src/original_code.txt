#include "Arduino.h"
#include <Motor.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Motor motor;

#define TAPE_SENSOR_L PA5
#define TAPE_SENSOR_R PA4
#define SWITCH A7

void disp_setup();

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(TAPE_SENSOR_L, INPUT);
  pinMode(TAPE_SENSOR_R, INPUT);
  disp_setup();
}

volatile float left = 0.0;
volatile float right = 0.0;

volatile double threshold = 500.0;
volatile bool l_on = false;
volatile bool r_on = false;
volatile bool cond = false;
volatile int tape = 1;

void loop()
{
  if(digitalRead(SWITCH) == HIGH){
    reflectance = analogRead(TAPE_SENSOR);
    if (reflectance > threshold){
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("On");
      display.println("Tape Detected!");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(800);
      motor.drive_ccw();
      delay(800);
    }
    motor.drive_forward(8);

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("On");
    display.println("Driving around...");
    display.display();
  }

  if (digitalRead(SWITCH) == LOW){
    motor.stop();
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Off");
    display.display();
  }
  // if(digitalRead(SWITCH) == HIGH){
  //   left = analogRead(TAPE_SENSOR_L);
  //   right = analogRead(TAPE_SENSOR_R);
    
  //   display.clearDisplay();
  //   display.setCursor(0,0);
  //   display.println("On");
  //   display.print("Left: ");
  //   display.println(left);
  //   display.print("Right: ");
  //   display.println(right);
  //   display.display();

  //   l_on = left > threshold;
  //   r_on = right > threshold;

  //   switch(tape){
  //     case 1:
  //     motor.drive_forward(10);
  //     if (l_on){
  //       if (r_on) {
  //         tape = 2;
  //       } else {
  //         tape = 3;
  //       }
  //     }
  //     if (r_on){
  //       tape = 4;
  //     }
  //     case 2: // Both tapes detected
  //       display.println("Both Detected!");
  //       display.display();
  //       motor.stop();
  //       motor.drive_backward(8);
  //       delay(1000);
  //       motor.drive_cw();
  //       delay(2000);
  //       motor.stop();
  //       tape = 1;
      
  //     case 3: 
  //       display.println("Left Detected!");
  //       display.display();
  //       motor.stop();
  //       motor.drive_backward(8);
  //       delay(1000);
  //       motor.drive_cw();
  //       delay(1000);
  //       motor.stop();
  //       tape = 1;

  //     case 4:
  //       display.println("Left Detected!");
  //       display.display();
  //       motor.stop();
  //       motor.drive_backward(8);
  //       delay(1000);
  //       motor.drive_cw();
  //       delay(1000);
  //       motor.stop();
  //       tape = 1;
  //   }
  }
  else {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Off");
    display.display();

    motor.stop();
  }
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}