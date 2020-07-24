#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_SSD1306.h>
#include <Motor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN PA15 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN PB3     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define CLAWDISTANCE 12  // The ideal distance for the claw to be away from the sonar.

Motor robotMotor;

void disp_setup();
void disp_dist(int dist);
bool sweepSearch();
void sweep(int direction);
bool headToCan();
int getMinIndex(int array[]);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

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
    objectDetected = sweepSearch();
  }
  if (objectDetected)
  {
    atCan = headToCan();
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
    delay(2000);
    return true;
  }
  else
  {
    display.println("No object detected...");
    display.display();
    sweep(1);
    delay(500);
    return false;
  }
  
}

void sweep(int direction)
{

  if (direction == 1)
  {
    robotMotor.stop();
    delay(1000);
    robotMotor.drive_cw();
    delay(1000);
    robotMotor.stop();
  }
  else
  {
    robotMotor.stop();
    delay(1000);
    robotMotor.drive_ccw();
    delay(1000);
    robotMotor.stop();
  }
}

bool headToCan()
{
  int lbdistance = 10;
  int ubdistance = 16;
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
      robotMotor.drive_forward(50);
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
      robotMotor.drive_backward(10);
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
