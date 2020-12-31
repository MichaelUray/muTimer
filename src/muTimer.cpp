#include "muTimer.h"

// constructor
muTimer::muTimer(void)
{
}

// ------
// Timers
// ------

// timer on and off
bool muTimer::timerOnOff(bool input, uint32_t delayOnTime, uint32_t delayOffTime)
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
        if (millis() - _startTime >= delayOnTime)
            _output = 1;
    }

    // timer off
    if (_output && !input)
    {
        if (millis() - _startTime >= delayOffTime)
            _output = 0;
    }

    return _output;
}

// timer on
bool muTimer::timerOn(bool input, uint32_t delayOnTime)
{
    return timerOnOff(input, delayOnTime, 0);
}

// timer off
bool muTimer::timerOff(bool input, uint32_t delayOffTime)
{
    return timerOnOff(input, 0, delayOffTime);
}

// timer on and off trigger - generates a pulse once if time is elapsed
bool muTimer::timerOnOffTrigger(bool input, uint32_t delayOnTime, uint32_t delayOffTime)
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
        if (millis() - _startTime >= delayOnTime)
        {
            _output = 1;
            return 1;
        }
    }

    // timer off
    if (_output && !input)
    {
        if (millis() - _startTime >= delayOffTime)
        {
            _output = 0;
            return 1;
        }
    }

    return 0;
}

// timer on trigger - generates a pulse once if time is elapsed
bool muTimer::timerOnTrigger(bool input, uint32_t delayOnTime)
{
    return timerOnOffTrigger(input, delayOnTime, 0);
}

// timer off trigger - generates a pulse once if time is elapsed
bool muTimer::timerOffTrigger(bool input, uint32_t delayOffTime)
{
    return timerOnOffTrigger(input, 0, delayOffTime);
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
