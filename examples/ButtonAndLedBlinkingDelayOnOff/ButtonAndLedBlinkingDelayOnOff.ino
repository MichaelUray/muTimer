/*
 * Example ButtonAndLedBlinkingDelayOnOff.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example creates a blinking LED if the input button gets pressed.
 * It uses the delayOnOff() function.
 * 
 * The library calls are non-blocking, means other code can get executed while the time duration is running.
 * 
 */

#include <muTimer.h>

muTimer myTimer1 = muTimer();

// processor pin definitions
#define PIN_BUTTON 3
#define PIN_LED 9

// pin status read from input
bool input1;

// output written to hardware output pin
bool output1;

void setup()
{
  // configure input hardware pin with internal pull-up resistor, button has to switch against GND
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // read input (button) from hardware (input is inverted since internal pull-up resistor gets used)
  input1 = !digitalRead(PIN_BUTTON);

  // starts blinking if input is true
  if (input1)
  {
    // On delay 500ms, off delay 100ms
    // Means the LED flashes 100ms and is then 500ms off.
    // Send the inverted output back as input of the function to toggle the input as soon as the output gets active. This creates a permanent on/off delayed cycle.
    output1 = myTimer1.delayOnOff(!output1, 500, 100);
  }
  else
  {
    output1 = 0;
  }

  // write output (LED) to hardware
  digitalWrite(PIN_LED, output1);

  // functions are non-blocking
  // other code can get executed there in the meanwhile
  // ...
}