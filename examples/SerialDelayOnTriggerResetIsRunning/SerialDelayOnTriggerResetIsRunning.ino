/*
 * Example SerialDelayOnTriggerResetIsRunning.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example waits for 1s and it sends then once the string "Delay-On triggered." via the serial interface.
 * If you push the button, then it waits again 1s to send the string.
 * It uses the functions delayOnTrigger(), delayIsRunning() and delayReset().
 * 
 * The library calls are non-blocking, means other code can get executed while the time duration is running.
 * 
 */
#include <muTimer.h>

muTimer myTimer1 = muTimer();

// processor pin definitions
#define PIN_BUTTON 3

// pin status read from input
bool input1;

void setup()
{
  // configure input hardware pin with internal pull-up resistor, button has to switch against GND
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Init done.");
}

void loop()
{
  // 1000ms on delay
  if (myTimer1.delayOnTrigger(1, 1000))
  {
    Serial.println("Delay-On triggered.");
  }

  // read input (button) from hardware (input is inverted since internal pull-up resistor gets used)
  input1 = !digitalRead(PIN_BUTTON);

  // reset delay if input is true and delay is not running
  if (input1 && !myTimer1.delayIsRunning())
  {
    myTimer1.delayReset();
  }

  // The library is non-blocking.
  // Other code can get executed there in the meanwhile.
  // ...
}