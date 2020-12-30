# muTimer Library #

This library provides a non-blocking timer/delay functionality for Arduinos.

It does not use any hardware timers, it uses the Arduino millis() function to store the start time.\
You can find the source there: https://github.com/MichaelUray/muTimer/ \
MIT license, check LICENSE file for more details

### About this Library ###

It is pretty easy to use library and it consumes not much RAM.

# Functions

### Timer Functions ###

**on and off** timer
```cpp
  // on delay 2000 ms, off delay 1000 ms
  output = myTimer1.timerOnOff(input, 2000, 1000);
```

**on** timer only
```cpp
  // on delay 2000 ms
  output = myTimer1.timerOn(input, 2000);
```

**off** timer only
```cpp
  // off delay 1000 ms
  output = myTimer1.timerOff(input, 1000);
```

### Timer Control ###

```cpp
    // restarts the current running time interval from 0
    void timerReset(void);
```

```cpp
    // ends the current running time intervall
    void timerElapse(void);
```

### Timer Information ###

```cpp
    // returns if timer is still running
    bool timerIsRunning(void);
```

```cpp
    // returns the time elapsed since start
    uint32_t getTimeElapsed(void);
```

## Example ##

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
  // read input
  input = digitalRead(PIN_BUTTON);

  // on delay 2000 ms, off delay 1000 ms
  output = myTimer1.timerOnOff(input, 2000, 1000);

  // write output
  digitalWrite(PIN_LED, output);
}
```

