# muTimer Library #

## Index ##
- [muTimer Library](#mutimer-library)
  * [Index](#index)
  * [About this Library](#about-this-library)
  * [Introduction](#introduction)
- [Functions](#functions)
  * [Timer On/Off](#timeronoff)
    + [delayOnOff()](#timeronoff)
    + [delayOn()](#timeron)
    + [delayOff()](#timeroff)
    + [delayOnOffTrigger()](#timeronofftrigger)
    + [delayOnTrigger()](#timerontrigger)
    + [delayOffTrigger()](#timerofftrigger)
  * [Timer Cycle](#timer-cycle)
    + [cycle()](#timercycle)
    + [cycleTrigger()](#timercycletrigger)
    + [cycleResetToOff()](#timercycleresettooff)
    + [cycleResetToOn()](#timercycleresettoon)
  * [Timer Control](#timer-control)
    + [delayReset()](#timerreset)
    + [delayElapse()](#timerelapse)
  * [Timer Information](#timer-information)
    + [delayIsRunning()](#timerisrunning)
    + [getTimeElapsed()](#gettimeelapsed)
- [Example](#example)

## About this Library ##
This library provides a non-blocking timer/delay functionality for Arduinos which consumes not much RAM.

Have a look on [delayOnOff()](#timeronoff) for normal on/off delays if you quickly want to understand how it works as well as on [cycle()](#timercycle) for periodically cycles.

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
  LED1 = myTimer1.delayOnOff(!LED1, 500, 100);
  digitalWrite(PIN_LED, LED1);
}
```
The accuracy of the time interval in this example depends on that how often the delayOnOff() function gets called, since the next time measurement starts everytime after a call.

A better way to create an accurate cycle would be to use the cycle() function since it internally makes sure that the time intervall stays the same.
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
  LED1 = myTimer1.cycle(500, 100);

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
    myTimer1.delayReset();
  }

  // check if time deviation since button press is greater as 2000ms
  if (myTimer1.delayOn(1, 2000))
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

### delayOnOff() ##
On and off delay.\
Starts the timer if the bool 'input' gets set and it returns true when the 'on' timer given by 'delayTimeSwitchOn' in msec is elapsed.\
If the output is already set and you clear the 'input', then it starts the 'off' timer and it returns false when the time given by 'delayOfTime' in msec is elapsed.
```cpp
bool delayOnOff(bool input, uint32_t delayTimeSwitchOn, uint32_t delayTimeSwitchOff);

// example: on delay 4000ms, off delay 2000ms
output1 = myTimer1.delayOnOff(input1, 4000, 2000);

// in : _______------------______---______________------------_------
// out: ___________----------_________________________---------------
```

### delayOn() ###
On delay only.\
Same as delayOnOff(), but on delay only.\
It works similar to the ton() function from the IEC-Timers which are well known in the PLC programming world.
```cpp
bool delayOn(bool input, uint32_t delayTimeSwitchOn);
  
// example: on delay 4000ms
output1 = myTimer1.delayOn(input1, 4000);

// in : _______------------____________---______
// out: ___________--------_____________________
```

### delayOff() ###
Off delay only.\
Same as delayOnOff(), but off delay only.\
It works similar to the tof() function from the IEC-Timers which are well known in the PLC programming world.
```cpp
bool delayOff(bool input, uint32_t delayTimeSwitchOff);

// example: off delay 2000ms
output1 = myTimer1.delayOff(input1, 2000);

// in : _______------------_______
// out: _______--------------_____
```

### delayOnOffTrigger() ###
On and off delay with output trigger.\
Timer on and off trigger.\
Sets the output to 0 once if the delayOffTime elapsed and if the output of delayOnOff() would go to 0.\
Sets the output to 1 once if the delayOnTime elapsed and if the output of delayOnOff() would go to 1.\
Sets the output to 2 if the time between cycles is running.
```cpp
byte delayOnOffTrigger(bool input, uint32_t delayTimeSwitchOff);

// example: on delay 4000ms, off delay 2000ms
switch (myTimer1.delayOnOffTrigger(input1, 4000, 2000))
{ 
  // timer elapsed, output = off now, gets executed just once
  case 0:
    Serial.println("Timer off finished: output == 0");
  break;
  
  // timer elapsed, output = on now, gets executed just once
  case 1:
    Serial.println("Timer on finished: output == 1");
  break;
  
  // timer is running
  case 2:
    // ...
  break;
}

// in : _______------------_________
// out: ___________1_________0______  (all "_" = 2)
// out: 2222222222212222222220222222  (it actually looks like this)
```
### delayOnTrigger() ###
On delay only with output trigger.\
The output gets just set once if the timer elapses.
```cpp
bool delayOnTrigger(bool input, uint32_t delayTimeSwitchOff);

// example: on delay 4000ms
if (myTimer1.delayOnTrigger(input1, 4000))
{ // timer elapsed - gets executed just once
  Serial.println("Timer on finished: input1 == 1");
}

// in : _______------------__________
// out: ___________-_________________
```

### delayOffTrigger() ###
Off delay only with output trigger.\
The output gets just set once if the timer elapses.
```cpp
bool delayOffTrigger(bool input, uint32_t delayTimeSwitchOff);

// example: off delay 2000ms
if (myTimer1.delayOffTrigger(input1, 2000))
{ // timer elapsed - gets executed just once
  Serial.println("Timer on finished: input1 == 0");
}

// in : _______------------__________
// out: _____________________-_______
```


## Timer Cycle ##

### cycle() ###
Sets the output between on and off by the given time intervals.
Could get used to create LED flashing or other intervals.
```cpp
bool cycle(uint32_t offTime, uint32_t onTime)

// example: LED off 4000ms, LED on 2000ms
LED1 = myTimer1.cycle(4000, 2000);

// out: ____--____--____--____--____
```
### cycleTrigger() ###
Sets the output to 0 once if the onTime elapsed and if the output of cycle() would go to 0.
Sets the output to 1 once if the offTime elapsed and if the output of cycle() would go to 1.
Sets the output to 2 if the time between cycles is running.
Could get used to run any action once if the cycle time is elapsed.
```cpp
byte cycleTrigger(uint32_t offTime, uint32_t onTime);

// example: off 4000ms, on 2000ms
out1 = myTimer1.cycle(4000, 2000);
if (out1 == 1)
{ // gets executed after 4000ms once, then the 2000ms delay starts

}
if (out1 == 0)
{ // gets executed after 2000ms once, then the 4000ms delay starts
  
}

// OUT: 2222|1|22|0|2222|1|22|0|2222
```

Creates a periodic output trigger.
```cpp
// triggers the output periodically once by the given cycleTime
bool cycleTrigger(uint32_t cycleTime);

// example: cycle time 4000ms
out1 = myTimer1.cycle(4000);

//OUT: ____-____-____-____-____
```

### cycleResetToOff() ###
Sets the output to off and starts the cycle time from now.
```cpp
    // timer cycle reset to off output, allows to synchronize cycle with other actions
    void cycleResetToOff(void);
```

### cycleResetToOn() ###
Sets the output to on and starts the cycle time from now.
```cpp
    // timer cycle reset to on output, allows to synchronize cycle with other action
    void cycleResetToOn(void);
```

## Timer Control ##
### delayReset() ###
Restarts the time from 0 and sets output != input at the next timer function call.
```cpp
void delayReset(void);
```

### delayElapse() ###
Ends the current running timer interval and sets output == input at the next timer function call.
```cpp
void delayElapse(void);
```

## Timer Information ##

### delayIsRunning() ###
Returns true if timer is still running.
```cpp
bool delayIsRunning(void);
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
```

