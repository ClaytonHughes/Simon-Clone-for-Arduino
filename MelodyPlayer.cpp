/*
   melody.cpp - a class to play various melodies (inspired by the original Super Mario Bros).
 */

#include "Arduino.h"
#include "MelodyPlayer.h"
#include "pitches.h"
#include "pins.h"
#include "gameplay.h"
#include "Output.h"

// Initialize static member variables
const int MelodyMode::losingTempo = 100;
const int MelodyMode::losingTones[] = { NOTE_C6, 0, NOTE_G5, 0, NOTE_E5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5, NOTE_G5 };
const int MelodyMode::losingBeats[] = { 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 4 };
const int MelodyMode::losingLength = sizeof(MelodyMode::losingTones) / sizeof(MelodyMode::losingTones[0]);

const int MelodyMode::winningTempo = 100;
const int MelodyMode::winningTones[] = { NOTE_G4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_E6, NOTE_G6, NOTE_E6, NOTE_GS4, NOTE_C5, NOTE_DS5, NOTE_GS5, NOTE_C6, NOTE_DS6, NOTE_GS6, NOTE_DS6, NOTE_AS4, NOTE_D5, NOTE_F5, NOTE_AS5, NOTE_D6, NOTE_F6, NOTE_AS6, NOTE_AS6, NOTE_AS6, NOTE_AS6, NOTE_C7 };
const int MelodyMode::winningBeats[] = { 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 4 };
const int MelodyMode::winningLength = sizeof(MelodyMode::winningTones) / sizeof(MelodyMode::winningTones[0]);

const int MelodyMode::easterEggTempo = 100;
const int MelodyMode::easterEggTones[] = { NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5, 0, 0, NOTE_G4, 0 };
const int MelodyMode::easterEggBeats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1 };
const int MelodyMode::easterEggLength = sizeof(MelodyMode::easterEggTones) / sizeof(MelodyMode::easterEggTones[0]);;

MelodyMode::MelodyMode(Melody melody, Mode* next)
:
mMelody(melody),
mNext(next)
{
}

Mode* MelodyMode::Update(int dT)
{
  switch(mMelody)
  {
    case LOSE:
      playMelody(losingTones, losingBeats, losingTempo, losingLength);
    break;
    case SECRET:
      playMelody(easterEggTones, easterEggBeats, easterEggTempo, easterEggLength);
    break;
    default:
      playMelody(winningTones, winningBeats, winningTempo, winningLength);    
      int fireworks = mMelody - WIN;
        playFireworks(fireworks);
    break;
  }
}


// Plays the specified tone for the specified duration
void MelodyMode::playTone(int toneToPlay, int duration)
{
    // Rest if 0
    if (toneToPlay == 0)
    {
        delay(duration);
    }
    // Otherwise, play
    else
    {
        tone(SPEAKER_PIN, toneToPlay, duration);
        delay(duration * 1.30);
        noTone(SPEAKER_PIN);
    }
}

// Play victory fireworks sounds
void MelodyMode::playFireworks(int numFireworks)
{
    // Firework sound:
    // 133 times a second for .18 seconds, then
    // 190 times a second for .10 seconds, then 
    // 133 times a second for .05 seconds, then
    // 83 times a second, for .05 seconds
    for (int i = 0; i < numFireworks; i++)
    {
        int color = i % 4;
        digitalWrite(RED_LED_PIN + color, HIGH);
        playTone(133, 80);
        playTone(180, 20);
        playTone(170, 20);
        playTone(160, 20);
        playTone(150, 20);
        playTone(140, 20);
        playTone(130, 20);
        playTone(120, 20);
        playTone(110, 20);
        playTone(100, 20);
        playTone(90, 20);
        digitalWrite(RED_LED_PIN + color, LOW);
        delay(200);
    }
}

void MelodyMode::playMelody(const int tones[], const int beats[], const int tempo, const int length)
{
    int curColor = random(0,4);
    for (int i = 0; i < length; i++)
    {
        // Perturb color by 1-3, so we get a new random color:
        curColor += random(1,4);
        digitalWrite(curColor + RED_LED_PIN, HIGH);
        playTone(tones[i], beats[i] * tempo);
        Output::Get().clearLights();
    }
}
