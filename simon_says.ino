/*

 Simon Says Project
 
 Uses a speaker, four LEDs and a Super Famicon controller
 to play a game of "Simon Says" with the user. An additional
 switch controls the difficulty of the game.
 
 */

#include "Arduino.h"
#include "Input.h"
#include "Output.h"
#include "Modes.h"

Mode* currentMode;
int curTime, prevTime;

void setup()
{
  // Invoke ctor through Singleton:
  Input::Get();
  Output::Get();
  
  // Initialize mode and time for loop.
  currentMode = new AttractMode();
  prevTime = millis();
}


void loop()
{
  curTime = millis();
  int dT = curTime - prevTime;
  // Compensate for millis() wrapping back to zero.
  if(curTime < prevTime)
    dT--;
  prevTime = curTime;
    
  Input::Get().Update();
  
  Mode* nextMode = currentMode->Update(dT);
  if(nextMode != currentMode)
  {
    delete currentMode;
    currentMode = nextMode;
  }
  
  Output::Get().Update(dT);
}


