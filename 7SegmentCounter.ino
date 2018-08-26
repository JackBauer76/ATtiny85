#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object

void setup()
{

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 12, 11, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(40);
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros

}

void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;

  if (millis() - timer >= 6000) {
    timer += 6000;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond

    if (deciSeconds == 1000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds = 0;
    }
    sevseg.setNumber(deciSeconds, 1);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}
