#include <Wire.h>
#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN  PA15  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     PB3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define servoPin PA6
#define maxAngle 120

#define OPEN 1
#define CLOSE 0

Servo myServo;
int pos = 0;
int i = 0;
int distance = 0;
int state = OPEN;

void disp_setup();

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  disp_setup();
  myServo.attach(servoPin);
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  delay(250);                     // Wait 500ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance = sonar.ping_cm();
  display.print("Ping: ");
  display.print(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  display.println("cm");
  display.display();

  if((distance>10 || distance <6)){
    if (state == CLOSE){
      display.println("open");
      display.display();
      for (i = 0; i<maxAngle-1; i+=2){
        myServo.write(i);
        delay(15);
      } 
      state = OPEN;
    } else {
      myServo.write(0);
      state = OPEN;
    }
  }else if(state == OPEN){
    display.println("close");
    display.display();
    for(i = maxAngle; i >0; i-=2){
      myServo.write(i);
      delay(15);
    }
    state = CLOSE;
  }else{
    myServo.write(maxAngle);
    state = CLOSE;
  }
}