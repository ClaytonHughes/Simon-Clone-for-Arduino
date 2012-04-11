#include "Modes.h"
#include "gameplay.h"
#include "SNESPad.h"
#include "Input.h"
#include "Output.h"

const int easterEggCheatCode[] = { SNES_UP, SNES_UP, SNES_DOWN, SNES_DOWN, SNES_LEFT, SNES_RIGHT, SNES_LEFT, SNES_RIGHT, SNES_B, SNES_A, SNES_START };
const int easterEggCheatCodeLength = sizeof(easterEggCheatCode) / sizeof(easterEggCheatCode[0]);
const int attractLEDDisplayTime = 120; // Time to show LED in ms during attract mode 
const int attractModeColors[] = { 2, 1, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2, 2, 2, 2, 0, 3, 1, 2, 0, 3, 1, 2, 0, 3, 1, 2, 2, 2 };
const int attractModeColorsLength = sizeof(attractModeColors) / sizeof(attractModeColors[0]);

AttractMode::AttractMode() :
easterEggPos(0),
time(0)
{
}


// Loop through an attract mode light pattern until the user hits
// the start button (also an easter egg)
Mode* AttractMode::Update(int dT)
{
  int difficulty = -1;

  int pressed = Input::Get().Pressed();

  if(CheckEasterEgg(pressed))
    difficulty = 2;
  UpdateLights(dT);

  if(pressed & SNES_START)
  {
    if(difficulty < 0)
      difficulty = Input::Get().Difficulty();

    // Start was pressed, so start the game
    return new DelayMode(new GameMode(difficulty), 200);
  }
  else
  {
    return this;
  }
}


boolean AttractMode::CheckEasterEgg(int pressed)
{
  if (pressed == easterEggCheatCode[easterEggPos])
  {
    // The correct button was just pressed, so advance the state
    easterEggPos++;
  }
  else if (pressed)
  {
    // User just pressed a wrong button, so reset the cheat code state
    easterEggPos = 0;
  }

  // If the user's done with the cheat code, trigger the easter egg
  if (easterEggPos == easterEggCheatCodeLength)
  {
    Output::Get().PlayEasterEggMelody();
    easterEggPos = 0;
    return true;
  }

  return false;
}


// Loop color pattern--display each color for FastLEDDisplayTime ms
// (broken into 32 parts, to increase sampling rate)
void AttractMode::UpdateLights(int dT)
{
  time += dT;
  if(attractLEDDisplayTime * attractLightPos < time)
  {
    Output::Get().SetLight(attractModeColors[attractLightPos], attractLEDDisplayTime);
  }
  attractLightPos++;

  if(attractLightPos == attractModeColorsLength)
  {
    attractLightPos = 0;
    time = 0;
  }
}


