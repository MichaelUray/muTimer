/*
 * Example SerialTimerOnTrigger.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example waits for 5s and it sends then once the string "Timer on finished." via the serial interface.
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
  // 5000ms on delay, condition gets true only once if time is elapsed
  if (myTimer1.timerOnTrigger(1, 5000))
  {
    Serial.println("Timer on finished.");
  }

  // The library is non-blocking.
  // Other code can get executed there in the meanwhile.
  // ...
}