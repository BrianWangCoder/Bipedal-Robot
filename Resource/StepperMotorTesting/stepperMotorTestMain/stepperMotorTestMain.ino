#include "stepperMotor.h"

// Create StepperMotor object (NO 'new')
StepperMotor motor1(18, 19);   // DIR=18, STEP=19

void setup() {
  motor1.beginStepper();
  
}

void loop() {
  
}
