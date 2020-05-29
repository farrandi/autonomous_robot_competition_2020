/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
#define OBJECT_SENSOR PA5

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OBJECT_SENSOR, INPUT);
  Serial.begin(115200);
}

void loop()
{
  double reflectance = analogRead(OBJECT_SENSOR);
  double threshold = 100;
  if (reflectance > threshold){
    Serial.println("No object here");
  } else {
    Serial.println("Object detected!");
  }
}