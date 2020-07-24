#include "INIT.h"
#include "Motor.h"

void disp_setup();
void disp_reset();

#define ANALOG_MAX 1023
#define MAX_I 200
#define SPEED MAX_MOTOR / 10 * 5

#define ERROR_RANGE 5

Motor motor;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile short int kp = 5;
volatile short int kd = 10;
volatile short int ki = 2;

volatile short int P = 0;
volatile short int D = 0;
volatile short int I = 0;
volatile short int G = 0;

volatile short int err = 0;
volatile short int prev = 0;

volatile unsigned short int left;
volatile unsigned short int right;
volatile unsigned short int left_high;
volatile unsigned short int left_low;
volatile unsigned short int right_high;
volatile unsigned short int right_low;

void setup()
{
  pinMode(IR_leftA, INPUT);
  pinMode(IR_leftB, INPUT);
  pinMode(IR_rightA, INPUT);
  pinMode(IR_rightB, INPUT);
  pinMode(A7, INPUT_PULLUP);
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

void loop()
{
  disp_reset();
  left_high = analogRead(IR_leftA);
  left_low = analogRead(IR_leftB);
  right_high = analogRead(IR_rightA);
  right_low = analogRead(IR_rightB);

  if (left_high > ANALOG_MAX)
  {
    left = left_low;
  }
  else
  {
    left = left_high;
  }

  if (right_high > ANALOG_MAX)
  {
    right = right_low;
  }
  else
  {
    right = right_high;
  }

  display.print("A1 (L_hi): ");
  display.println(left_high);
  display.print("A0 (L_lo): ");
  display.println(left_low);

  display.print("B1 (R_hi): ");
  display.println(right_high);
  display.print("B0 (R_lo): ");
  display.println(right_low);

  display.display();

  // if (digitalRead(PA7) == HIGH)
  // {
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
    display.display();
  }
  // else
  // {
  //   display.println("OFF");
  //   display.display();
  // }
// }