#include "Modes.h"

// Gameplay elements
const int easyModeTurns = 7;
const int hardModeTurns = 11;
const int superHardModeTurns = 15;

                          // easy  hard  secret
const int turnsToWin[]     = {  7,   11,  15};
const int ledDisplayTime[] = {200,  200,  75};
const int lightDelay[]     = {200,  200,  75};

GameMode::GameMode(int difficulty)
{
  turnsUntilWin = turnsToWin[difficulty];
  LEDDisplayTime = ledDisplayTime[difficulty];
  delayBetweenLights = lightDelay[difficulty];
}


Mode* GameMode::Update(int dT)
{
  return this;
}
