#include "INIT.h"
#include "Motor.h"

void disp_setup();
void disp_reset();

#define ANALOG_MAX 1023
#define MAX_I 200
#define SPEED MAX_MOTOR / 10 * 5

#define ERROR_RANGE 10
#define NOISE 10
#define STOP_RANGE 950

Motor motor;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile short int kp = 20;
volatile short int kd = 20;
volatile short int ki = 2;

volatile short int P = 0;
volatile short int D = 0;
volatile short int I = 0;
volatile short int G = 0;

volatile short int err = 0;
volatile short int prev = 0;

volatile unsigned short int l;
volatile unsigned short int r;
volatile unsigned short int left;
volatile unsigned short int right;
volatile unsigned short int left_high;
volatile unsigned short int left_low;
volatile unsigned short int right_high;
volatile unsigned short int right_low;

// volatile int honing = 1;

volatile double reflectance_L = 0.0;
volatile double reflectance_R = 0.0;
volatile double threshold = 500.0;

void setup()
{
  pinMode(IR_leftA, INPUT);
  pinMode(IR_leftB, INPUT);
  pinMode(IR_rightA, INPUT);
  pinMode(IR_rightB, INPUT);
  pinMode(PB14, INPUT_PULLUP);
//   pinMode(TAPE_right, INPUT);
//   pinMode(TAPE_left, INPUT);
  disp_setup();
}

void disp_setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void disp_reset()
{
  display.clearDisplay();
  display.setCursor(0, 0);
}

int leftReading();
int rightReading();
void checkTape();
void IR_honing(int left, int right);

void loop()
{
  disp_reset();
  l = leftReading();
  r = rightReading();
  display.display();

  if (digitalRead(PB14) == HIGH)
  {
    IR_honing(l,r);
    // checkTape();
    // switch(honing){
    //   case 1: 
    //     IR_honing(l,r);
    //     if
    // }  
    display.display();
  }
  else
  {
    display.println("OFF");
    display.display();
    pwm_start(MOTOR_LF, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
  }
}

int leftReading()
{
  left_high = analogRead(IR_leftA);
  left_low = analogRead(IR_leftB);

  if (left_high > ANALOG_MAX)
    left = left_low;
  else
    left = left_high;

  display.print("A1 (L_hi): ");
  display.println(left_high);
  display.print("A0 (L_lo): ");
  display.println(left_low);

  return left;
}
int rightReading()
{
  right_high = analogRead(IR_rightA);
  right_low = analogRead(IR_rightB);

  if (right_high > ANALOG_MAX)
    right = right_low;
  else
    right = right_high;

  display.print("B1 (R_hi): ");
  display.println(right_high);
  display.print("B0 (R_lo): ");
  display.println(right_low);

  return right;
}

void IR_honing(int left, int right)
{
  if (left < NOISE && right < NOISE)
  {
    pwm_start(MOTOR_LF, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
    display.println("Noise...");
    display.display();
  }
  else if (left > STOP_RANGE && right > STOP_RANGE)
  {
    pwm_start(MOTOR_LF, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);
    display.println("At beacon!");
    display.display();
  }
  else
  {
    err = left - right;

    if (err < ERROR_RANGE && err > -ERROR_RANGE)
    {
      pwm_start(MOTOR_LF, FREQUENCY, SPEED, RESOLUTION_16B_COMPARE_FORMAT);
      pwm_start(MOTOR_RF, FREQUENCY, SPEED, RESOLUTION_16B_COMPARE_FORMAT);
      display.println("Running forward...");
      display.display();
    }
    else
    {
      P = kp * err;
      D = kd * (err - prev);
      I = (ki * err) + I;
      if (I > MAX_I)
        I = MAX_I;
      if (I < -MAX_I)
        I = -MAX_I;
      G = P + D + I;
      if (err > 0)
      {
        pwm_start(MOTOR_LF, FREQUENCY, SPEED - G, RESOLUTION_16B_COMPARE_FORMAT);
        pwm_start(MOTOR_RF, FREQUENCY, SPEED + G, RESOLUTION_16B_COMPARE_FORMAT);
        display.println("L > R");
        display.display();
      }
      else
      {
        pwm_start(MOTOR_LF, FREQUENCY, SPEED + G, RESOLUTION_16B_COMPARE_FORMAT);
        pwm_start(MOTOR_RF, FREQUENCY, SPEED - G, RESOLUTION_16B_COMPARE_FORMAT);
        display.println("R > L");
        display.display();
      }
      prev = err;
    }
  }
}

void checkTape(){
    reflectance_L = analogRead(TAPE_left);
    reflectance_R = analogRead(TAPE_right);

    display.print("Left: ");
    display.println(reflectance_L);
    display.print("Right: ");
    display.println(reflectance_R);

    if (reflectance_L > threshold && reflectance_R > threshold){
      display.println("Tape Detected! (front)");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(900);
      motor.drive_ccw();
      delay(1000);
    } else if (reflectance_L > threshold){
      display.println("Tape Detected! (left)");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(800);
      motor.drive_cw();
      delay(600);
    } else if (reflectance_R > threshold){
      display.println("Tape Detected! (right)");
      display.display();
      
      motor.stop();
      motor.drive_backward(9);
      delay(800);
      motor.drive_ccw();
      delay(600);
    }
}