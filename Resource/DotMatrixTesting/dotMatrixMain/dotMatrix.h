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

    uint8_t offAll[8][8] = {
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
    uint8_t shocked[8][8] = {
      {0,1,1,1,1,1,1,0},
      {1,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,1},
      {1,0,0,1,1,0,0,1},
      {1,0,0,1,1,0,0,1},
      {1,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,1},
      {0,1,1,1,1,1,1,0}
    };
    uint8_t normal[8][8] = {
      {0,0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1,0},
      {0,1,0,0,0,0,1,0},
      {0,1,0,1,1,0,1,0},
      {0,1,0,1,1,0,1,0},
      {0,1,0,0,0,0,1,0},
      {0,1,1,1,1,1,1,0},
      {0,0,0,0,0,0,0,0}
    };
    uint8_t laugh[8][8] = {
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1,0},
      {0,1,0,0,0,0,1,0},
      {0,1,0,1,1,0,1,0},
      {0,1,1,1,1,1,1,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
    uint8_t rightClosed[8][8] = {
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,0},
      {1,1,1,1,1,1,1,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
    uint8_t leftClosed[8][8] = {
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,1,1,1,1,1,1,1},
      {0,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
    uint8_t leftMadOne[8][8] = {
      {0,1,1,1,1,1,0,0},
      {1,0,0,0,0,0,1,0},
      {1,0,0,0,0,0,0,1},
      {1,0,0,1,1,0,0,1},
      {1,0,0,1,1,0,0,1},
      {1,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,1},
      {0,1,1,1,1,1,1,0}
    };

  public:
    // Correct constructor syntax
    dotMatrix(int DIN, int CLK, int CS) {
      _DIN = DIN;
      _CLK = CLK;
      _CS  = CS;

      // must allocate mx after pins are known
      mx = new MD_MAX72XX(HARDWARE_TYPE, _DIN, _CLK, _CS, 1);
    }

    void dotMatrixBegin() {
      mx->begin();
      mx->clear();
      mx->control(MD_MAX72XX::SHUTDOWN, MD_MAX72XX::OFF);
      mx->control(MD_MAX72XX::INTENSITY, 8);
    }

    void off() {
      mx->clear();
      for (uint8_t row = 0; row < 8; row++) {
        for (uint8_t col = 0; col < 8; col++) {
          if (offAll[row][col]) {
            mx->setPoint(row, col, true);
          }
        }
      }
    }
    void idleEyes() {
      mx->clear();
      for (uint8_t row = 0; row < 8; row++) {
        for (uint8_t col = 0; col < 8; col++) {
          if (shocked[row][col]) {
            mx->setPoint(row, col, true);
          }
        }
      }
    }
};

#endif
