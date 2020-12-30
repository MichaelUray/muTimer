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