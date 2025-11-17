#include "dotMatrix.h"

// Use your pin numbers
#define DIN_PIN 32
#define CLK_PIN 33
#define CS_PIN  25

dotMatrix screen(DIN_PIN, CLK_PIN, CS_PIN);

void setup() {
  screen.dotMatrixBegin();
  
}

void loop() {
  screen.idleEyes();
}
