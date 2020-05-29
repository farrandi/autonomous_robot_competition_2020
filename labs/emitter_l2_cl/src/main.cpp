#include <Arduino.h>

#include <Wire.h>
#define INTERRUPTPIN PA5

void handle_interrupt();
volatile int threshold = 100;
volatile int reflectance = 0;

void setup() {
  pinMode(INTERRUPTPIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Reflectance: ");
  Serial.println(reflectance);
  reflectance = analogRead(INTERRUPTPIN);
  if (reflectance > threshold) {
    Serial.println("nothing detected");
  } else {
    Serial.println("object detected");
  }
  delay(300);
};