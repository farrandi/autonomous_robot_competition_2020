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
int sonarReading = 0;                     // the sonarReading value in cm
int sonarThreshold = 50;                  // the sonar threshold value for detecting objects
const int clawRangeLB = 10;               // the claw range lower bound
const int clawRangeUB = 14;               // the claw range upper bound

bool ping();
bool search();

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

    if (sonarFind == 'Y')     // If sonar finds object
    {
      state = HEAD;
      break;
    }
    else
    {
      //add a drive forward?
      break;
    }

  case HEAD:

    if (can == 'N')
    {
      state = SEARCH;
      break;
    }
    else
    {
      if (close == 'Y')
      {
        state = PICK_UP;
        break;
      }
      else
      {
        break;
      }
    }
  case PICK_UP:

    if (can == 'N')
    {
      state = SEARCH;
      break;
    }
    else
    {

      state = HOME;
      break;
    }
  case HOME:

    if (can == 'N')
    {
      state = SEARCH;
      break;
    }

    if (bin == 'Y')
    {
      state = DROP;
      break;
    }
    else
    {
      break;
    }
  case DROP:

    state = SEARCH;
    break;
  case AVOID:

    state = prev_state;
    break;
  case FUN:

    break;
  }
}


bool ping() {
  bool objectDetected = false;
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
  if (ping() == true) {
    if (sonarReading >= clawRangeUB) {
      myMotor.drive_forward(5);
    } else if (sonarReading <= clawRangeLB) {
      myMotor.drive_backward(5);
    }
    else if (sonarReading <= clawRangeUB && sonarReading >= clawRangeLB) {
      myMotor.stop();
      return true;
    }
  } else { 
    myMotor.drive_cw();
  }

}