#include "INIT.h"
#include "Motor.h"
#include "Claw.h"

Ultrasonic ultrasonic(TRIGGER_PIN,ECHO_PIN);
Motor robotMotor;
Claw claw;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void disp_setup();
void disp_label_value(const char *label, int value);
void disp_msg(const char *msg);
void disp_clear();
void motorRawStop();

/* TEST FUNCTIONS */
void testDrive(); // (Uses Motor.h) Tests: driving forwards, backwards, turning ccw and cw
void testDriveRaw(); // (Uses PWM) Tests: driving forwards, backwards, turning ccw and cw
void testGrabber(); // Tests //Claw opening and closing
void testArm(); // Tests arm lifting and lowering
void testClawFunctions(); // Uses //Claw.h
void testDriveAndServos(); // (Uses Motor.h)
void testDriveAndServosRaw(); // (Uses PWM)
void testSonar();
void testSonarClawArm();
void testIRreading();
void testTapeReading();

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_LA,INPUT);
  pinMode(IR_LB,INPUT);
  pinMode(IR_RA,INPUT);
  pinMode(IR_RB,INPUT);
  pinMode(TAPE_L, INPUT_PULLUP);
  pinMode(TAPE_R, INPUT_PULLUP);

  disp_setup();
  claw.setup();
}


void loop() {
  // CHOOSE WHICH TEST FUNCTION TO RUN:
  // NOTE: if running the raw motor test files, make sure to comment out lines 2 and 7
  // disp_msg("Driving forward...");
  testSonar();
}



/* COMPONENTS TEST FUNCTIONS */

// (Uses Motor.h) Tests: driving forwards, backwards, turning ccw and cw
void testDrive(){
  robotMotor.drive_forward(5);
  disp_msg("Driving forward...");
  delay(5000);
  robotMotor.drive_backward(5);
  disp_msg("Driving backward...");
  delay(3000);
  robotMotor.drive_ccw();
  disp_msg("Turning ccw...");
  delay(2000);
  robotMotor.drive_cw();
  disp_msg("Turning cw...");
  delay(2000);
} 

// (Uses PWM) Tests: driving forwards, backwards, turning ccw and cw
void testDriveRaw(){
  disp_msg("Driving forward...");
  motorRawStop();
  pwm_start(MOTOR_LF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(5000);
  disp_msg("Driving backward...");
  motorRawStop();
  pwm_start(MOTOR_LB, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(3000);
  disp_msg("Turning ccw...");
  motorRawStop();
  pwm_start(MOTOR_LB, FREQUENCY, MOTOR_RATIO*0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, 0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(2000);
  disp_msg("Turning cw...");
  motorRawStop();
  pwm_start(MOTOR_LF, FREQUENCY, MOTOR_RATIO*0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, 0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(2000);
}

// Tests Claw opening and closing
void testGrabber(){
  claw.openClaw();
  claw.closeClaw();
}

// // Tests arm lifting and lowering
void testArm(){
  claw.raiseClaw();
  claw.lowerClaw();
}

// (Uses Motor.h) Drives, stops, moves servos
void testDriveAndServos(){
  disp_clear();
  disp_msg("Driving...");
  robotMotor.drive_forward(5);
  delay(5000);
  robotMotor.stop();
  delay(300);
  disp_clear();
  disp_msg("Moving servos...");
  for (int i = 0; i < 90; i++) {
    //Claw.writeSmallServo(i);
    //Claw.writeBigServo(i);
    delay(15);
  }
  for (int i = 90; i >= 0; i--) {
    //Claw.writeSmallServo(i);
    //Claw.writeBigServo(i);
    delay(15);
  }
}

// (Uses PWM) Drives, stops, moves servos
void testDriveAndServosRaw(){
  disp_clear();
  disp_msg("Driving...");
  pwm_start(MOTOR_LF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(5000);
  motorRawStop();
  delay(300);

  disp_clear();
  disp_msg("Moving servos...");
  for (int i = 0; i < 90; i++) {
    //Claw.writeSmallServo(i);
    //Claw.writeBigServo(i);
    delay(15);
  }
  for (int i = 90; i >= 0; i--) {
    //Claw.writeSmallServo(i);
    //Claw.writeBigServo(i);
    delay(15);
  }
}

// Reads the sonar reading
void testSonar(){
  disp_clear();
  disp_label_value("Distance (cm): ",ultrasonic.read());
  delay(500);
}

// Tests if servo can actuate based on servo readings
void testSonarClawArm(){
  int distance = ultrasonic.read();
  disp_label_value("Dist (cm): ", distance);
  //Claw.openClaw();
  //Claw.closeClaw();

  if(distance<8 && distance>3) {
    disp_msg("Can detected!\n //Claw closing...");
    //Claw.closeClaw();
    //Claw.raiseClaw();
    delay(2000);
    disp_msg("releasing //Claw...");
    //Claw.lowerClaw();
    //Claw.openClaw();
  }
}

void testIRreading(){
  disp_clear();
  disp_label_value("LEFT IR HI: ", analogRead(IR_LA));
  disp_label_value("LEFT IR LO: ", analogRead(IR_LB));
  disp_label_value("RIGHT IR HI: ", analogRead(IR_RA));
  disp_label_value("RIGHT IR LO: ", analogRead(IR_RB));
  delay(500);
}

void testTapeReading(){
  disp_clear();
  disp_label_value("Left Sensor: ",analogRead(TAPE_L));
  disp_label_value("Right Sensor: ",analogRead(TAPE_R));
  delay(500);
}

/* OTHER DISPLAY FUNCTIONS */

void motorRawStop(){
  pwm_start(MOTOR_LF, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_LB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  delay(50);
}

/* DISPLAY FUNCTIONS */

void disp_setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

}

void disp_label_value(const char *label, int value){
  display.print(label);
  display.println(value);
  display.display();
}

void disp_msg(const char *msg) {
  display.println(msg);
  display.display();  
}

void disp_clear() {
  display.clearDisplay();
  display.setCursor(0, 0);
}