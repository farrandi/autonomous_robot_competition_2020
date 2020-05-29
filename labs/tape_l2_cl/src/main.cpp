#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
#define OBJECT_SENSOR PA5

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(OBJECT_SENSOR, INPUT);
  Serial.begin(9600);
}

void loop()
{
  double reflectance = analogRead(OBJECT_SENSOR);
  double threshold = 100;

  Serial.println(reflectance);
  if (reflectance > threshold){
    Serial.println("No object here");
  } else {
    Serial.println("Object detected!");
  }
  delay(1000);
}