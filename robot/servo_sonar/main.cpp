#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#include <servo.h>
#include <Arduino.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define servoPin PA6
#define maxAngle 180

#define closePos 0 // check that your servo is oriented this way - it may be the opposite
#define openPos (maxAngle-1)

void disp_setup();
void disp_dist(int dist);
void openClaw(int servoPos);
void closeClaw(int servoPos);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo myServo;
int distance = 0;
int servoPos = -1;

void setup() {
  myServo.attach(servoPin);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();
  delay(2000);
}

void loop() {
  disp_setup();
  delay(500);                     // Wait 500ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance = sonar.ping_cm();
  disp_dist(distance);

  servoPos = myServo.read();

  // claw should always be open unless it is grabbing can
  if (servoPos != openPos) {
    openClaw(servoPos);
    servoPos = openPos;
  }

  // if can is in range, grab claw and hold on to it for 3 seconds, then release
  if(distance<13 && distance>3) {
    display.println("Can detected! Claw closing...");
    display.display();
    closeClaw(servoPos);
    servoPos = closePos;
    delay(3000);
    display.println("releasing claw...");
    display.display();
    openClaw(servoPos);
  }
}

void openClaw(int servoPos){
  for (int pos = servoPos; pos <= openPos; pos++){
    myServo.write(pos);
    delay(5);
  }
  return;
}

void closeClaw(int servoPos){
  if (servoPos!=openPos) {
    openClaw(servoPos);
  }
  for (int pos = openPos; pos >= closePos; pos--) {
    myServo.write(pos);
    delay(5);
  }
  return;
}

void disp_setup() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void disp_dist(int dist){
  display.print("Ping: ");
  display.print(dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
  display.println("cm");
  display.display();
}





