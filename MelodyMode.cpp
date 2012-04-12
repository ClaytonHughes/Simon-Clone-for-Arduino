/*
   melody.cpp - a class to play various melodies (inspired by the original Super Mario Bros).
 */

#include "Arduino.h"
#include "Modes.h"
#include "pitches.h"
#include "pins.h"
#include "gameplay.h"
#include "Output.h"

class Note
{
public:
  Note(int f, int b) : 
  freq(f), beats(b) {
  }
  int freq;
  int beats;  
};

// Set up the melodies:
static const int losingTempo = 100;
static const Note losingMelody[] =
{
  Note(NOTE_C6,  2),
  Note(REST,     1),
  Note(NOTE_G5,  2),
  Note(REST,     1),
  Note(NOTE_E5,  2),
  Note(NOTE_A5,  2),
  Note(NOTE_B5,  2),
  Note(NOTE_A5,  2),
  Note(NOTE_GS5, 2),
  Note(NOTE_AS5, 2),
  Note(NOTE_GS5, 2),
  Note(NOTE_G5,  1),
  Note(NOTE_F5,  1),
  Note(NOTE_G5,  4)
};
static const int losingLength = sizeof(losingMelody) / sizeof(losingMelody[0]);


static const int winningTempo = 100;
static const Note winningMelody[] =
{
  Note(NOTE_G4,  1),
  Note(NOTE_C5,  1),
  Note(NOTE_E5,  1),
  Note(NOTE_G5,  1),
  Note(NOTE_C6,  1),
  Note(NOTE_E6,  1),
  Note(NOTE_G6,  2),
  Note(NOTE_E6,  2),

  Note(NOTE_GS4, 1),
  Note(NOTE_C5,  1),
  Note(NOTE_DS5, 1),
  Note(NOTE_GS5, 1),
  Note(NOTE_C6,  1),
  Note(NOTE_DS6, 1),
  Note(NOTE_GS6, 2),
  Note(NOTE_DS6, 2),

  Note(NOTE_AS4, 1),
  Note(NOTE_D5, 1),
  Note(NOTE_F5, 1),
  Note(NOTE_AS5, 1),
  Note(NOTE_D6, 1),
  Note(NOTE_F6, 1), 

  Note(NOTE_AS6, 2),
  Note(NOTE_AS6, 1),
  Note(NOTE_AS6, 1),
  Note(NOTE_AS6, 1),
  Note(NOTE_C7, 4)
};
static const int winningLength = sizeof(winningMelody) / sizeof(winningMelody[0]);


static const int easterEggTempo = 100;
static const Note easterEggMelody[] = {
  Note(NOTE_E5,  1),
  Note(NOTE_E5,  1),
  Note(REST,     1),
  Note(NOTE_E5,  1),
  Note(REST,     1),
  Note(NOTE_C5,  1),
  Note(NOTE_E5,  1),
  Note(REST,     1),
  Note(NOTE_G5,  1),
  Note(REST,     3),
  Note(NOTE_G4,  1),
  Note(REST,     1)
};
static const int easterEggLength = sizeof(easterEggMelody) / sizeof(easterEggMelody[0]);


static const int fireworkTempo = 20;
static const Note fireworkMelody[] = {
  Note(133, 4),
  Note(190, 1),
  Note(180, 1),
  Note(170, 1),
  Note(160, 1),
  Note(150, 1),
  Note(140, 1),
  Note(130, 1),
  Note(120, 1),
  Note(110, 1),
  Note(100, 1),
  Note(90, 1),
};
static const int fireworkLength = sizeof(fireworkMelody) / sizeof(fireworkMelody[0]);


MelodyMode::MelodyMode(Melody melody, Mode* next)
:
mNext(next),
time(0),
nextTime(0),
note(0),
fireworks(0)
{
  switch(melody)
  {
  case LOSE:
    notes = losingMelody;
    tempo = losingTempo;
    length = losingLength;
    break;

  case SECRET:
    notes = easterEggMelody;
    tempo = easterEggTempo;
    length = easterEggLength;
    break;

  default:
    notes = winningMelody;
    tempo = winningTempo;
    length = winningLength;
    int fireworks = melody - WIN;
    break;
  }

  color = (Color)random(0,4);
}

Mode* MelodyMode::Update(int dT)
{
  // If the melody isn't finished, update it:
  if(note < length)
  {  
    nextTime -= dT; 
    if(nextTime <= 0)
    {
      Output::Get().ClearLights();
      color = (Color)((color + random(1,4)) % 4); // advance color by 1-3 to guarantee a new color.
      Output::Get().LightOn(color);
      StartTone(notes[note].freq, notes[note].beats * tempo);

      nextTime = notes[note].beats * tempo;
      ++note;
    }    
  }
  else if(0 < fireworks)
  {
    // when finished with melody, and there are fireworks to play
    // set up firework melody
    length = fireworkLength;
    notes = fireworkMelody;
    tempo = fireworkTempo;
    --fireworks;
    nextTime = 0;
  }
  else
  {
    // melody is done, fireworks are done:
    return new DelayMode(200, mNext);
  }

  return this;
}


// Plays the specified tone for the specified duration
void MelodyMode::StartTone(int toneToPlay, int duration)
{
  // Rest if 0
  if (toneToPlay != 0)
  { 
    Output::Get().SetTone(toneToPlay, duration);   
  }
}

// Play victory fireworks sounds
void MelodyMode::PlayFireworks(int numFireworks)
{

  for (int i = 0; i < numFireworks; i++)
  {
    int color = i % 4;
    digitalWrite(RED_LED_PIN + color, HIGH);

    digitalWrite(RED_LED_PIN + color, LOW);
    delay(200);
  }
}






