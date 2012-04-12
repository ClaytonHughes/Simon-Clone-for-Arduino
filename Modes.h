#ifndef MODE_H
#define MODE_H

#include "Arduino.h"
#include "gameplay.h"


// Represents the mode or state of the application
class Mode
{
public:
  virtual Mode* Update(int dT)
  {
    return this;
  }
  virtual ~Mode() {
  }
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
  virtual ~AttractMode() {
  }
private:
  boolean CheckEasterEggCode(int pressed);
  void UpdateLights(int dT);
  int easterEggPos;
  int attractLightPos;
  int time;
};


/////////////////////////////////////////////////

class State;
class ShowSeqState;
class ReadSeqState;

// Once the game has started.
class GameMode :
public Mode
{
public:
  GameMode(Difficulty difficulty);
  virtual Mode* Update(int dT);
  virtual ~GameMode() {
  }
private:
  State* curState;
  
  enum Condition
  {
    StillPlaying = 0,
    Defeat,
    Victory
  };
  
  Condition condition;
  
  int turnNo;
  
  int turnsUntilWin;
  int LEDDisplayTime;
  int delayBetweenLights; // Wait this time (ms) between light display; changes depending on difficulty mode
  int fireworks;
  
  Color colorChain[100];

  friend class ShowSeqState;
  friend class ReadSeqState;
};


/////////////////////////////////////////////////

// Causes a delay in transition between modes
class DelayMode :
public Mode
{
public:
  DelayMode(int delayTime, Mode* next)
  {
    mNext = next; 
    mDelay = delayTime;
  }
  virtual Mode* Update(int dT)
  { 
    mDelay -= dT; 
    if(mDelay <= 0) 
      return mNext; 
    return this; 
  }
  virtual ~DelayMode() {
  }
private:
  Mode* mNext;
  int mDelay;
};


/////////////////////////////////////////////////

class Note;

// Plays a song and goofs around with lights
class MelodyMode :
public Mode
{
public:
  MelodyMode(Melody melody, Mode* next);
  virtual Mode* Update(int dT);     

private:
  Mode* mNext;
  
  const Note* notes;
  int tempo;
  int length;
  
  Color color;
  int note;
  int nextTime;
  int time;
  
  int fireworks;

  void StartTone(int freq, int duration);
  void PlayFireworks(int count);
};


#endif





