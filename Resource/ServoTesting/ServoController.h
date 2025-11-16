#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

class ServoController {
  private:
    Servo servo;   // the servo object (composition)
    int pin;       // the pin it's attached to
    int currentAngle; // track current angle

  public:
    // Constructor
    ServoController(int pinNumber) {
      pin = pinNumber;
      currentAngle = 90; // start at center position
    }

    // Attach the servo
    void begin() {
      servo.attach(pin);
      servo.write(currentAngle);
    }

    // Move instantly to a specific angle
    void setAngle(int angle) {
      currentAngle = constrain(angle, 0, 180);
      servo.write(currentAngle);
    }

    // Smooth motion to target angle
    void smoothMove(int targetAngle, int stepDelay = 10) {
      targetAngle = constrain(targetAngle, 0, 180);
      if (targetAngle > currentAngle) {
        for (int i = currentAngle; i <= targetAngle; i++) {
          servo.write(i);
          delay(stepDelay);
        }
      } else {
        for (int i = currentAngle; i >= targetAngle; i--) {
          servo.write(i);
          delay(stepDelay);
        }
      }
      currentAngle = targetAngle;
    }

    // Get current angle
    int getAngle() {
      return currentAngle;
    }
};

#endif
