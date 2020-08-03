<<<<<<< HEAD
#include "INIT.h"
#include <Display.h>

// void disp_setup();
// void disp_reset();

#define ANALOG_MAX 1023
#define MAX_I 200
#define SPEED MAX_MOTOR/10*6

#define ERROR_RANGE 10


//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Display disp;

volatile short int kp = 6;
volatile short int kd = 0;
volatile short int ki = 0;

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
  pinMode(IR_LA, INPUT);
  pinMode(IR_LB, INPUT);
  pinMode(IR_RA, INPUT);
  pinMode(IR_RB, INPUT);

  disp.setup();
  // pinMode(A7, INPUT_PULLUP);


  // disp_setup();
}

// void disp_setup()
// {
//   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(0, 0);
// }

// void disp_reset()
// {
//   display.clearDisplay();
//   display.setCursor(0, 0);
// }

void loop()
{
  // disp_reset();
  left_high = analogRead(IR_LA);
  left_low = analogRead(IR_LB);
  right_high = analogRead(IR_RA);
  right_low = analogRead(IR_RB);

  if (left_high > ANALOG_MAX)
  {
    left = left_low;
  }
  else
  {
    left = left_high;
  }
=======
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

Display myDisp;
Motor myMotor;
Claw myClaw;

void setup() {
  myDisp.setup();
}

void loop() {
  prev_state = state;
>>>>>>> 7c132714873f53004ef8de7d758466cb71f25058

  switch (state)
  {
<<<<<<< HEAD
    right = right_high;
  }

  disp.taggedValue("Left (H):",left_high);
  disp.taggedValue("Left (L):",left_low);

  disp.taggedValue("Right (H):",right_high);
  disp.taggedValue("Right (L):",right_low);

disp.clear();


  // display.print("A1: ");
  // display.println(left_high);
  // display.print("A0: ");
  // display.println(left_low);

  // display.print("B1: ");
  // display.println(right_high);
  // display.print("B0: ");
  // display.println(right_low);

  // display.display();
=======
  default:

    if (sonar == 'Y')
    {
      state = HEAD;
      break;
    }
    else
    {
      break;
    }
>>>>>>> 7c132714873f53004ef8de7d758466cb71f25058

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

<<<<<<< HEAD
      // display.print("Error: ");
      // display.println(err);
      // display.print("Gain: ");
      // display.println(G);

      // display.display();
=======
    if (can == 'N')
    {
      state = SEARCH;
      break;
    }
    else
    {

      state = HOME;
      break;
>>>>>>> 7c132714873f53004ef8de7d758466cb71f25058
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
