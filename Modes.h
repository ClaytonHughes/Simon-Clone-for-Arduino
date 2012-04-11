#ifndef MODE_H
#define MODE_H

#include "Arduino.h"

// Represents the mode or state of the application
class Mode
{
public:
  virtual Mode* Update(int dT) {return this;}
  virtual ~Mode() {}
};


/////////////////////////////////////////////////

// Play some lights, and check for the easter egg code
// This will eventually start the game mode.
class AttractMode : 
public Mode
{
public:
  AttractMode();
  virtual Mode* Update(int dT);
  virtual ~AttractMode() {}
private:
  boolean CheckEasterEgg(int pressed);
  void UpdateLights(int dT);
  int easterEggPos;
  int attractLightPos;
  int time;
};


/////////////////////////////////////////////////

// Once the game has started.
class GameMode :
public Mode
{
public:
  GameMode(int difficulty);
  virtual Mode* Update(int dT);
  virtual ~GameMode() {}
private:
  int turnsUntilWin;
  int LEDDisplayTime;
  int delayBetweenLights;
};


/////////////////////////////////////////////////

// Causes a delay in transition between modes
class DelayMode :
public Mode
{
public:
  DelayMode(Mode* next, int delayTime) {mNext = next; mDelay = delayTime;}
  virtual Mode* Update(int dT) { mDelay -= dT; if(mDelay <= 0) { return mNext; } else { return this; } }
  virtual ~DelayMode() {}
private:
  Mode* mNext;
  int mDelay;
};


#endif



