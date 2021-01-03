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
    bool delayOnOff(bool input, uint32_t delayTimeSwitchOn, uint32_t delayTimeSwitchOff);

    // timer on
    bool delayOn(bool input, uint32_t delayTimeSwitchOn);

    // timer off
    bool delayOff(bool input, uint32_t delayTimeSwitchOff);

    // timer on and off trigger
    // sets the output to 0 once if the delayTimeSwitchOff elapsed and if the output of delayOnOff() would go to 0
    // sets the output to 1 once if the delayTimeSwitchOn elapsed and if the output of delayOnOff() would go to 1
    // sets the output to 2 if the time between cycles is running
    byte delayOnOffTrigger(bool input, uint32_t delayTimeSwitchOn, uint32_t delayTimeSwitchOff);

    // timer on trigger - generates a pulse once if time is elapsed
    bool delayOnTrigger(bool input, uint32_t delayTimeSwitchOn);

    // timer off trigger - generates a pulse once if time is elapsed
    bool delayOffTrigger(bool input, uint32_t delayTimeSwitchOff);

    // timer on/off cycle, sets the output between on and off by the given time intervals, could get used to create a flashing LED
    bool cycle(uint32_t offTime, uint32_t onTime);

    // timer on and off cycle trigger
    // sets the output to 0 once if the onTime elapsed and if the output of delayOnOffCycle() would go to 0
    // sets the output to 1 once if the offTime elapsed and if the output of delayOnOffCycle() would go to 1
    // sets the output to 2 if the time between cycles is running
    byte cycleTrigger(uint32_t offTime, uint32_t onTime);

    // triggers the output periodically once by the given cycleTime
    bool cycleTrigger(uint32_t cycleTime);

    // timer cycle reset to off output, allows to synchronize cycle with other timings
    void cycleResetToOff(void);

    // timer cycle reset to on output, allows to synchronize cycle with other timings
    void cycleResetToOn(void);

    // -------------
    // Timer Control
    // -------------

    // restarts the time from 0 and sets output != input at next timer function call
    void delayReset(void);

    // ends the current running timer interval and sets output == input at next timer function call
    void delayElapse(void);

    // -----------------
    // Timer Information
    // -----------------

    // returns true if timer is still running
    bool delayIsRunning(void);

    // returns the time elapsed since start
    uint32_t getTimeElapsed(void);

private:
    bool _input_M;
    bool _output;
    uint32_t _startTime;
};

#endif /* mTimer_h */