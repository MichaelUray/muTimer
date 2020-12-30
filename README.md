# muTimer Library #

This library does not use any hardware timers, it just uses the Arduino millis() function to store the start time.\
You can find the source there: https://github.com/MichaelUray/muTimer/

## About this Library ##

It is pretty easy to use and it consumes just a very little bit of RAM.

```cpp
#include <muTimer.h>

muTimer myTimer1 = muTimer();

// processor pin definitions
#define PIN_BUTTON  3
#define PIN_LED 9

bool input;
bool output;

void setup()
{

  // configure input pin switch with internal pull-up resistor
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // configure output pin LED
  pinMode(PIN_LED, OUTPUT);

}

void loop()
{
  input = digitalRead(PIN_BUTTON); // read input
  output = myTimer1.timerOnOff(input, 2000, 1000); // on delay 2000 ms, off delay 1000 ms
  digitalWrite(PIN_LED, output); // write output
}
```

There are also calls available to use either the on or off timer
```cpp
  output = myTimer1.timerOn(input, 2000); // on delay 2000 ms
```

```cpp
  output = myTimer1.timerOff(input, 1000); // off delay 1000 ms
```


Written by Michael Uray / Austria\
MIT license, check LICENSE file for more details
