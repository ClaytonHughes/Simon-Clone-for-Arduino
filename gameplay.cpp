/* 
    Various settings related to gameplay.
 */

#include "gameplay.h"
#include "SNESPad.h"
#include "pitches.h"

// Number of successful turns required to win; set when the game starts depending on DIFF_SWITCH_PIN
int turnsUntilWin;

// Array to hold colors used so far
int colorChain[100];
// Wait this time (ms) between light display; changes depending on difficulty mode
int delayBetweenLights = 200;

// LEDs
int LEDDisplayTime = 200; // time to show the LED in ms

// Time to play a Simon Says sound in ms (should probably match LEDDisplayTime)
const int soundPlayTime = 700;

const int redTone = NOTE_CS6;
const int greenTone = NOTE_D5;
const int blueTone = NOTE_E5;
const int yellowTone = NOTE_B5;

// Gameplay elements
const int easyModeTurns = 7;
const int hardModeTurns = 11;
const int superHardModeTurns = 15;

// States for buttons
int red_button_state;
int green_button_state;
int blue_button_state;
int yellow_button_state;

// Outputs a random integer between 0 and 3 (corresponding to a color)
int randomColor()
{
    return (int)random(0, 4);
}

