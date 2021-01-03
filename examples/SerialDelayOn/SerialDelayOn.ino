/*
 * Example SerialDelayOn.ino for muTimer library.
 * Library source: https://github.com/MichaelUray/muTimer
 * 
 * This example waits for 5s and it is sending then the string "Delay-On finished." permanently via the serial interface.
 * It uses the delayOn() function.
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
  // Input is set permanent to true, so it gets executed all the time when the 5s are elapsed.
  if (myTimer1.delayOn(1, 5000))
  {
    Serial.println("Delay-On finished.");
  }

  // library is non-blocking
  // other code can get executed there in the meanwhile
  // ...
}