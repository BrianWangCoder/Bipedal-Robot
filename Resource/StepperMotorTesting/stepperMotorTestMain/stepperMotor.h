#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor {
  private:
    int dirPin;
    int stepPin;

  public:
    StepperMotor(int dir, int step) {
      dirPin  = dir;
      stepPin = step;
    }

    void beginStepper() {
      pinMode(dirPin, OUTPUT);
      pinMode(stepPin, OUTPUT);
    }

    void rotateCW(int speed) {
      digitalWrite(dirPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed);
    }

    void rotateACW(int speed) {
      digitalWrite(dirPin, HIGH);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speed);
    }
};

#endif
