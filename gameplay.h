/* 
 Various settings related to gameplay.
 */

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Arduino.h"

// Number of successful turns required to win; set when the game starts depending on DIFF_SWITCH_PIN
extern int turnsUntilWin;

// Array to hold colors used so far
extern int colorChain[100];
// Wait this time (ms) between light display; changes depending on difficulty mode
extern int delayBetweenLights;

// LEDs
extern int LEDDisplayTime; // time to show the LED in ms

// Time to play a Simon Says sound in ms (should probably match LEDDisplayTime)
extern const int soundPlayTime;

extern const int redTone;
extern const int greenTone;
extern const int blueTone;
extern const int yellowTone;

// States for buttons
extern int red_button_state;
extern int green_button_state;
extern int blue_button_state;
extern int yellow_button_state;

// Outputs a random integer between 0 and 3 (corresponding to a color)
int randomColor();


#endif

