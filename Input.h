/* 
 Functions to handle button input on the Arduino.
 */

#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

class SNESpad;

class Input
{
public:
  static Input& Get();
  void Update();
  
  int Buttons();
  int Pressed();
  int Released();
  int Held();
  
  int Difficulty();

  // Returns the button being pressed by the user. If no button
  // is being pressed, returns -1.
  int getPressedColor();

  // Updates the current state for all of the color buttons
  void updateButtonStates();

  // Checks to see if a certain button is being pressed
  boolean isPressed(int);

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

