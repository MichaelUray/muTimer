/*
  Example SerialMsecOverflowSafeTest.ino for muTimer library.
  Library source: https://github.com/MichaelUray/muTimer
  
  This example sets the current msec() return value 5s before uint32_t is overflowing and initiates then a 10s waiting time which reaches over the overflow value.
  It uses the delayOnTrigger() function.

  The serial monitor window should show then the following data:
  
  timer0_millis HEX: FFFFEC77
  timer0_millis DEC: 4294962295
  Init done.
  -----------------------------
  Delay-On triggered.
  timer0_millis HEX: 13AD
  timer0_millis DEC: 5037
  -----------------------------
  
  The library calls are non-blocking, means other code can get executed while the time duration is running.
*/

#include <muTimer.h>

muTimer myTimer1 = muTimer();
extern unsigned long timer0_millis;

void setup()
{
    Serial.begin(9600);

    noInterrupts();
    timer0_millis = UINT32_MAX - 5000;

    Serial.print("timer0_millis HEX: ");
    Serial.println(timer0_millis, HEX);
    Serial.print("timer0_millis DEC: ");
    Serial.println(timer0_millis, DEC);

    interrupts();

    Serial.println("Init done.");
    Serial.println("-----------------------------");
}

void loop()
{
    // 10000ms on delay, condition gets true only once if time is elapsed
    if (myTimer1.delayOnTrigger(1, 10000))
    {
        Serial.println("Delay-On triggered.");

        Serial.print("timer0_millis HEX: ");
        Serial.println(timer0_millis, HEX);
        Serial.print("timer0_millis DEC: ");
        Serial.println(timer0_millis, DEC);
        Serial.println("-----------------------------");
    }

    // The library is non-blocking.
    // Other code can get executed there in the meanwhile.
    // ...
}