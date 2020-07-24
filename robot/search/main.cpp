#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_SSD1306.h>
#include <Motor.h>
#include <Claw.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Motor robotMotor;
Claw robotClaw;

void disp_setup();
void disp_dist(int dist);
bool sweepSearch();
void sweep();
bool headToCan();

volatile int count = 0;

void setup()
{
  disp_setup();
}

bool atCan = false;
bool objectDetected = false;
void loop()
{
  //robotMotor.drive_forward(11);
  //delay(3000);
  display.clearDisplay();
  display.setCursor(0, 0);
  if (!atCan)
  {
    robotClaw.openClaw();
    objectDetected = sweepSearch();
    count++;
  }
  if (objectDetected)
  {
    count = 0;
    atCan = headToCan();
  } 
  if (atCan) {
    robotClaw.closeClaw();
    display.clearDisplay();
    display.println("Grabbing can...");
    display.display();
  }

}

bool sweepSearch()
{

  int sonarReading = sonar.ping_cm();
  disp_dist(sonarReading);
  if (sonarReading < 50)
  {
    display.println("Object Detected!");
    display.display();
    delay(500);
    return true;
  }
  else
  {
    display.println("No object detected...");
    display.display();
    sweep();
    delay(500);
    return false;
  }
  
}

void sweep()
{
  int sweepTime = 500;
  int direction = count % 2;
  if (count % 3 == 0) {
    sweepTime = 1000; 
  }
  if (count % 5 == 0) {
    sweepTime = 2000;
  }
  if (direction == 1)
  {
    robotMotor.stop();
    delay(sweepTime);
    robotMotor.drive_cw();
    delay(sweepTime);
    robotMotor.stop();
  }
  else
  {
    robotMotor.stop();
    delay(sweepTime);
    robotMotor.drive_ccw();
    delay(sweepTime);
    robotMotor.stop();
  }
}

bool headToCan()
{
  int lbdistance = 10;
  int ubdistance = 14;
  int sonarReading = sonar.ping_cm();

  if (sonarReading > ubdistance || sonarReading < lbdistance)
  {
    if (sonarReading > ubdistance)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      disp_dist(sonarReading);
      display.println("Heading to can...");
      display.display();
      robotMotor.drive_forward(8);
      delay(500);
      robotMotor.stop();
    }
    else if (sonarReading < lbdistance)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      disp_dist(sonarReading);
      display.println("Heading to can...");
      display.display();
      robotMotor.drive_backward(8);
      delay(500);
      robotMotor.stop();
    }
    else if (sonarReading <= ubdistance && sonarReading >= lbdistance)
    {
      robotMotor.stop();
      return true;
    }
  }
  else if (sonarReading < ubdistance && sonarReading > lbdistance)
  {
    return true;
  }
  return false;
}

void disp_setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void disp_dist(int dist)
{
  display.print("Ping: ");
  display.print(dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
  display.println("cm");
  display.display();
}
