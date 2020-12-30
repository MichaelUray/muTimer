# muTimer Library #

This library provides a non-blocking timer/delay functionality for Arduinos.

It does not use any hardware timers, it uses the Arduino millis() function to store the start time.\
You can find the source there: https://github.com/MichaelUray/muTimer/ \
MIT license, check LICENSE file for more details

### About this Library ###

It is pretty easy to use library and it consumes not much RAM.

# Functions

### Timer Functions ###

**on and off** delay\
timerOnOff()\
Starts the timer if the bool 'input' bit gets set and it returns true when the 'on' timer given by 'delayOnTime' in msec is elapsed.\
If the output is already set and you clear the 'input' bit, then it starts the 'off' timer and it returns false when the time given by 'delayOfTime' in msec is elapsed.
```cpp
  bool timerOnOff(bool input, uint32_t delayOnTime, uint32_t delayOffTime);
  
  // example: on delay 2000 ms, off delay 1000 ms
  output1 = myTimer1.timerOnOff(input1, 2000, 1000);
```

**on** delay only
timerOn()\
Same as timerOnOff(), but on delay only.
```cpp
  bool timerOn(bool input, uint32_t delayOnTime);
  
  // example: on delay 2000 ms
  output1 = myTimer1.timerOn(input1, 2000);
```

**off** delay only
timerOff()\
Same as timerOnOff(), but off delay only.
```cpp
  bool timerOff(bool input, uint32_t delayOffTime);

  // example: off delay 1000 ms
  output1 = myTimer1.timerOff(input1, 1000);
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
    // returns true if timer is still running
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

bool input1;
bool output1;

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
  input1 = digitalRead(PIN_BUTTON);

  // on delay 2000 ms, off delay 1000 ms
  output1 = myTimer1.timerOnOff(input1, 2000, 1000);

  // write output
  digitalWrite(PIN_LED, output1);
}
```

