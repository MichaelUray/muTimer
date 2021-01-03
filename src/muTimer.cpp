#include "muTimer.h"

// constructor
muTimer::muTimer(void)
{
}

// ------
// Delays
// ------

// delay on and off
bool muTimer::delayOnOff(bool input, uint32_t delayTimeSwitchOn, uint32_t delayTimeSwitchOff)
{
    // has input changed?
    if (_input_M != input)
    {
        _input_M = input;
        _startTime = millis();
    }

    // delay on
    if (!_output && input)
    {
        if (millis() - _startTime >= delayTimeSwitchOn)
            _output = 1;
    }

    // delay off
    if (_output && !input)
    {
        if (millis() - _startTime >= delayTimeSwitchOff)
            _output = 0;
    }

    return _output;
}

// delay on
bool muTimer::delayOn(bool input, uint32_t delayTimeSwitchOn)
{
    return delayOnOff(input, delayTimeSwitchOn, 0);
}

// delay off
bool muTimer::delayOff(bool input, uint32_t delayTimeSwitchOff)
{
    return delayOnOff(input, 0, delayTimeSwitchOff);
}

// delay on and off with trigger output
// sets the output to 0 once if the delayTimeSwitchOff elapsed and if the output of delayOnOff() would go to 0
// sets the output to 1 once if the delayTimeSwitchOn elapsed and if the output of delayOnOff() would go to 1
// sets the output to 2 if the delay time is running
byte muTimer::delayOnOffTrigger(bool input, uint32_t delayTimeSwitchOn, uint32_t delayTimeSwitchOff)
{
    // has input changed?
    if (_input_M != input)
    {
        _input_M = input;
        _startTime = millis();
    }

    // delay on
    if (!_output && input)
    {
        if (millis() - _startTime >= delayTimeSwitchOn)
        {
            _output = 1;
            return 1;
        }
    }

    // delay off
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

// delay on with trigger output - gets true only once if the delay-on time is elapsed
bool muTimer::delayOnTrigger(bool input, uint32_t delayTimeSwitchOn)
{
    return delayOnOffTrigger(input, delayTimeSwitchOn, 0) == 1;
}

// delay off with trigger output - gets true only once if the delay-off time is elapsed
bool muTimer::delayOffTrigger(bool input, uint32_t delayTimeSwitchOff)
{
    return delayOnOffTrigger(input, 0, delayTimeSwitchOff) == 0;
}

// -------------
// Delay Control
// -------------

// restarts the time from 0 and sets output != input at next delay function call
void muTimer::delayReset(void)
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

// ends the current running delay interval and sets output == input at next delay function call
void muTimer::delayElapse(void)
{
    if (delayIsRunning())
        _output = _input_M;
}

// -----------------
// Delay Information
// -----------------

// returns true if the delay is still running
bool muTimer::delayIsRunning(void)
{
    return _output != _input_M;
}

// -----
// Cycle
// -----

// cycle on/off, sets the output between on and off by the given time intervals, could get used to create a flashing LED
bool muTimer::cycleOnOff(uint32_t onTime, uint32_t offTime)
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

// cycle on and off with output trigger
// sets the output to 0 once if the onTime elapsed and if the output of the cycle() function would go to 0
// sets the output to 1 once if the offTime elapsed and if the output of the cycle() function would go to 1
// sets the output to 2 if the time between cycles is running
byte muTimer::cycleOnOffTrigger(uint32_t offTime, uint32_t onTime)
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

// triggers the output cyclically by the given cycleTime, could get used to run periodically actions
bool muTimer::cycleTrigger(uint32_t cycleTime)
{
    return cycleOnOffTrigger(0, cycleTime) == 1;
}

// -------------
// Cycle Control
// -------------

// cycle reset to output off, allows to synchronize cycle with other timings
void muTimer::cycleResetToOff(void)
{
    _output = 0;
    _startTime = millis();
}

// cycle reset to output on, allows to synchronize cycle with other timings
void muTimer::cycleResetToOn(void)
{
    _output = 1;
    _startTime = millis();
}

// -------------------
// General Information
// -------------------

// returns the time elapsed since start
uint32_t muTimer::getTimeElapsed(void)
{
    return millis() - _startTime;
}
