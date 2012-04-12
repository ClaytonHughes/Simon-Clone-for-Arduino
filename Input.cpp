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

//                             RED,  GREEN,   BLUE, YELLOW
const int colorButtons[] = {SNES_A, SNES_Y, SNES_X, SNES_B};

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


// Buttons that are pressed this frame.
int Input::Buttons()
{
  return curPad;
}


// Buttons that were pressed this frame, but not last
int Input::Pressed()
{
  return curPad & ~prevPad;
}


// Buttons that were not pressed this frame, but were last
int Input::Released()
{
  return ~curPad & prevPad;
}

// Buttons that were pressed both this and last frame
int Input::Held()
{
  return curPad & prevPad;
}


// The Button Flag for the specified color
int Input::SNESCode(Color color)
{
  return colorButtons[color];
}

// State of the Difficulty Switch
Difficulty Input::GetDifficulty()
{
  return digitalRead(DIFF_SWITCH_PIN) == HIGH ? HARD : EASY;
}




