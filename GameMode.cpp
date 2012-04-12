#include "Modes.h"
#include "Output.h"
#include "Input.h"

// Gameplay elements
const int easyModeTurns = 7;
const int hardModeTurns = 11;
const int superHardModeTurns = 15;

//                            easy  hard  secret
const int turnsToWin[]     = {   7,   11,  15 };
const int ledDisplayTime[] = { 200,  200,  75 };
const int lightDelay[]     = { 200,  200,  75 };
const int fireworksCount[] = {   0,    3,   6 };

class State : 
public Mode
{
public:
  State(GameMode& game);
  virtual Mode* Update(int dT);

protected:
    GameMode& mGame;
};

class ShowSeqState : 
public State
{
public:
  ShowSeqState(GameMode& game);
  virtual Mode* Update(int dT);
private:
  int seqShow;
  int time;
};

class ReadSeqState : 
public State
{
public:
  ReadSeqState(GameMode& game);
  virtual Mode* Update(int dT);
private:
  int correct;
};

State::State(GameMode& game)
:
mGame(game)
{
}


/////////////////////////////////////////////////
// Showing the Sequence

ShowSeqState::ShowSeqState(GameMode& game)
: 
State(game),
seqShow(0),
time(0)
{
  mGame.colorChain[mGame.turnNo] = (Color)random(0,4);
  ++mGame.turnNo;
}

Mode* ShowSeqState::Update(int dT)
{ 
  time += dT;
  if((mGame.LEDDisplayTime + mGame.delayBetweenLights) * seqShow < time)
  {
    // enough time has passed, we should start the next light/sound in the sequence:
    Output::Get().LightOn(mGame.colorChain[seqShow], mGame.LEDDisplayTime);
    Output::Get().SetTone(mGame.colorChain[seqShow], mGame.LEDDisplayTime);
  }
  seqShow++;

  if(seqShow == mGame.turnNo)
  {
    // hit the end of the sequence, transition to reading input state:
    return new ReadSeqState(mGame);
  }

  return this;
}


/////////////////////////////////////////////////
// Reading the Sequence
ReadSeqState::ReadSeqState(GameMode& game)
: 
State(game),
correct(0)
{
}

Mode* ReadSeqState::Update(int dT)
{  
  // turn off lights/sounds as they're released.
  int released = Input::Get().Released();
  if(released)
  {
    if(released & Input::Get().SNESCode(RED))
      Output::Get().LightOff(RED);
    if(released & Input::Get().SNESCode(GREEN))
      Output::Get().LightOff(GREEN);
    if(released & Input::Get().SNESCode(BLUE))
      Output::Get().LightOff(BLUE);
    if(released & Input::Get().SNESCode(YELLOW))
      Output::Get().LightOff(YELLOW);
  }

  // handle new input
  int pressed = Input::Get().Pressed();
  if(pressed)
  {
    Color expectedColor = mGame.colorChain[correct];
    if(pressed == Input::Get().SNESCode(expectedColor))
    {
      Output::Get().LightOn(expectedColor);
      ++correct;
    }
    else
    {
      mGame.condition = GameMode::Defeat;
    }
  }
  
  if(correct == mGame.turnNo)
  {
    if(correct == mGame.turnsUntilWin)
      mGame.condition = GameMode::Victory;
    return new ShowSeqState(mGame);
    
  }
  
  return this;
}


// when input is received:
  // play the light/color that they're pressing
  // if it's right:
    // if the sequence is not yet complete:
      // keep going
    // else, sequence is done:
      // transition to playing back sequence / win
  // if it's wrong:
    // transition to losing melody



/////////////////////////////////////////////////
// Game

GameMode::GameMode(Difficulty difficulty)
:
condition(StillPlaying),
turnNo(0)
{
  turnsUntilWin = turnsToWin[difficulty];
  LEDDisplayTime = ledDisplayTime[difficulty];
  delayBetweenLights = lightDelay[difficulty];
  fireworks = fireworksCount[difficulty];
}


Mode* GameMode::Update(int dT)
{
  // Manage our own state -- waiting for input, or playing back a sequence.
  State* newState = (State*)curState->Update(dT);
  if(newState != curState)
  {
    delete curState;
    curState = newState;
  }

  switch(condition)
  {
    case Victory:
      return new MelodyMode((Melody)(WIN + fireworks), new AttractMode());
      break;
    case Defeat:
      return new MelodyMode(LOSE, new AttractMode());    
      break;
  }
 
  return this;
}

