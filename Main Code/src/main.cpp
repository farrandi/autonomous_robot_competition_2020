#include <INIT.h>
#include <Motor.h>
#include <Claw.h>
#include <Display.h>

//STATE CONSTANTS
#define SEARCH 0 //default
#define PICK_UP 1
#define LOOK 2
#define HOME 3
#define DROP 4
#define AVOID 5
#define FUN 6
#define OFF 8
int state = 0;
int prev_state = state;

//INITIALIZING COMPONENTS
Display myDisp;
Motor myMotor;
Claw myClaw;
Ultrasonic sonar(TRIGGER_PIN, ECHO_PIN, 15000UL);

//INITIALIZING TIMER CONSTANTS
const int sonarInterval = 20;             // the interval between sonar pings
unsigned long currentMillis = 0;          // the value of millis in the current iteration of the loop
unsigned long previousSonarMillis = 0;    // the previous valut of the sonar millis.
volatile unsigned int sonarReading;                     // the sonarReading value in cm
int sonarThreshold = 120;                  // the sonar threshold value for detecting objects
const int clawRangeLB = 10;               // the claw range lower bound
const int clawRangeUB = 14;               // the claw range upper bound

bool ping();
bool search();
bool pickUp();

void setup() {
  myDisp.setup();
  myClaw.setup();
}

void loop() {
  prev_state = state;
  currentMillis = millis();

  switch (state)
  {
  default:
    myDisp.taggedValue("Actual reading: ", sonar.read());
    if (search() == true)     // If sonar finds object
    {
      state = PICK_UP;
      break;
    }
    else
    {
      myMotor.drive_forward(5); //not sure if this is necessary
      break;
    }

  case PICK_UP:

    if (pickUp() == false)
    {
      state = SEARCH;
      break;
    }
    else
    {

      state = HOME;
      break;
    }
  // case HOME:

  //   if (can == 'N')
  //   {
  //     state = SEARCH;
  //     break;
  //   }

  //   if (bin == 'Y')
  //   {
  //     state = DROP;
  //     break;
  //   }
  //   else
  //   {
  //     break;
  //   }
  // case DROP:

  //   state = SEARCH;
  //   break;
  // case AVOID:

  //   state = prev_state;
  //   break;
  // case FUN:

  //   break;
  }
}


bool ping() {
  
  if (currentMillis - previousSonarMillis >= sonarInterval) {
    sonarReading = sonar.read();
    previousSonarMillis += sonarInterval;
    if (sonarReading <= sonarThreshold) {
      return true;
    } 
  }
  return false;
}

bool search() {
  
  myDisp.clear();
  if (ping() == true) {
    if (sonarReading >= clawRangeUB) {
      myMotor.drive_forward(5);
      myDisp.println("driving forward...");
      myDisp.taggedValue("Sonar reading: ", sonarReading);
    } else if (sonarReading <= clawRangeLB) {
      myMotor.drive_backward(5);
      myDisp.println("driving backward...");
      myDisp.taggedValue("Sonar reading: ", sonarReading);

    }
    else if (sonarReading <= clawRangeUB && sonarReading >= clawRangeLB) {
      myMotor.stop();
      myDisp.taggedValue("Sonar reading: ", sonarReading);
      myDisp.println("FOUND!");
      return true;
    }
  } else { 
    myMotor.drive_cw();
    myDisp.println("searching...");
    myDisp.taggedValue("Sonar reading: ", sonarReading);
  }

  return false;
}

bool pickUp() {

  sonarReading = sonar.read();    // for checking if the can is still in range

  if (sonarReading <= clawRangeUB && sonarReading >= clawRangeLB) {

     // claw actions
     myClaw.open();     // ensures the claw is open
     myClaw.lower();    // ensures the claw arm is down
     myClaw.close();    // closes claw to grab can
     myClaw.raise();    // raises the claw arm

     sonarReading = sonar.read();   // for checking once more if the can is still in range
     
     // if the following is true, the can is properly placed in our claw
     if (sonarReading <= clawRangeUB && sonarReading >= clawRangeLB) {
       return true;
     }

  }

  return false;
 
}