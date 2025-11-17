#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

class dotMatrix {
private:
  int _DIN;
  int _CLK;
  int _CS;

  MD_MAX72XX* mx;

  // ---------------- PATTERNS ----------------
  uint8_t offAll[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };

  // Big round “surprised” eye
  uint8_t shocked[8][8] = {
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 1, 1, 1, 1, 1, 0 }
  };

  // Normal “idle” eye
  uint8_t normal[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };

  // Laughing eye
  uint8_t laugh[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };

  // Symmetric closed eye (used for blink)
  uint8_t closed[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };

  // “Angry” version you had
  uint8_t leftMadOne[8][8] = {
    { 0, 1, 1, 1, 1, 1, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 1, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 1, 1, 1, 1, 1, 0 }
  };

  // Crying eye (single frame)
  uint8_t cry[8][8] = {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };
  uint8_t heart[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 0, 1, 1, 0 }
  };



  // ------------- INTERNAL HELPER -------------
  void drawPattern(const uint8_t pattern[8][8], bool transpose = true) {
    mx->clear();
    for (uint8_t row = 0; row < 8; row++) {
      for (uint8_t col = 0; col < 8; col++) {
        if (pattern[row][col]) {
          if (transpose) {
            mx->setPoint(col, row, true);  // rotated mapping (your hardware)
          } else {
            mx->setPoint(row, col, true);  // default mapping
          }
        }
      }
    }
  }

public:
  // Constructor
  dotMatrix(int DIN, int CLK, int CS) {
    _DIN = DIN;
    _CLK = CLK;
    _CS = CS;
    mx = new MD_MAX72XX(HARDWARE_TYPE, _DIN, _CLK, _CS, 1);
  }

  void dotMatrixBegin() {
    mx->begin();
    mx->clear();
    mx->control(MD_MAX72XX::SHUTDOWN, MD_MAX72XX::OFF);
    mx->control(MD_MAX72XX::INTENSITY, 8);
  }

  // --------- SIMPLE STATIC EXPRESSIONS ---------
  void off() {
    drawPattern(offAll);
  }
  void heartEyes() {
    drawPattern(heart);
  }
  void idleEyes() {  // uses “shocked” pattern
    drawPattern(shocked);
  }

  void normalEye() {
    drawPattern(normal);
  }

  void leftMadOneEye() {
    drawPattern(leftMadOne);
  }

  void laughEye() {
    drawPattern(laugh);
  }

  void closedEye() {
    drawPattern(closed);
  }

  void cryEye() {          // NEW: show crying eye
    drawPattern(cry);
  }

  // --------- PER-EYE ANIMATIONS (still available) ---------
  void blinkAnimation(uint8_t times = 2,
                      uint16_t openMs = 800,
                      uint16_t closedMs = 120) {
    for (uint8_t i = 0; i < times; i++) {
      normalEye();
      delay(openMs);

      closedEye();
      delay(closedMs);

      normalEye();
      delay(80);
    }
  }

  void laughAnimation(uint8_t times = 4,
                      uint16_t normalMs = 120,
                      uint16_t laughMs = 160) {
    for (uint8_t i = 0; i < times; i++) {
      normalEye();
      delay(normalMs);

      laughEye();
      delay(laughMs);
    }
    normalEye();
  }

  // --------- BOTH-EYES HELPERS (STATIC) ---------  // NEW

  static void blinkBoth(dotMatrix &left,
                        dotMatrix &right,
                        uint8_t times = 2,
                        uint16_t openMs = 800,
                        uint16_t closedMs = 120) {
    for (uint8_t i = 0; i < times; i++) {
      // both open
      left.normalEye();
      right.normalEye();
      delay(openMs);

      // both closed
      left.closedEye();
      right.closedEye();
      delay(closedMs);

      // open again
      left.normalEye();
      right.normalEye();
      delay(80);
    }
  }

  static void laughBoth(dotMatrix &left,
                        dotMatrix &right,
                        uint8_t times = 4,
                        uint16_t normalMs = 120,
                        uint16_t laughMs = 160) {
    for (uint8_t i = 0; i < times; i++) {
      left.normalEye();
      right.normalEye();
      delay(normalMs);

      left.laughEye();
      right.laughEye();
      delay(laughMs);
    }

    left.normalEye();
    right.normalEye();
  }

  static void cryBoth(dotMatrix &left,
                      dotMatrix &right,
                      uint16_t holdMs = 1000) {
    left.cryEye();
    right.cryEye();
    delay(holdMs);
  }
};

#endif
