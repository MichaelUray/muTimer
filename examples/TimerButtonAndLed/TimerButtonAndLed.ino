#include <muTimer.h>

muTimer myTimer1 = muTimer();

// processor pin definitions
#define PIN_BUTTON  3
#define PIN_LED 9

bool input;
bool output;

void setup()
{

  // configure input pin switch with internal pull-up resistor
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  // configure output pin LED
  pinMode(PIN_LED, OUTPUT);

}

void loop()
{
  input = digitalRead(PIN_BUTTON); // read input
  output = myTimer1.timerOnOff(input, 2000, 1000); // on delay 2000 ms, off delay 1000 ms
  digitalWrite(PIN_LED, output); // write output
}