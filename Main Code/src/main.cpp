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
const unsigned int sonarInterval = 25;    // the interval between sonar pings (ms)
unsigned long currentMillis = 0;          // the value of millis in the current iteration of the loop
unsigned long previousSonarMillis = 0;    // the previous valut of the sonar millis.
volatile unsigned int sonarReading;       // the sonarReading value in cm
unsigned int sonarThreshold = 120;        // the sonar threshold value for detecting objects
const int clawRangeLB = 5;                // the claw range lower bound
const int clawRangeUB = 12;               // the claw range upper bound
const int dropTime = 1000;                // the rotating time after dropping claw;

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
void tapeRejectionB(); //tape rejection for homing
bool checkPaper(); //checks if it is near trashbin

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

    prev_state = state;
    currentMillis = millis();
    myDisp.clear();
    myDisp.taggedValue("Left Tape:", sensors.tape_l());
    myDisp.taggedValue("Right Tape:", sensors.tape_r());
    tape = sensors.on_tape();

    if (state != HOME || state != DROP) {
      if (tape > 0) {
        state = AVOID;
      }
      else if (tape > 0 && tape < 4) {
        state = AVOID;
      }
    }

    myDisp.taggedValue("State:", state);

    switch (state) {

    default:
      myDisp.println("SEARCH");
      myDisp.taggedValue("Actual reading: ", sonar.read());
      if (search() == true) { // If sonar finds object
        state = PICK_UP;
        break;
      }
      else {
        myMotor.drive_forward(5); //not sure if this is necessary
        break;
      }

    case PICK_UP:
      myDisp.println("PICK-UP");
      if (pickUp() == false) {
        state = SEARCH;
        break;
      } else {
        state = HOME;
        break;
      }
<<<<<<< HEAD

=======
>>>>>>> f28a2494999efeb9ede7e17097d5202a06a0460e
    case HOME:
      myDisp.println("HOME");
      if (checkCan() == false) {
        myClaw.lower();
        myClaw.open();
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
    case AVOID:
      myDisp.println("AVOID");
      if (prev_state == HOME) {
        tapeRejectionB();
      }
      else {
        tapeRejectionA();
      }
      state = prev_state;
      break;

    case FUN:
      myDisp.println("FUN");
      fun_func();
      state = SEARCH;
      break;
    }
  } else {
    myMotor.stop();
    myDisp.clear();
    myDisp.println("OFF");
<<<<<<< HEAD
  }
}

void fun_interrupt(){
  state = FUN;
}

void fun_func(){
  // insert ur fun function here 
  for (int i = 0; i < 100; i++){
        myDisp.print(i);
=======
>>>>>>> f28a2494999efeb9ede7e17097d5202a06a0460e
  }
  delay(5000);
}

void fun_interrupt(){
  state = FUN;
}

void fun_func(){
  // insert ur fun function here 
  for (int i = 0; i < 100; i++){
        myDisp.print(i);
  }
  delay(5000);
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

  if (checkPaper() == true) {
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
  myDisp.println("Lowering claw...");
  myClaw.lower();       // lowering the claw arm
  myDisp.println("Opening claw...");
  myClaw.open();        // opening the claw to drop
  myDisp.println("Raising claw....");
  myClaw.raise();       // the sonar gets in the way so we raise the claw before turning
  myMotor.drive_cw();   // turning robot around
  delay(dropTime);          // play around with the delay, we want a 180 turn ideally
  myMotor.stop();
  myClaw.lower();       // lowering claw once again
  
}

/** For not homing state
 *  Will avoid both the paper and tape borders
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

bool checkPaper() {
  int status = sensors.on_tape();

  if (status == P_BOTH){
    myMotor.stop();
    return true;
  }
  else if (status == P_RIGHT){
    myMotor.drive_cw();
    delay(300);
  }
  else if (status == P_LEFT){
    myMotor.drive_ccw();
    delay(300);
  }

  return false;
}
