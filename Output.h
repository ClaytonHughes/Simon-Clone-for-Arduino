/* 
 Functions to manipulate lights on the Arduino. Some sound-related code is also included.
 */

#ifndef LIGHTS_H
#define LIGHTS_H

#include "gameplay.h"

class Output
{
public:
  static Output& Get();
  void Update(int dT);

  // Turns a color on, with unlimited duration.
  void LightOn(Color color);
  // Turns a color on, and sets the duration for it to turn off.
  void LightOn(Color color, int duration);
  void LightOff(Color color);
  
  // Turns a tone on, and sets the duration for it to turn off.
  void SetTone(Color color, int duraction);
  void SetTone(int freq, int duraction);
 
  // Turn off all LEDs
  void ClearLights();

private:
  Output();
  Output(const Output& rhs);
  Output& operator=(const Output& rhs);
  static Output* spInstance;
  
  void SetLight(int color, int duration, int state);
  
  int lightOffTime[4];
  int soundOffTime;
};

#endif

