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
#define AVOID_ALL 5
#define AVOID_BOUNDARY 6
#define OFF 8
int state = 0;
int prev_state = state;

//INITIALIZING COMPONENTS
Display myDisp;
Motor myMotor;
Claw myClaw;
Sensors sensors;
Ultrasonic sonar(TRIGGER_PIN, ECHO_PIN, TIMEOUT);

//INITIALIZING TIMER CONSTANTS

unsigned long currentMillis = 0;          // the value of millis in the current iteration of the loop
const unsigned int sonarInterval = 25;    // the interval between sonar pings (ms)
const unsigned int searchInterval = 3000; // the interval between search resets (ms)
unsigned long previousSonarMillis = 0;    // the previous value of the sonar millis.
unsigned long previousSearchInterval = 0; // the previous value of the searching millis
volatile unsigned int sonarReading;       // the sonarReading value in cm

/*FILL THE # CONST BELOW*/
unsigned int sonarThreshold = 100;        // the sonar threshold value for detecting objects
const int clawRangeLB = 7;                // the claw range lower bound 
const int clawRangeUB = 11;               // the claw range upper bound

const int dropTime = 1000;                // the rotating time after dropping claw;

//INITIALIZING MISC
volatile unsigned int ReflStatus = 0;

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
volatile short int prevErr = 0;          // PID previous error

void fun_interrupt();
void fun_func();

bool avoid();
bool ping();
bool search();
bool pickUp();
bool checkCan();
bool returnToBin();
void dropCan();
void tapeRejectionA(); //for anything but homing
void tapeRejectionB(); //ReflStatus rejection for homing
bool checkBin(); //checks if it is near trashbin

void setup() {
  myDisp.setup();
  myClaw.setup();
  sensors.setup();
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), fun_interrupt, FALLING);
}

void loop() {
  if (digitalRead(SWITCH) == HIGH) {
    myDisp.print("STATE: ");

    if (prev_state != AVOID_ALL ){ // dont want to recursively state AVOID
      if (prev_state != AVOID_BOUNDARY)
        prev_state = state;
    }

    currentMillis = millis();
    myDisp.clear();

    ReflStatus = sensors.on_tape();

    //basically if in home or drop, avoid ReflStatus BUT not avoid paper
    if ((state == HOME || state == DROP) && (ReflStatus > 0 && ReflStatus < 4)) // for Sylvia: ((state == HOME || state == DROP) && ReflStatus >= 4)
      state = AVOID_BOUNDARY;
    else if (ReflStatus > 0 ) // avoid both ReflStatus AND paper when in any other state
      state = AVOID_ALL;

    myDisp.taggedValue("State:", state);

    switch (state) {

    default: // this is SEARCH
      myClaw.reset();
      myDisp.println("SEARCH");
      myDisp.taggedValue("Actual reading: ", sonar.read());
      if (search() == true) { // If sonar finds object
        state = PICK_UP;
        break;
      }
      break;
      
    case PICK_UP:
      myDisp.println("PICK-UP");
      if (pickUp() == false) {
        state = SEARCH;
        break;
      } else {
        state = HOME;
        break;
      }

    case HOME:
      myDisp.println("HOME");
      if (checkCan() == false) {
        state = SEARCH;
        break;
      }

      if (returnToBin() == true) {
        state = DROP;
        break;
      } else {
        break;
      }

    case DROP:
      myDisp.println("DROP");
      dropCan();
      state = SEARCH;
      break;
    case AVOID_ALL:
      myDisp.println("AVOID_ALL");
      tapeRejectionA();
      state = prev_state;
      break;
    case AVOID_BOUNDARY:
      myDisp.println("AVOID_BOUNDARY");
      tapeRejectionB();
      state = prev_state;
      break;
    }
  } else {
    state = SEARCH;
    myMotor.stop();
    myDisp.clear();
    myDisp.println("OFF");
    myDisp.taggedValue("Left Tape:", sensors.tape_l());
    myDisp.taggedValue("Right Tape:", sensors.tape_r());

  }
}

void fun_interrupt(){ 
  if (digitalRead(SWITCH)==LOW){
    myDisp.clear();
    myDisp.println("fun!");
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
    // Move forward after searchInterval if nothing is detected
    if (currentMillis - previousSearchInterval > searchInterval){
        // TODO: Fine tune this
        myMotor.drive_forward(6);
        delay(20);
        myMotor.stop();
        previousSearchInterval += searchInterval;
    }
    myMotor.drive_cw_slow();
    myDisp.println("Searching...");
    myDisp.taggedValue("Sonar reading: ", sonarReading);
  }

  return false;
}

bool pickUp() {

  myDisp.clear();

  if (checkCan()) {
     // claw actions
     myClaw.reset();
     myDisp.println("Closing claw");
     myClaw.close();    // closes claw to grab can
     myDisp.println("Raising arm");
     myClaw.raise();    // raises the claw arm
     
     return checkCan();
  }

  return false;
 
}

bool checkCan() {

  sonarReading = sonar.read();   // for the can is still in range
  myDisp.println("Checking can...");
     // if the following is true, the can is properly placed in our claw
    if (sonarReading <= clawRangeUB && sonarReading >= clawRangeLB) {
      myDisp.println("Holding can!");
      return true;
    }
  myDisp.println("Dropped can :( ");
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

  if (checkBin() == true) {
    myMotor.stop();
    myDisp.println("At bin!");
    return true;
  } else if (!sensors.ir_noise()) {
    //myMotor.stop_back(); // need this to ensure the rotate component from search doesn't cross in

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

    if (left_speed < MAX_MOTOR*0.4){
      left_speed = MAX_MOTOR*0.4;
    }

    if (right_speed < MAX_MOTOR*0.4){
      right_speed = MAX_MOTOR*0.4;
    }

    pwm_start(MOTOR_LF,FREQUENCY, left_speed, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF,FREQUENCY, right_speed, RESOLUTION_16B_COMPARE_FORMAT);

    myDisp.taggedValue("Right Speed:", right_speed);
    myDisp.taggedValue("Left Speed:", left_speed);

    prevErr = err;
  } else {
    myMotor.drive_forward(5);
    myDisp.println("searching...");
  }

  return false;

}

void dropCan() {
  myDisp.println("Lowering claw...");
  myClaw.lower();       // lowering the claw arm
  myDisp.println("Opening claw...");
  myClaw.open();        // opening the claw to drop
  myDisp.println("Raising claw....");
  myClaw.raise();       // the sonar gets in the way so we raise the claw before turning
  myMotor.drive_backward(8);
  delay(50);
  myMotor.drive_cw();   // turning robot around
  delay(dropTime);          // play around with the delay, we want a 180 turn ideally
  myMotor.stop();
  
}

/** For not homing state
 *  Will avoid both the paper and ReflStatus borders
 */
void tapeRejectionA() { 
  int status = sensors.on_tape();

  if (status == P_LEFT || status == T_LEFT){
    myMotor.drive_cw();
  }
  else if (status == P_RIGHT || status == T_RIGHT) {
    myMotor.drive_ccw();
  }
  else if (status == P_BOTH || status == T_BOTH){
    myMotor.drive_backward(5);
  }
}

/** For homing state
 *  Only avoids Tape
 */
void tapeRejectionB() {
  int status = sensors.on_tape();

  if (status == T_LEFT){
    myMotor.drive_cw();
  }
  else if (status == T_RIGHT) {
    myMotor.drive_ccw();
  }
  else if (status == T_BOTH){
    myMotor.drive_backward(5);
  }
  else
    myMotor.drive_forward(5); 
}

bool checkBin() {
  int status = sensors.on_tape();

  if (status == P_BOTH){
    myMotor.stop();
    return true;
  }
  else if (status == P_RIGHT){
    myMotor.drive_cw_slow();
  }
  else if (status == P_LEFT){
    myMotor.drive_ccw_slow();
  }

  return false;
}
