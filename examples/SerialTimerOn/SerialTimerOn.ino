/*
 * Example SerialTimerOn.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example waits for 5s and it is sending then the string "Timer finished." permanently via the serial interface.
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
  // 5000ms on delay
  if (myTimer1.timerOn(1, 5000))
  {
    Serial.println("Timer finished.");
  }

  // library is non-blocking
  // other code can get executed there in the meanwhile
  // ...
}