/* 
 Functions to handle button input on the Arduino.
 */

#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

#include "gameplay.h"

class SNESpad;

class Input
{
public:
  static Input& Get();  
  void Update();
                        
  int Buttons();    // Buttons that are pressed this frame.
  int Pressed();    // Buttons that were pressed this frame, but not last
  int Released();   // Buttons that were not pressed this frame, but were last
  int Held();       // Buttons that were pressed both this and last frame
  Difficulty GetDifficulty(); // State of the Difficulty Switch
  
  int SNESCode(Color color); // The Button Flag for the specified color

private:
  Input();
  Input(const Input& rhs);
  Input& operator=(const Input& rhs);
  static Input* spInstance;
  
  SNESpad* padInput;
  int prevPad;
  int curPad;
};

#endif

