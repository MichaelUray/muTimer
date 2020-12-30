#include "muTimer.h"

// constructor
muTimer::muTimer(void)
{
}

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

uint32_t muTimer::getTimeElapsed(void)
{
    return millis() - _startTime;
}
