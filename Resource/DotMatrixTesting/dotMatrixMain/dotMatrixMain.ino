#include "dotMatrix.h"

dotMatrix screenLeft(32, 33, 25);
dotMatrix screenRight(14, 26, 27);

void setup() {
  screenLeft.dotMatrixBegin();
  screenRight.dotMatrixBegin();

  screenLeft.normalEye();
  screenRight.normalEye();
}

void loop() {
  // Blink both eyes together
  dotMatrix::blinkBoth(screenLeft, screenRight);
  delay(500);

  // Laugh with both eyes together
  dotMatrix::laughBoth(screenLeft, screenRight);
  delay(500);

  // Cry with both eyes together
  dotMatrix::cryBoth(screenLeft, screenRight, 800);
  delay(1000);

  screenLeft.heartEyes();
  screenRight.heartEyes();
  delay(1000);
}
