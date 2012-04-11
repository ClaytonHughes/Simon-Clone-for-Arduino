/*
   melody.h - a class to play various melodies (inspired by the original Super Mario Bros).
 */

#ifndef MELODYPLAYER_H
#define MELODYPLAYER_H

#include "Modes.h"

class MelodyMode :
public Mode
{
    public:
        MelodyMode(Melody melody, Mode* next);
        virtual Mode* Update(int dT);
       
        void playTone(int, int);
        void playFireworks(int);
    private:
        Melody mMelody;
        Mode* mNext;
    
        void playMelody(const int[], const int[], const int, const int);

        static const int losingTempo;
        static const int losingLength;
        static const int losingTones[];
        static const int losingBeats[];

        static const int winningTempo;
        static const int winningLength;
        static const int winningTones[];
        static const int winningBeats[];

        static const int easterEggTempo;
        static const int easterEggLength;
        static const int easterEggTones[];
        static const int easterEggBeats[];
};

#endif
