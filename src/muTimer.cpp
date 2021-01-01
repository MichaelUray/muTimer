#include "muTimer.h"

// constructor
muTimer::muTimer(void)
{
}

// ------
// Timers
// ------

// timer on and off
bool muTimer::timerOnOff(bool input, uint32_t delayTimeSwitchOn, uint32_t delayTimeSwitchOff)
{
    // has input changed?
    if (_input_M != input)
    {
        _input_M = input;
        _startTime = millis();
    }

    // timer on
    if (!_output && input)
    {
        if (millis() - _startTime >= delayTimeSwitchOn)
            _output = 1;
    }

    // timer off
    if (_output && !input)
    {
        if (millis() - _startTime >= delayTimeSwitchOff)
            _output = 0;
    }

    return _output;
}

// timer on
bool muTimer::timerOn(bool input, uint32_t delayTimeSwitchOn)
{
    return timerOnOff(input, delayTimeSwitchOn, 0);
}

// timer off
bool muTimer::timerOff(bool input, uint32_t delayTimeSwitchOff)
{
    return timerOnOff(input, 0, delayTimeSwitchOff);
}

// timer on and off trigger
// sets the output to 0 once if the delayTimeSwitchOff elapsed and if the output of timerOnOff() would go to 0
// sets the output to 1 once if the delayTimeSwitchOn elapsed and if the output of timerOnOff() would go to 1
// sets the output to 2 if the time between cycles is running
byte muTimer::timerOnOffTrigger(bool input, uint32_t delayTimeSwitchOn, uint32_t delayTimeSwitchOff)
{
    // has input changed?
    if (_input_M != input)
    {
        _input_M = input;
        _startTime = millis();
    }

    // timer on
    if (!_output && input)
    {
        if (millis() - _startTime >= delayTimeSwitchOn)
        {
            _output = 1;
            return 1;
        }
    }

    // timer off
    if (_output && !input)
    {
        if (millis() - _startTime >= delayTimeSwitchOff)
        {
            _output = 0;
            return 0;
        }
    }

    return 2;
}

// timer on trigger - generates a pulse once if time is elapsed
bool muTimer::timerOnTrigger(bool input, uint32_t delayTimeSwitchOn)
{
    return timerOnOffTrigger(input, delayTimeSwitchOn, 0);
}

// timer off trigger - generates a pulse once if time is elapsed
bool muTimer::timerOffTrigger(bool input, uint32_t delayTimeSwitchOff)
{
    return timerOnOffTrigger(input, 0, delayTimeSwitchOff);
}

// timer on/off cycle, sets the output between on and off by the given time intervals, could get used to create a flashing LED
bool muTimer::timerCycleOnOff(uint32_t offTime, uint32_t onTime)
{
    if (!_output)
    { // output is off, keep it off until offTime duration is reached
        if (millis() - _startTime >= offTime)
        {
            _output = 1;
            _startTime += offTime; // adding duration time instead of to set it to millis() keeps the interval more accurate
        }
    }
    else
    {
        if (millis() - _startTime >= onTime)
        { // output is on, keep it on until onTime duration is reached
            _output = 0;
            _startTime += onTime; // adding duration time instead of to set it to millis() keeps the interval more accurate
        }
    }

    return _output;
}

// timer on and off cycle trigger
// sets the output to 0 once if the onTime elapsed and if the output of timerCycleOnOff() would go to 0
// sets the output to 1 once if the offTime elapsed and if the output of timerCycleOnOff() would go to 1
// sets the output to 2 if the time between cycles is running
byte muTimer::timerCycleOnOffTrigger(uint32_t offTime, uint32_t onTime)
{
    if (!_output)
    { // output is off, keep it off until offTime duration is reached
        if (millis() - _startTime >= offTime)
        {
            _output = 1;
            _startTime += offTime; // adding the time duration since last start instead of to set it to millis() keeps the interval more accurate
            return 1;              // returns on trigger
        }
    }
    else
    { // output is on, keep it on until onTime duration is reached
        if (millis() - _startTime >= onTime)
        {
            _output = 0;
            _startTime += onTime; // adding the time duration since last start instead of to set it to millis() keeps the interval more accurate
            return 0;             // returns off trigger
        }
    }

    return 2; // returns time is running
}

// triggers the output cyclically by the given cycleTime
bool muTimer::timerCycleTrigger(uint32_t cycleTime)
{
    return timerCycleOnOffTrigger(cycleTime, 0) == 1;
}

// timer cycle reset to off output, allows to synchronize cycle with other action
void muTimer::timerCycleOnOffResetToOff(void)
{
    _output = 0;
    _startTime = millis();
}

// timer cycle reset to on output, allows to synchronize cycle with other action
void muTimer::timerCycleOnOffResetToOn(void)
{
    _output = 1;
    _startTime = millis();
}

// -------------
// Timer Control
// -------------

// restarts the time from 0 and sets output != input at next timer function call
void muTimer::timerReset(void)
{
    _startTime = millis();

    if (_input_M)
    {
        _output = 0;
    }
    else
    {
        _output = 1;
    }
}

// ends the current running timer interval and sets output == input at next timer function call
void muTimer::timerElapse(void)
{
    if (timerIsRunning())
        _output = _input_M;
}

// -----------------
// Timer Information
// -----------------

// returns true if timer is still running
bool muTimer::timerIsRunning(void)
{
    return _output != _input_M;
}

// returns the time elapsed since start
uint32_t muTimer::getTimeElapsed(void)
{
    return millis() - _startTime;
}
