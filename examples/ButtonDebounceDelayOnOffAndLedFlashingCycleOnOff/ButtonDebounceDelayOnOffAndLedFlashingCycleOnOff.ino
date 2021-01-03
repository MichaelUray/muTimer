/*
 * Example ButtonDebounceDelayOnOffAndLedFlashingCycleOnOff.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example creates a blinking LED (100ms/500ms) if the input button gets pressed for at least 1s.
 * If the button gets released for at least 2s, then the blinking stops.
 * It uses the delayOnOff() and cycleOnOff() functions.
 * 
 * The library calls are non-blocking, means other code can get executed while the time duration is running.
 * 
 */

#include <muTimer.h>

muTimer mutButtonDebounce = muTimer();
muTimer mutLedFlashing = muTimer();

// processor pin definitions
#define PIN_BUTTON1 3
#define PIN_LED1 9

// pin status read from input
bool button1;

// output written to hardware output pin
bool led1;

void setup()
{
  // configure input hardware pin with internal pull-up resistor, button has to switch against GND
  pinMode(PIN_BUTTON1, INPUT_PULLUP);

  // configure output hardware pin
  pinMode(PIN_LED1, OUTPUT);
}

void loop()
{
  // read input (button) from hardware (input is inverted since internal pull-up resistor gets used)
  button1 = !digitalRead(PIN_BUTTON1);

  // starts blinking if input is true for at least 1000ms, stops blinking if input is false for at least 2000ms
  // in a normal debounce application whould that be just a few ms, these high values are just for this example that you can recognize the time delay.
  if (mutButtonDebounce.delayOnOff(button1, 1000, 2000))
  {
    // the LED is on for 100ms and then off for 500ms
    led1 = mutLedFlashing.cycleOnOff(100, 500);
  }
  else
  {
    led1 = 0;
  }
  
  // write output (LED) to hardware
  digitalWrite(PIN_LED1, led1);


  // functions are non-blocking
  // other code can get executed there in the meanwhile
  // ...
    
}