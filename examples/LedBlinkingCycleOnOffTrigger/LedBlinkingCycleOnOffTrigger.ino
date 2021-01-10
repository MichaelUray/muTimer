/*
 * Example LedBlinkingCycleOnOffTrigger.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example creates a blinking LED.
 * It only writes to the output on a change.
 * 
 * The library calls are non-blocking, means other code can get executed while the time duration is running.
 * 
 */

#include <muTimer.h>

// processor pin definitions
#define PIN_LED 9

// muTimer object
muTimer myCycle1 = muTimer();

void setup()
{
  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // LED flashing with 100ms on and 500ms off
  switch (myCycle1.cycleOnOffTrigger(100, 500))
  {
    // state changed from 1->0
    // turn LED off
    case 0:
      digitalWrite(PIN_LED, LOW);
      break;

    // state changed from 0->1
    // turn LED on
    case 1:
      digitalWrite(PIN_LED, HIGH);
      break;

    // no state change, timer is running
    case 2:
      break;
  }
}

// out: _____-_____-_____-_____-_____
