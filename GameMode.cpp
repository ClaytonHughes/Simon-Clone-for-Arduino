#include "Modes.h"
#include "Output.h"
#include "Input.h"

// Gameplay elements
const int easyModeTurns = 7;
const int hardModeTurns = 11;
const int superHardModeTurns = 15;

// easy  hard  secret
const int turnsToWin[]     = {  
  7,   11,  15};
const int ledDisplayTime[] = {
  200,  200,  75};
const int lightDelay[]     = {
  200,  200,  75};

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
  GameMode& game;
};

State::State(GameMode& game)
:
mGame(game)
{
}


ShowSeqState::ShowSeqState(GameMode& game)
: 
State(game),
seqShow(0),
time(0)
{
  mGame.colorChain[mGame.turnNo] = random(0,4);
}

Mode* ShowSeqState::Update(int dT)
{
  time += dT;
  if((mGame.LEDDisplayTime + mGame.delayBetweenLights) * seqShow < time)
  {
    // enough time has passed, we should start the next light/sound in the sequence:
    Output::Get().SetLight(mGame.colorChain[seqShow], mGame.LEDDisplayTime);
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

GameMode::GameMode(int difficulty)
{
  turnsUntilWin = turnsToWin[difficulty];
  LEDDisplayTime = ledDisplayTime[difficulty];
  delayBetweenLights = lightDelay[difficulty];
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

  // [else] if waiting for input, and input is received:
  // play the light/color that they're pressing
  // if it's right:
  // if the sequence is not yet complete:
  // keep going
  // else, sequence is done:
  // transition to playing back sequence / win
  // if it's wrong:
  // transition to losing melody

}

