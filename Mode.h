#ifndef MODE_H
#define MODE_H

#include "Arduino.h"

class Mode
{
public:
  virtual Mode* Update(int dT);
  virtual ~Mode() {}
};


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


class GameMode :
public Mode
{
public:
  GameMode(int difficulty);
  virtual Mode* Update(int dT);
  virtual ~GameMode() {}
private:
  int mDifficulty;
};


class DelayMode :
public Mode
{
public:
  DelayMode(Mode* next, int delayTime);
  virtual Mode* Update(int dT);
  virtual ~DelayMode() {}
private:
  Mode* mNext;
  int mDelay;
};


#endif



