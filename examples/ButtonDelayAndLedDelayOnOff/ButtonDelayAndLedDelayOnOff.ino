/*
 * Example ButtonDelayAndLedDelayOnOff.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example has a button which needs to get pressed for 2s to turn a LED on and it requires the button released for 1s to turn the LED off.
 * You can use such a functionality to debounce a button or switch, but in this case a few ms delay are probably a good delay value instead of 2s and 1s like in this example.
 *
 * The library calls are non-blocking, means other code can get executed while the time duration is running.
 * 
 */
#include <muTimer.h>

muTimer myTimer1 = muTimer();

// processor pin definitions
#define PIN_BUTTON 3
#define PIN_LED 9

bool input1;
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

  // on delay 2000ms, off delay 1000ms
  output1 = myTimer1.delayOnOff(input1, 2000, 1000);

  // write output (LED) to hardware
  digitalWrite(PIN_LED, output1);
}