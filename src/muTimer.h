#ifndef mTimer_h
#define mTimer_h
#include "Arduino.h"

class muTimer
{
public:
    // constructor
    muTimer(void);

    // ------
    // Timers
    // ------

    // timer on and off
    bool timerOnOff(bool input, uint32_t delayOnTime, uint32_t delayOffTime);

    // timer on
    bool timerOn(bool input, uint32_t delayOnTime);

    // timer off
    bool timerOff(bool input, uint32_t delayOffTime);

    // timer on and off trigger - generates a pulse once if time is elapsed
    bool timerOnOffTrigger(bool input, uint32_t delayOnTime, uint32_t delayOffTime);

    // timer on trigger - generates a pulse once if time is elapsed
    bool timerOnTrigger(bool input, uint32_t delayOnTime);

    // timer off trigger - generates a pulse once if time is elapsed
    bool timerOffTrigger(bool input, uint32_t delayOffTime);

    // timer cycle, sets the output between on and off by the given time intervals
    bool timerCycle(uint32_t offTime, uint32_t onTime);

    // timer cycle trigger
    // sets the output to 0 once if the onTime elapsed and if the output of timerCycle() would go to 0
    // sets the output to 1 once if the offTime elapsed and if the output of timerCycle() would go to 1
    // sets the output to 2 if the time between cycles is running
    byte timerCycleTrigger(uint32_t offTime, uint32_t onTime);

    // timer cycle reset to off output, allows to synchronize cycle with other actions
    void timerCycleResetToOff(void);

    // timer cycle reset to on output, allows to synchronize cycle with other action
    void timerCycleResetToOn(void);

    // -------------
    // Timer Control
    // -------------

    // restarts the time from 0 and sets output != input at next timer function call
    void timerReset(void);

    // ends the current running timer interval and sets output == input at next timer function call
    void timerElapse(void);

    // -----------------
    // Timer Information
    // -----------------

    // returns true if timer is still running
    bool timerIsRunning(void);

    // returns the time elapsed since start
    uint32_t getTimeElapsed(void);

private:
    bool _input_M;
    bool _output;
    uint32_t _startTime;
};

#endif /* mTimer_h */