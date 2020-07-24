#include "INIT.h"

#define OPEN 1
#define CLOSE 0

// Servo myServo;
// int pos = 0;
// int i = 0;
// int distance = 0;
// int state = OPEN;

void disp_setup();

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  disp_setup();
  // myServo.attach(servoPin);
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void loop() {
  // display.clearDisplay();
  // display.setCursor(0,0);
  // delay(250);                     // Wait 500ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  // distance = sonar.ping_cm();
  // display.print("Ping: ");
  // display.print(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  // display.println("cm");
  // display.display();

  // if((distance>10 || distance <6)){
  //   if (state == CLOSE){
  //     display.println("open");
  //     display.display();
  //     for (i = 0; i<maxAngle-1; i+=2){
  //       myServo.write(i);
  //       delay(15);
  //     } 
  //     state = OPEN;
  //   } else {
  //     myServo.write(0);
  //     state = OPEN;
  //   }
  // }else if(state == OPEN){
  //   display.println("close");
  //   display.display();
  //   for(i = maxAngle; i >0; i-=2){
  //     myServo.write(i);
  //     delay(15);
  //   }
  //   state = CLOSE;
  // }else{
  //   myServo.write(maxAngle);
  //   state = CLOSE;
  // }
}