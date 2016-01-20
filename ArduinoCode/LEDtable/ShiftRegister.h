#ifndef CELL_NUM
#define DATA_WIDTH 64 // Width of data (how many ext lines).
#else
#define DATA_WIDTH CELL_NUM
#endif

#ifndef PULSE_WIDTH_USEC
#define PULSE_WIDTH_USEC 5 // Width of clock pulse (us) to trigger the shift register to read and latch.
#endif

#ifndef SH_LD_PIN
#define SH_LD_PIN 8 // SH/LD(bar) pin: HIGH = shift, LOW = load.
#endif
#ifndef CLK_INH_PIN
#define CLK_INH_PIN 9 // CLK-INH pin: HIGH = disable clock, LOW = enable clock.
#endif
#ifndef QH_PIN
#define QH_PIN 11 // Q_H pin, data output.
#endif
#ifndef CLK_PIN
#define CLK_PIN 12 // CLK_PIN, rising edge triggers shift of the next bit.
#endif

// Read from daisy-chained shift registers.
void readShiftRegisters(bool pinValues[DATA_WIDTH])
{
  // Trigger a parallel Load to latch the state of the data lines.
  digitalWrite(CLK_INH_PIN, HIGH);
  digitalWrite(SH_LD_PIN, LOW);
  delayMicroseconds(PULSE_WIDTH_USEC);
  digitalWrite(SH_LD_PIN, HIGH);
  digitalWrite(CLK_INH_PIN, LOW);
  
  // Loop to read each bit value from the serial out line of the SN74HC165N.
  for(int i = 0; i < DATA_WIDTH; i++)
  {
    pinValues[i] = digitalRead(QH_PIN);
    
    // Pulse the Clock (rising edge shifts the next bit).
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(CLK_PIN, LOW);
  }
}

// Display pin values onto serial port.
void displayPinValues(bool pinValues[DATA_WIDTH])
{
  Serial.println("Pin States:");
  for(int i = 0; i < DATA_WIDTH; i++)
  {
    Serial.print("Pin-");
    Serial.print(i);
    Serial.print(": ");
    if(pinValues[i])
    {
      Serial.println("HIGH");
    }
    else
    {
      Serial.println("LOW");
    }
  }
}
