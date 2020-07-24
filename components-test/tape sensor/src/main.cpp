#include "Arduino.h"
#include "Adafruit_SSD1306.h"

#include <Motor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TAPE_SENSOR_R PA4
#define TAPE_SENSOR_L PA5
#define SWITCH A7

Motor motor;

volatile double reflectance_L = 0.0;
volatile double reflectance_R = 0.0;
volatile double threshold = 500.0;
volatile bool tape = false;

void disp_setup();

void setup() {
  // put your setup code here, to run once:
  pinMode(TAPE_SENSOR_R, INPUT);
  pinMode(TAPE_SENSOR_L, INPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  disp_setup();
}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);

  if(digitalRead(SWITCH) == HIGH){
    display.println("On");
    reflectance_L = analogRead(TAPE_SENSOR_L);
    reflectance_R = analogRead(TAPE_SENSOR_R);

    display.print("Left: ");
    display.println(reflectance_L);
    display.print("Right: ");
    display.println(reflectance_R);

    if (reflectance_L > threshold && reflectance_R > threshold){
      display.println("Tape Detected! (front)");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(900);
      motor.drive_ccw();
      delay(1000);
    } else if (reflectance_L > threshold){
      display.println("Tape Detected! (left)");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(800);
      motor.drive_cw();
      delay(600);
    } else if (reflectance_R > threshold){
      display.println("Tape Detected! (right)");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(800);
      motor.drive_ccw();
      delay(600);
    }

    motor.drive_forward(10);
    display.println("Driving around...");
    display.display();
  }

  if (digitalRead(SWITCH) == LOW){
    motor.stop();
    display.println("Off");
    display.display();
  }
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}