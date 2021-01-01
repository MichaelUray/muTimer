# muTimer Library #

## About this Library ##
This library provides a non-blocking timer/delay functionality for Arduinos which consumes not much RAM.

Have a look on [timerOnOff()](#timeronoff) for normal on/off delays if you quickly want to understand how it works as well as on [timerCycle()](#timercycle) for periodically cycles.

It does not use any hardware timers, it uses the Arduino millis() function to store the start time.\
You can find the source there: https://github.com/MichaelUray/muTimer/ \
MIT license, check LICENSE file for more details.

## Introduction ##

There is often the requirement in a program to wait for a certain time before an action gets taken.
The easiest way to create a delay in a program is probably the function delay(), but with the disadvantage that nothing else can happen in the meanwhile, means the delay() function is blocking other code executions while it is waiting.
```cpp
// processor pin definitions
#define PIN_LED 9

// LED1 status variable
bool LED1;

void setup()
{
  // put your setup code here, to run once:

  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  LED1 = 0;
  digitalWrite(PIN_LED, LED1);
  delay(500);
  LED1 = 1;
  digitalWrite(PIN_LED, LED1);
  delay(100);
}
```
While the LED is off or on in this example and the delay(500) or delay(100) is waiting for its time to elapse, nothing else can happen (except of interrupts).

The following example shows how a flashing LED can get implemented without blocking other code.
```cpp
#include <muTimer.h>

// processor pin definitions
#define PIN_LED 9

// LED1 status variable
bool LED1;

// muTimer object
muTimer myTimer1 = muTimer();

void setup()
{
  // put your setup code here, to run once:

  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // LED flashing with 500ms off and 100ms on
  LED1 = myTimer1.timerOnOff(!LED1, 500, 100);
  digitalWrite(PIN_LED, LED1);
}
```
The accuracy of the time interval in this example depends on that how often the timerOnOff() function gets called, since the next time measurement starts everytime after a call.

A better way to create an accurate cycle would be to use the timerCycle() function since it internally makes sure that the time intervall stays the same.
```cpp
#include <muTimer.h>

// processor pin definitions
#define PIN_LED 9

// LED1 status variable
bool LED1;

// muTimer object
muTimer myTimer1 = muTimer();

void setup()
{
  // put your setup code here, to run once:

  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // LED flashing with 500ms off and 100ms on
  LED1 = myTimer1.timerCycle(500, 100);

  // write LED1 status to hardware output
  digitalWrite(PIN_LED, LED1);
}
```



Another typical example would be to store the current time in msec if something happens and to subtract it then from the current time later to check if a certain interval elapsed.
```cpp
// processor pin definitions
#define PIN_BUTTON 3
#define PIN_LED 9

// button status read from input pin
bool button1;

// LED1 status variable
bool LED1;

// store time when button got pressed
uint32_t timeWhenButtonPressed;

void setup()
{
  // put your setup code here, to run once:

  // configure input hardware pin with internal pull-up resistor, button has to switch against GND
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // read input (button) from hardware (input is inverted since internal pull-up resistor gets used)
  button1 = !digitalRead(PIN_BUTTON);

  // store time if button gets pressed
  if (button1)
  {
    timeWhenButtonPressed = millis();
  }

  // check if time deviation since button press is greater than 2000ms
  if (millis() - timeWhenButtonPressed >= 2000)
  {
    LED1 = 1;
  }
  else
  {
    LED1 = 0;
  }

  // write LED1 status to hardware output
  digitalWrite(PIN_LED, LED1);
}
```
There is a problem in this example which occurs if button1 stays true for longer as the uint32_t range in msec (~49 days) minus the interval, the condition would get then false again, even if this probably happens not often in the most of the applications.

The muTimer library does not have this problem since it only gets active if (output != input). If the timer is already elapsed it does not care anymore about the time difference.

This is how the same example looks with the muTimer library:
```cpp
#include <muTimer.h>

// processor pin definitions
#define PIN_BUTTON 3
#define PIN_LED 9

// button status read from input pin
bool button1;

// LED1 status variable
bool LED1;

// muTimer object
muTimer myTimer1 = muTimer();

void setup()
{
  // put your setup code here, to run once:

  // configure input hardware pin with internal pull-up resistor, button has to switch against GND
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // read input (button) from hardware (input is inverted since internal pull-up resistor gets used)
  button1 = !digitalRead(PIN_BUTTON);

  // store time if button gets pressed
  if (button1)
  {
    myTimer1.timerReset();
  }

  // check if time deviation since button press is greater as 2000ms
  if (myTimer1.timerOn(1, 2000))
  {
    LED1 = 1;
  }
  else
  {
    LED1 = 0;
  }

  // write LED1 status to hardware output
  digitalWrite(PIN_LED, LED1);
}
```


Another disadvantage from the delay() function is, that you cannot use it within interrupts, since the time gets generated by the timer0 interrupt, which does not work as long as you are in another interrupt routine.

These library functions can get used for example to do any action if an input is active at least for a given time period.

Some application examples for which this library could work for.
- Debounce a switch or button.
- Take any action after a given time permanently, e.g. switch an LED on 5s after the input gets set.
- Take any action after a given time just once or repeatedly, e.g. send a string via the serial interface every 5s.
- Create LED flashing with given on/off interval times.
- Switch a pump on by a floating switch if the switch is true for at least 1 minute and turn the pump off, if the switch gets false for at least 15 seconds.


# Functions #

## Timer On/Off ##

### timerOnOff() ##
On and off delay.\
Starts the timer if the bool 'input' gets set and it returns true when the 'on' timer given by 'delayOnTime' in msec is elapsed.\
If the output is already set and you clear the 'input', then it starts the 'off' timer and it returns false when the time given by 'delayOfTime' in msec is elapsed.
```cpp
bool timerOnOff(bool input, uint32_t delayOnTime, uint32_t delayOffTime);

// example: on delay 4000ms, off delay 2000ms
output1 = myTimer1.timerOnOff(input1, 4000, 2000);

// in : _______------------______---______________------------_------
// out: ___________----------_________________________---------------
```

### timerOn() ###
On delay only.\
Same as timerOnOff(), but on delay only.
```cpp
bool timerOn(bool input, uint32_t delayOnTime);
  
// example: on delay 4000ms
output1 = myTimer1.timerOn(input1, 4000);

// in : _______------------____________---______
// out: ___________--------_____________________
```

### timerOff() ###
Off delay only.\
Same as timerOnOff(), but off delay only.
```cpp
bool timerOff(bool input, uint32_t delayOffTime);

// example: off delay 2000ms
output1 = myTimer1.timerOff(input1, 2000);

// in : _______------------_______
// out: _______--------------_____
```

### timerOnOffTrigger() ###
On and off delay with output trigger.\
The output gets just set once if the timer elapses.
```cpp
bool timerOnOffTrigger(bool input, uint32_t delayOffTime);

// example: on delay 4000ms, off delay 2000ms
if (myTimer1.timerOnOffTrigger(input1, 4000, 2000))
{ // timer elapsed - gets executed just once
  if (input1)
  {
    Serial.println("Timer on finished: input1 == 1");
  }
  else
  {
    Serial.println("Timer off finished: input1 == 0");
  }
}

// in : _______------------_________
// out: ___________-_________-______
```
### timerOnTrigger() ###
On delay only with output trigger.\
The output gets just set once if the timer elapses.
```cpp
bool timerOnTrigger(bool input, uint32_t delayOffTime);

// example: on delay 4000ms
if (myTimer1.timerOnTrigger(input1, 4000))
{ // timer elapsed - gets executed just once
  Serial.println("Timer on finished: input1 == 1");
}

// in : _______------------__________
// out: ___________-_________________
```

### timerOffTrigger() ###
Off delay only with output trigger.\
The output gets just set once if the timer elapses.
```cpp
bool timerOffTrigger(bool input, uint32_t delayOffTime);

// example: off delay 2000ms
if (myTimer1.timerOffTrigger(input1, 2000))
{ // timer elapsed - gets executed just once
  Serial.println("Timer on finished: input1 == 0");
}

// in : _______------------__________
// out: _____________________-_______
```


## Timer Cycle ##

### timerCycle() ###
```cpp
// timer cycle, sets the output between on and off by the given time intervals
bool timerCycle(uint32_t offTime, uint32_t onTime)

// example: LED off 500ms, LED on 100ms
LED1 = myTimer1.timerCycle(4000, 2000);

// out: ____--____--____--____--____
```
### timerCycleTrigger() ###
Sets the output to 0 once if the onTime elapsed and if the output of timerCycle() would go to 0.
Sets the output to 1 once if the offTime elapsed and if the output of timerCycle() would go to 1.
Sets the output to 2 if the time between cycles is running.
```cpp
byte timerCycleTrigger(uint32_t offTime, uint32_t onTime);

// example: off 500ms, on 100ms
out1 = myTimer1.timerCycle(4000, 2000);
if (out1 == 1)
{ // gets executed after 4000ms once, then the 2000ms delay starts

}
if (out1 == 0)
{ // gets executed after 2000ms once, then the 4000ms delay starts
  
}

// OUT: 2222|1|22|0|2222|1|22|0|2222
```

### timerCycleResetToOff() ###
Sets the output to off and starts the cycle time from now.
```cpp
    // timer cycle reset to off output, allows to synchronize cycle with other actions
    void timerCycleResetToOff(void);
```

### timerCycleResetToOn() ###
Sets the output to on and starts the cycle time from now.
```cpp
    // timer cycle reset to on output, allows to synchronize cycle with other action
    void timerCycleResetToOn(void);
```

## Timer Control ##
### timerReset() ###
Restarts the time from 0 and sets output != input at the next timer function call.
```cpp
void timerReset(void);
```

### timerElapse() ###
Ends the current running timer interval and sets output == input at the next timer function call.
```cpp
void timerElapse(void);
```

## Timer Information ##

### timerIsRunning() ###
Returns true if timer is still running.
```cpp
bool timerIsRunning(void);
```
### getTimeElapsed() ###
Returns the elapsed time since the start of the timer.
```cpp
uint32_t getTimeElapsed(void);
```

# Example #

```cpp
/*
 * Example ButtonAndLedBlinkingTimerOnOff.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example creates a blinking LED if the input button gets pressed.
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
    // on delay 500ms, off delay 100ms
    // means the LED flashes 100ms and is then 500ms off
    output1 = myTimer1.timerOnOff(!output1, 500, 100);
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
```

