/* 
 Functions to handle button input on the Arduino.
 */

#include "Arduino.h"
#include "Input.h"
#include "SNESpad.h"
#include "pins.h"
#include "gameplay.h"
#include "Modes.h"

Input* Input::spInstance = NULL;

Input::Input()
:
curPad(0),
prevPad(0)
{
  pinMode(DIFF_SWITCH_PIN, INPUT);  
  padInput = new SNESpad(SNESPAD_STROBE_PIN, SNESPAD_CLOCK_PIN, SNESPAD_DATA_PIN);

  // Use unconnected analog pin 1 as a random seed
  randomSeed(analogRead(A1));

  spInstance = this;
}

Input& Input::Get()
{
  if(NULL == spInstance)
    spInstance = new Input();

  return *spInstance;
}

void Input::Update()
{
  prevPad = curPad;
  curPad = padInput->buttons();
}

int Input::Buttons()
{
  return padInput->buttons();
}

int Input::Pressed()
{
  return curPad & ~prevPad;
}

int Input::Released()
{
  return ~curPad & prevPad;
}

int Input::Held()
{
  return curPad & prevPad;
}

int Input::Difficulty()
{
  return digitalRead(DIFF_SWITCH_PIN) == HIGH ? HARD : EASY;
}

// Returns the button being pressed by the user. If no button
// is being pressed, returns -1.
int Input::getPressedColor()
{
  // First update buttons states to make sure that we
  // get the most recent information
  //updateButtonStates();

  // Now, get the button that's been pressed. If multiple
  // buttons are pressed, get the first one in order.
  //if (red_button_state)
  //{
  // return 0;
  //}
  //else if (green_button_state)
  //{
  //  return 1;
  //}
  //else if (blue_button_state)
  //{
  //  return 2;
  //}
  //else if (yellow_button_state)
  //{
  //  return 3;
  //}
  //else
  //{
  //  return -1;
  //}
}

// Updates the current state for all of the color buttons
void Input::updateButtonStates()
{
//  int state = padInput->buttons();
//  red_button_state = state & SNES_A;
//  green_button_state = state & SNES_Y;
//  blue_button_state = state & SNES_X;
//  yellow_button_state = state & SNES_B; 
}

// Checks to see if a certain button is being pressed
boolean Input::isPressed(int color)
{
//  switch (color)
//  {
//  case 0:
//    return red_button_state;
//    break;
//  case 1:
//    return green_button_state;
//    break;
//  case 2:
//    return blue_button_state;
//    break;
//  case 3:
//    return yellow_button_state;
//    break;
//  default:
//    return false;
//  }
}


