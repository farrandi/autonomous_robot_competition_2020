#include <INIT.h>
#include <Motor.h>
#include <Claw.h>
#include <Display.h>
#include <Sensors.h>

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
Sensors sensors;
Ultrasonic sonar(TRIGGER_PIN, ECHO_PIN, 15000UL);

//INITIALIZING TIMER CONSTANTS
const unsigned int sonarInterval = 20;    // the interval between sonar pings
unsigned long currentMillis = 0;          // the value of millis in the current iteration of the loop
unsigned long previousSonarMillis = 0;    // the previous valut of the sonar millis.
volatile unsigned int sonarReading;       // the sonarReading value in cm
unsigned int sonarThreshold = 120;        // the sonar threshold value for detecting objects
const int clawRangeLB = 5;               // the claw range lower bound
const int clawRangeUB = 12;               // the claw range upper bound

//INITIALIZING MISC
volatile unsigned int tape = 0;

//INITIALIZING PID CONSTANTS
const unsigned int kp = 34;
const unsigned int kd = 100;
const unsigned int ki = 0;
const unsigned int MAX_I = 120;
volatile unsigned int P = 0;
volatile unsigned int D = 0;
volatile unsigned int I = 0;
volatile unsigned int G = 0;
volatile signed int err = 0;
volatile short int prevErr = 0;         // PID previous error

bool avoid();
bool ping();
bool search();
bool pickUp();
bool checkCan();
bool returnToBin();
void dropCan();

void setup() {
  myDisp.setup();
  myClaw.setup();
  sensors.setup();
  
  pinMode(SWITCH, INPUT_PULLUP);
}

void loop() {
  prev_state = state;
  currentMillis = millis();

  tape = sensors.on_tape();
  if (tape > 0 && tape < 4)
    state = AVOID;

  if (digitalRead(SWITCH)==HIGH){
    state = OFF;
  }

  if (digitalRead(BUTTON) == HIGH){
    state = FUN;
  }

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
  case HOME:

  if (checkCan() == false)
    {
      state = SEARCH;
      break;
    }

    if (returnToBin() == true)
    {
      state = DROP;
      break;
    }
    else
    {
      break;
    }

  case DROP:
    dropCan();
    state = SEARCH;
    break;
  case AVOID:
    if (tape == 1){

    }

    void tapeRejectionTest(){
  int left_reflection = sensors.tape_l();
  int right_reflection = sensors.tape_r();
  disp_label_value("left: ", left_reflection);
  disp_label_value("right: ", right_reflection);
  disp_label_value("threshold: ", TAPE_THRES);

  if (left_reflection > TAPE_THRES){
    robotMotor.drive_cw();
  } else if (right_reflection > TAPE_THRES){
    robotMotor.drive_ccw();
  } else {
    robotMotor.drive_forward(5);
  }
}

void tapeRejectionTestSylvia(){
  int left_reflection = sensors.tape_l();
  int right_reflection = sensors.tape_r();
  disp_label_value("left: ", left_reflection);
  disp_label_value("right: ", right_reflection);
  disp_label_value("threshold: ", TAPE_THRES);

  if (left_reflection < TAPE_THRES){
    robotMotor.drive_cw();
  } else if (right_reflection < TAPE_THRES){
    robotMotor.drive_ccw();
  } else {
    robotMotor.drive_forward(5);
  }
}
    state = prev_state;
    break;
  case FUN:
    // insert ur fun function here :)
    break;
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
    myDisp.println("Searching...");
    myDisp.taggedValue("Sonar reading: ", sonarReading);
  }

  return false;
}

bool pickUp() {
  myDisp.clear();
  if (checkCan()) {

     // claw actions
     myDisp.println("Opening claw");
     myClaw.open();     // ensures the claw is open
     delay(500);
     myDisp.println("Lowering arm");
     myClaw.lower();    // ensures the claw arm is down
     delay(500);
     myDisp.println("Closing claw");
     myClaw.close();    // closes claw to grab can
     delay(1000);
     myDisp.println("Raising arm");
     myClaw.raise();    // raises the claw arm
     delay(1000);
     
     return checkCan();

  }

  return false;
 
}
bool checkCan() {

  sonarReading = sonar.read();   // for the can is still in range
     
     // if the following is true, the can is properly placed in our claw
    if (sonarReading <= clawRangeUB && sonarReading >= clawRangeLB) {
      return true;
    }

  return false;

}

bool returnToBin() {

  //checks if the can is in the claw otherwise return to searching
  if (!checkCan()) {
    return false;
  }
  // int kp = 34;
  // int kd = 100;
  // int ki = 0;

  P = 0;
  D = 0;
  I = 0;
  G = 0;

  err = sensors.ir_error();

  myDisp.clear();

  // The current implementation for determining we are in bin range is unknown at the moment.
  // The code below does not have a stop, and only follows IR.

  // if (checkTape() == 4) {

  //   myMotor.stop();
  //   myDisp.println("At bin!");
  //   return true;
  //} else 
  if (!sensors.ir_noise()) {
    myMotor.stop_back(); // need this to ensure the rotate component from search doesn't cross in

    P = kp * err;
    D = kd * (err - prevErr);
    I = (ki * err) + I;
    if (I > MAX_I)
      I = MAX_I;
    if (I < -MAX_I)
      I = -MAX_I;
    G = P + D + I;

    myDisp.taggedValue("gain = ",G);
    myDisp.taggedValue("Left:", sensors.ir_l());
    myDisp.taggedValue("Right:", sensors.ir_r());
    float left_speed = 4.5/10*MAX_MOTOR - G;
    float right_speed = 4.5/10*MAX_MOTOR + G;
    pwm_start(MOTOR_LF,FREQUENCY, left_speed, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF,FREQUENCY, right_speed, RESOLUTION_16B_COMPARE_FORMAT);

    myDisp.taggedValue("Right Speed:", right_speed);
    myDisp.taggedValue("Left Speed:", left_speed);

    prevErr = err;
  } else {
    myMotor.drive_ccw();
    myDisp.println("searching...");
  }

  return false;

}

void dropCan() {

  myClaw.lower();       // lowering the claw arm
  myClaw.open();        // opening the claw to drop
  
  myMotor.drive_cw();   // turning robot around
  delay(1000);          // play around with the delay, we want a 180 turn ideally
  myMotor.stop();
}

