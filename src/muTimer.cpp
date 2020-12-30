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

// -------------
// Timer Control
// -------------

// restarts the current running time interval from 0 (only if timer is still running)
void muTimer::timerReset(void)
{
    if (timerIsRunning())
        _startTime = millis();
}

// ends the current running time intervall
void muTimer::timerElapse(void)
{
    if (timerIsRunning())
        _output = _input_M;
}

// -----------------
// Timer Information
// -----------------

// returns if timer is still running
bool muTimer::timerIsRunning(void)
{
    return _output != _input_M;
}

// returns the time elapsed since start
uint32_t muTimer::getTimeElapsed(void)
{
    return millis() - _startTime;
}
