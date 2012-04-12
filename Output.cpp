/* 
 Functions to manipulate lights on the Arduino. Some sound-related code is also included.
 */

#include "Arduino.h"
#include "Output.h"
#include "pins.h"
#include "gameplay.h"
#include "pitches.h"

Output* Output::spInstance = NULL;

// Time to play a Simon Says sound in ms (should probably match LEDDisplayTime)
const int soundPlayTime = 700;

const int redTone = NOTE_CS6;
const int greenTone = NOTE_D5;
const int blueTone = NOTE_E5;
const int yellowTone = NOTE_B5;
const int colorTones[] = {redTone, greenTone, blueTone, yellowTone};


Output::Output()
{
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  ClearLights();

  spInstance = this;
}

Output& Output::Get()
{
  if(NULL == spInstance)
    spInstance = new Output();

  return *spInstance;
}


// Update delay times, turning off things if their duration is up.
void Output::Update(int dT)
{
  for(int i = 0; i < 4; ++i)
  {
    if(0 < lightOffTime[i])
    {
      lightOffTime[i] -= dT;
      if(lightOffTime[i] <= 0)
      {
        digitalWrite(RED_LED_PIN + i, LOW);
      }
    }
  }
    
  if(0 < soundOffTime)
  {  
    soundOffTime -= dT;
    if(soundOffTime <= 0)
    {
      noTone(SPEAKER_PIN);
    }
  }
}


// Turn on LED corresponding to the color
void Output::LightOn(Color color)
{
  LightOn(color, -1);
}


// Turn on LED corresponding to the color
void Output::LightOn(Color color, int duration)
{
  digitalWrite(RED_LED_PIN + color, HIGH);
  lightOffTime[color] = duration;
}


// Turn off the LED corresponding to the color
void Output::LightOff(Color color)
{
  digitalWrite(RED_LED_PIN + color, LOW);
}


// Turn on Speaker for a specified tone
void Output::SetTone(Color color, int duration)
{
  tone(SPEAKER_PIN, colorTones[color], duration);
  soundOffTime = duration * 1.3;
}


void Output::SetTone(int freq, int duration)
{
  tone(SPEAKER_PIN, freq, duration);
  soundOffTime = duration * 1.3;
}


// Turn off all LEDs
void Output::ClearLights()
{
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
}



