#include <FastLED.h>

#define CELL_NUM 64 // Number of unit cells.

#define LED_PIN 6 // LED data pin.
#define SH_LD_PIN 8 // SH/LD(bar) pin: HIGH = shift, LOW = load.
#define CLK_INH_PIN 9 // CLK-INH pin: HIGH = disable clock, LOW = enable clock.
#define QH_PIN 11 // Q_H pin, data output.
#define CLK_PIN 12 // CLK_PIN, rising edge triggers shift of the next bit.

#include "LEDstrip.h"
// This header includes the following:
// (1) void writeUniformly(byte color)

#include "ShiftRegister.h"
// This header includes the following:
// (1) void readShiftRegisters(bool pinValues[DATA_WIDTH])
// (2) void displayPinValues(bool pinValues[DATA_WIDTH])

CRGB ledColorArray[CELL_NUM];
bool irSignalArray[CELL_NUM];

void setup()
{
  // Shift register part.
  Serial.begin(9600);
  pinMode(SH_LD_PIN, OUTPUT);
  pinMode(CLK_INH_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(QH_PIN, INPUT);
  
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(SH_LD_PIN, HIGH);
  
  // LED strip part, FastLED.h is included in LEDstrip.h. Initially set color yellow.
  FastLED.addLeds<NEOPIXEL, LED_PIN>(ledColorArray, CELL_NUM);
  writeUniformly(ledColorArray, CRGB::Yellow);
}

void loop()
{
  test1();
  delay(10);
}

// If any IR detector gives a HIGH, turn the LED from yellow to orange.
void test1()
{
  readShiftRegisters(irSignalArray);
  displayPinValues(irSignalArray);
  for (int i = 0; i < CELL_NUM; i++)
  {
    if (irSignalArray[i])
    {
      ledColorArray[i] = CRGB::Orange;
    }
    else
    {
      ledColorArray[i] = CRGB::Yellow;
    }
  }
  FastLED.show();
}

void test2()
{
  
}

