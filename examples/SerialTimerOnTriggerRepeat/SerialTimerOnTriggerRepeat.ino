/*
 * Example SerialTimerOnTriggerRepeat.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example waits for 1s and it sends then once the string "Timer on finished." via the serial interface. It does repeat this action all the time.
 * 
 * The library calls are non-blocking, means other code can get executed while the time duration is running.
 * 
 */
 #include <muTimer.h>

muTimer myTimer1 = muTimer();

void setup()
{
  Serial.begin(9600);
  Serial.println("Init done.");
}

void loop()
{
  // 1000ms on delay, gets only executed one if time is elapsed
  if (myTimer1.timerOnTrigger(1, 1000))
  {
    // resets timer to start time from 0
    myTimer1.timerReset();

    // prints string via the serial interface to the serial monitor
    Serial.println("Timer on finished.");
  }

  // The library is non-blocking.
  // Other code can get executed there in the meanwhile.
  // ...
}