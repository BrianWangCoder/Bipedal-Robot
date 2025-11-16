#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor {
  private:
    int dirPin;
    int stepPin;
    int minValue = 400;
    int maxValue = 7000;

    const float baseStepAngle = 1.8; // degrees per FULL step for most NEMA17
    int microsteps = 1;     

    long currentStep = 0;         

    void singleStepCW(int speedMicros) {
      constrain(speedMicros, minValue, maxValue);
      digitalWrite(dirPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speedMicros);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speedMicros);
      currentStep++;
    }

    // do ONE microstep ACW
    void singleStepACW(int speedMicros) {
      constrain(speedMicros, minValue, maxValue);
      digitalWrite(dirPin, HIGH);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speedMicros);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speedMicros);
      currentStep--;
    }

  public:
    StepperMotor(int dir, int step) {
      dirPin  = dir;
      stepPin = step;
    }
    void beginStepper() {
      pinMode(dirPin, OUTPUT);
      pinMode(stepPin, OUTPUT);
    }

    void rotateCW(int speedMicros) {
      singleStepCW(speedMicros);
    }
    void rotateACW(int speedMicros) {
      singleStepACW(speedMicros);
    }
    void rotateCWAngle(float angleDeg, int speedMicros) {
      // angle per microstep:
      float anglePerMicrostep = baseStepAngle / microsteps;
      long stepsNeeded = angleDeg / anglePerMicrostep;

      for (long i = 0; i < stepsNeeded; i++) {
        singleStepCW(speedMicros);
      }
    }
    void rotateACWAngle(float angleDeg, int speedMicros) {
      // angle per microstep:
      float anglePerMicrostep = baseStepAngle / microsteps;
      long stepsNeeded = angleDeg / anglePerMicrostep;

      for (long i = 0; i < stepsNeeded; i++) {
        singleStepACW(speedMicros);
      }
    }
    void goToAngle(float targetAngleDeg, int speedMicros) {
      float anglePerMicrostep = baseStepAngle / microsteps;
      long targetStep = targetAngleDeg / anglePerMicrostep;
      long delta = targetStep - currentStep;

      if (delta > 0) {
        for (long i = 0; i < delta; i++) {
          singleStepCW(speedMicros);
        }
      } else if (delta < 0) {
        for (long i = 0; i < -delta; i++) {
          singleStepACW(speedMicros);
        }
      }
    }
};

#endif
