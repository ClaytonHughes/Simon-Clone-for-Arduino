/*

 Simon Says Project
 
 Uses a speaker, four LEDs and four switches to play
 a game of "Simon Says" with the user. An additional
 switch can be used for resetting the game.
 
 */

#include "pins.h"
#include "gameplay.h"
#include "Input.h"
#include "Output.h"
#include "Modes.h"

#include "SNESpad.h"

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

// Main game loop. Returns a boolean that signals whether or not to jump
// straight into the game again (restart) or go into a waiting loop.
void mainGame()
{

  boolean stillPlaying = true;
  boolean wonGame = false;
  int turnNo = 0; // Current player turn
  // Main game loop; loop until the player messes up or wins
  while(stillPlaying && !wonGame)
  {
    // Get a new color and add it to the color chain
    colorChain[turnNo] = randomColor();

    // Play color chain up to this point
    for(int i = 0; i <= turnNo; i++)
    {
      delay(delayBetweenLights);
      Output::Get().playColorAndSound(colorChain[i], LEDDisplayTime, true);
      Output::Get().clearLights();
    }

    // Now, get user input and ensure it matches the pattern
    int correctPresses = 0;
    while ((correctPresses <= turnNo) && stillPlaying)
    {
      // If the user is pressing a color button,
      // show its sound and light until they release the button
      int pressedColor = Input::Get().getPressedColor();

      if (pressedColor != -1)
      {
        // Play color and sound
        Output::Get().playPressedButtonColorAndSound();

        // Check if correct
        if (pressedColor == colorChain[correctPresses])
        {
          correctPresses++;
        }
        else
        {
          // Screwed up, so the player loses
          stillPlaying = false;
        }
      }
    }

    // At this point, the user has successfully pressed all
    // of the color chain up to this point
    delay(400);

    if (correctPresses == turnsUntilWin)
    {
      // User has won, so exit!
      wonGame = true;
    }

    // Increment turn number
    turnNo++;
  }

  // If user won, play victory song and go to attract mode loop
  if (wonGame)
  {
    Output::Get().PlayWinningMelody(turnsUntilWin);
    return;
  }
  // Otherwise, play losing song and go to attract mode loop
  else
  {
    Output::Get().PlayLosingMelody();
    return;
  }   
}

