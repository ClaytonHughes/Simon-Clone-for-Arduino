/* 
    Functions to manipulate lights on the Arduino. Some sound-related code is also included.
 */

#include "Arduino.h"
#include "Output.h"
#include "MelodyPlayer.h"
#include "pins.h"
#include "gameplay.h"
#include "Output.h"
#include "Input.h"

Output* Output::spInstance = NULL;

Output::Output()
{
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  
  melodyPlayer = new MelodyPlayer();
  
  spInstance = this;
}

Output& Output::Get()
{
  if(NULL == spInstance)
    spInstance = new Output();
    
  return *spInstance;
}

// Displays a color and plays the corresponding sound
void Output::playColorAndSound(int color, int duration, boolean playAudio)
{
    int toneToPlay;
    // Turn on LED corresponding to the color
    switch (color)
    {
        case 0:
            digitalWrite(RED_LED_PIN, HIGH);
            toneToPlay = redTone;
            break;
        case 1:
            digitalWrite(GREEN_LED_PIN, HIGH);
            toneToPlay = greenTone;
            break;
        case 2:
            digitalWrite(BLUE_LED_PIN, HIGH);
            toneToPlay = blueTone;
            break;
        case 3:
            digitalWrite(YELLOW_LED_PIN, HIGH);
            toneToPlay = yellowTone;
            break;
        default:
            break;
    }

    // Play the corresponding tone for the time in "duration",
    // unless you're not playing audio, in which case just wait
    if (playAudio)
    {
        melodyPlayer->playTone(toneToPlay, duration);
    }
    else
    {
        delay(duration);
    }
}


// Lights the LED of the corresponding color
void Output::lightUpColor(int color)
{
    switch (color)
    {
        case 0:
            digitalWrite(RED_LED_PIN, HIGH);
            break;
        case 1:
            digitalWrite(GREEN_LED_PIN, HIGH);
            break;
        case 2:
            digitalWrite(BLUE_LED_PIN, HIGH);
            break;
        case 3:
            digitalWrite(YELLOW_LED_PIN, HIGH);
            break;
        default:
            return;
    }
}

// Turn off all LEDs
void Output::clearLights()
{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
}

// Plays the appropriate sound given a certain color
void Output::playSoundForColor(int color)
{
    // Get frequency in hz
    int frequency;
    switch (color)
    {
        case 0:
            frequency = redTone;
            break;
        case 1:
            frequency = greenTone;
            break;
        case 2:
            frequency = blueTone;
            break;
        case 3:
            frequency = yellowTone;
            break;
        default:
            return;
    }
    // Now, play audio (will be turned off in another function,
    // when the user releases the button)
    tone(SPEAKER_PIN, frequency);
}

// Play the color and sound for a pressed button until the button is released
void Output::playPressedButtonColorAndSound()
{
    // Grab first color pressed by the user
    int pressedColor = Input::Get().getPressedColor();

    // Light corresponding light
    lightUpColor(pressedColor);

    // Loop until the user releases that button
    while (Input::Get().isPressed(pressedColor))
    {
        playSoundForColor(pressedColor);
        Input::Get().updateButtonStates();
    }
    noTone(SPEAKER_PIN);
    clearLights();
}

void Output::PlayWinningMelody(int value)
{
  melodyPlayer->playWinningMelody(value);
}

void Output::PlayLosingMelody()
{
  melodyPlayer->playLosingMelody();
}

void Output::PlayEasterEggMelody()
{
  melodyPlayer->playEasterEggMelody();
}
