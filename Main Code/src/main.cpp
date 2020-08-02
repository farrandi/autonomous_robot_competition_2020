#include <INIT.h>
#include <Motor.h>
#include <Claw.h>

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

void setup()
{
}

void loop()
{
  prev_state = state;

  switch (state)
  {
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
