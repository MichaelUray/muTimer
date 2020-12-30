# muTimer Library #

This library provides a non-blocking timer/delay functionality for Arduinos in msec.

It does not use any hardware timers, it uses the Arduino millis() function to store the start time. It might be useable for other platforms as well, if you replace the millis() function with any other function which returns a msec counter as unsigned 32-bit value.\
You can find the source there: https://github.com/MichaelUray/muTimer/ \
MIT license, check LICENSE file for more details.

### About this Library ###

It is a pretty easy to use library and it consumes not much RAM.

# Functions

### Timer Functions ###
**timerOnOff()**\
'On' and 'off' delay.\
Starts the timer if the bool 'input' gets set and it returns true when the 'on' delay given by 'delayOnTime' in msec is elapsed.\
If the output is already set and you clear the bool 'input', then it starts the 'off' delay and it returns false when the time given by 'delayOfTime' in msec is elapsed.
```cpp
  bool timerOnOff(bool input, uint32_t delayOnTime, uint32_t delayOffTime);
  
  // example: on delay 2000 ms, off delay 1000 ms
  output1 = myTimer1.timerOnOff(input1, 2000, 1000);
```

**timerOn()**\
'On' delay only.\
Same as timerOnOff(), but 'on' delay only.
```cpp
  bool timerOn(bool input, uint32_t delayOnTime);
  
  // example: on delay 2000 ms
  output1 = myTimer1.timerOn(input1, 2000);
```

**timerOff()**\
'Off' delay only.\
Same as timerOnOff(), but 'off' delay only.
```cpp
  bool timerOff(bool input, uint32_t delayOffTime);

  // example: off delay 1000 ms
  output1 = myTimer1.timerOff(input1, 1000);
```

### Timer Control ###
**timerReset()**
```cpp
    // restarts the current running time interval from 0
    void timerReset(void);
```
**timerElapse()**
```cpp
    // ends the current running time intervall, return value equals then input value at next call of timer function
    void timerElapse(void);
```

### Timer Information ###
**timerIsRunning()**
```cpp
    // returns true if timer is still running
    bool timerIsRunning(void);
```
**getTimeElapsed()**
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

