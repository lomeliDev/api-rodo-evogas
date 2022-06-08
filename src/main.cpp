#include <Arduino.h>
#include "Network.h"

void setup()
{
  Serial.begin(38400);
  setupAP();
}

void loop()
{
  delay(10);
}