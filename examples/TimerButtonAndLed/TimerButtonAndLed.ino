#include <muTimer.h>

muTimer myTimer1 = muTimer();

// processor pin definitions
#define PIN_BUTTON 3
#define PIN_LED 9

bool input1;
bool output1;

void setup()
{
  // configure input hardware pin with internal pull-up resistor
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // configure output hardware pin
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  // read input (button) from hardware
  input1 = digitalRead(PIN_BUTTON);

  // on delay 2000 ms, off delay 1000 ms
  output1 = myTimer1.timerOnOff(input1, 2000, 1000);

  // write output (LED) to hardware
  digitalWrite(PIN_LED, output1);
}