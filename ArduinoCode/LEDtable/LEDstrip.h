#include <FastLED.h>

#ifndef CELL_NUM
#define LED_NUM 64 // Number of LEDs.
#else
#define LED_NUM CELL_NUM
#endif

#ifndef LED_PIN
#define LED_PIN 6 // LED data pin.
#endif

void writeUniformly(CRGB ledColorArray[LED_NUM], byte color)
{
  // Write all LEDs to the same color.
  for (int i = 0; i < LED_NUM; i++)
  {
    ledColorArray[i] = color;
  }
  FastLED.show();
}

