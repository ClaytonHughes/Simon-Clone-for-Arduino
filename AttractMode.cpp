#include "Modes.h"
#include "gameplay.h"
#include "SNESPad.h"
#include "Input.h"
#include "Output.h"

const int easterEggCheatCode[] = { 
  SNES_UP, SNES_UP, SNES_DOWN, SNES_DOWN, SNES_LEFT, SNES_RIGHT, SNES_LEFT, SNES_RIGHT, SNES_B, SNES_A, SNES_START };
const int easterEggCheatCodeLength = sizeof(easterEggCheatCode) / sizeof(easterEggCheatCode[0]);
const int attractLEDDisplayTime = 120; // Time to show LED in ms during attract mode 
const Color attractModeColors[] = { 
  BLUE, GREEN, YELLOW, RED,
  BLUE, GREEN, YELLOW, RED,
  BLUE, GREEN, YELLOW, RED,
  BLUE, BLUE, BLUE, BLUE,
  RED, YELLOW, GREEN, BLUE,
  RED, YELLOW, GREEN, BLUE,
  RED, YELLOW, GREEN, BLUE,
  BLUE, BLUE };
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
  int pressed = Input::Get().Pressed();

  if(CheckEasterEggCode(pressed))
    return new MelodyMode(SECRET, new GameMode(SUPERHARD));

  UpdateLights(dT);

  if(pressed & SNES_START)
  {
    Difficulty difficulty = Input::Get().GetDifficulty();    
    return new DelayMode(200, new GameMode(difficulty));
  }
  
  return this;
}


boolean AttractMode::CheckEasterEggCode(int pressed)
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
  return (easterEggPos == easterEggCheatCodeLength);
}


void AttractMode::UpdateLights(int dT)
{
  time += dT;
  if(attractLEDDisplayTime * attractLightPos < time)
  {
    // enough time has passed, we should start the next light in the sequence:
    Output::Get().LightOn(attractModeColors[attractLightPos], attractLEDDisplayTime);
  }
  attractLightPos++;

  if(attractLightPos == attractModeColorsLength)
  {
    // hit the end of the sequence, reset and start over:
    attractLightPos = 0;
    time = 0;
  }
}



