/*

 Simon Says Project
 
 Uses a speaker, four LEDs and four switches to play
 a game of "Simon Says" with the user. An additional
 switch can be used for resetting the game.
 
 */

#include "Arduino.h"
#include "pins.h"
#include "Input.h"
#include "Output.h"
#include "Modes.h"

Mode* currentMode;
int curTime, prevTime;

void setup()
{
  Input::Get();
  Output::Get();
  currentMode = new AttractMode();
  prevTime = millis();
}


void loop()
{
  curTime = millis();
  int dT = curTime - prevTime;
  prevTime = curTime;
  
  Input::Get().Update();
  
  Mode* newMode = currentMode->Update(dT);
  if(newMode != currentMode)
    delete currentMode;
  currentMode = newMode;
}


