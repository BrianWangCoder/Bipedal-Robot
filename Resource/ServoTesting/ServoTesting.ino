#include "ServoController.h"
ServoController testServo = ServoController(13);
void setup() {
  testServo.begin();
}

void loop() {
  testServo.setAngle(0);
  testServo.smoothMove(180);
  testServo.smoothMove(0);
}
