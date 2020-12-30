#ifndef mTimer_h
#define mTimer_h
#include "Arduino.h"

class muTimer
{
public:
    // constructor
    muTimer(void);

    // timer on and off
    bool timerOnOff(bool input, uint32_t delayOnTime, uint32_t delayOffTime);

    bool timerOn(bool input, uint32_t delayOnTime)
    {
        return timerOnOff(input, delayOnTime, 0);
    }

    bool timerOff(bool input, uint32_t delayOffTime)
    {
        return timerOnOff(input, 0, delayOffTime);
    }

    uint32_t getTimeElapsed(void);

private:
    bool _input_M;
    bool _output;
    uint32_t _startTime;
};

#endif /* mTimer_h */