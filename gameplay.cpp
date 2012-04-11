/* 
    Various settings related to gameplay.
 */

#include "Arduino.h"
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


// States for buttons
int red_button_state;
int green_button_state;
int blue_button_state;
int yellow_button_state;

