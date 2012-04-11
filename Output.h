/* 
 Functions to manipulate lights on the Arduino. Some sound-related code is also included.
 */

#ifndef LIGHTS_H
#define LIGHTS_H

class MelodyPlayer;

class Output
{
public:
  static Output& Get();
  void Update(int dT);

  // Displays a color and plays the corresponding sound
  void SetLight(int light, int duration);
  
  void playColorAndSound(int, int, boolean);

  // Lights the LED of the corresponding color
  void lightUpColor(int);

  // Turn off all LEDs
  void clearLights();

  // Plays the appropriate sound given a certain color
  void playSoundForColor(int);

  // Play the color and sound for a pressed button until the button is released
  void playPressedButtonColorAndSound();

  void PlayWinningMelody(int difficulty);
  void PlayLosingMelody();
  void PlayEasterEggMelody();
  

private:
  Output();
  Output(const Output& rhs);
  Output& operator=(const Output& rhs);
  static Output* spInstance;
  
  MelodyPlayer* melodyPlayer;
  int mCurTime;
  int lightOffTime[4];
};

#endif

