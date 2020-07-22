#include "Arduino.h"
#include "Adafruit_SSD1306.h"

#include <Motor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TAPE_SENSOR PA5
#define SWITCH A7

Motor motor;

volatile double reflectance = 0.0;
volatile double threshold = 500.0;
volatile bool tape = false;

void disp_setup();

void setup() {
  // put your setup code here, to run once:
  pinMode(TAPE_SENSOR, INPUT);
  pinMode(SWITCH, INPUT_PULLDOWN);
  disp_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(SWITCH) == HIGH){
    reflectance = analogRead(TAPE_SENSOR);
    if (reflectance > threshold){
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("On");
      display.println("Tape Detected!");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(500);
      motor.drive_ccw();
      delay(500);
    }
    motor.drive_forward(5);

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
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}