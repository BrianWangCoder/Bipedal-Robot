#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// I2C address 0x40 is default for most PCA9685 boards.
// If you changed A0–A5 address jumpers, adjust this.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// ---- Servo timing (tune if needed) ----
// Most analog servos: ~500–2500 µs for 0–180°.
// Many work well with 600–2400 µs. Calibrate yours!
const int SERVO_MIN_US = 600;   // pulse at 0°
const int SERVO_MAX_US = 2400;  // pulse at 180°
const int SERVO_FREQ   = 50;    // Hz (standard)

int angleToMicros(float deg) {
  // constrain angle and map to pulse width
  deg = constrain(deg, 0.0, 180.0);
  return SERVO_MIN_US + (int)((SERVO_MAX_US - SERVO_MIN_US) * (deg / 180.0));
}

// Convert microseconds to 12-bit ticks for PCA9685 at given frequency
uint16_t microsToTicks(int us) {
  // 4096 ticks per period
  // period (µs) = 1e6 / SERVO_FREQ
  float period_us = 1000000.0f / SERVO_FREQ;
  float ticks = (us * 4096.0f) / period_us;
  // Clamp to [0, 4095]
  if (ticks < 0) ticks = 0;
  if (ticks > 4095) ticks = 4095;
  return (uint16_t)(ticks);
}

// Write an angle to a PCA9685 channel
void writeServoAngle(uint8_t channel, float deg) {
  int us = angleToMicros(deg);
  uint16_t on = 0;
  uint16_t off = microsToTicks(us);
  pwm.setPWM(channel, on, off);
}

void setup() {
  // If you use different I2C pins on ESP32, set them here:
  // Default ESP32 I2C is SDA=21, SCL=22.
  Wire.begin(21, 22);

  pwm.begin();
  // Use the internal oscillator; for most boards this is fine.
  // If you have timing drift, you can call pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10); // allow frequency to settle

  // Move both servos to a known start angle
  writeServoAngle(0, 90);  // CH0 @ 90°
  writeServoAngle(1, 90);  // CH1 @ 90°
}

void loop() {
  // Simple demo: sweep both servos 0→180→0
  for (int a = 0; a <= 180; a += 2) {
    writeServoAngle(0, a);
    writeServoAngle(1, 180 - a);
    delay(10);
  }
  for (int a = 180; a >= 0; a -= 2) {
    writeServoAngle(0, a);
    writeServoAngle(1, 180 - a);
    delay(10);
  }
}
