\
#include "MotorDrive.h"

MotorDrive::MotorDrive(uint8_t left_pwm_pin, uint8_t left_dir_pin_a, uint8_t left_dir_pin_b,
                       uint8_t right_pwm_pin, uint8_t right_dir_pin_a, uint8_t right_dir_pin_b,
                       bool invert_left, bool invert_right)
  : _lpwm(left_pwm_pin), _ldirA(left_dir_pin_a), _ldirB(left_dir_pin_b),
    _rpwm(right_pwm_pin), _rdirA(right_dir_pin_a), _rdirB(right_dir_pin_b),
    _invertLeft(invert_left), _invertRight(invert_right)
{}

void MotorDrive::begin() {
  pinMode(_lpwm, OUTPUT);
  pinMode(_ldirA, OUTPUT);
  pinMode(_ldirB, OUTPUT);
  pinMode(_rpwm, OUTPUT);
  pinMode(_rdirA, OUTPUT);
  pinMode(_rdirB, OUTPUT);

  digitalWrite(_ldirA, LOW);
  digitalWrite(_ldirB, LOW);
  analogWrite(_lpwm, 0);

  digitalWrite(_rdirA, LOW);
  digitalWrite(_rdirB, LOW);
  analogWrite(_rpwm, 0);
}

void MotorDrive::setInversion(bool invert_left, bool invert_right) {
  _invertLeft = invert_left;
  _invertRight = invert_right;
}

int MotorDrive::clampPWM(int v) {
  if (v > 255) return 255;
  if (v < -255) return -255;
  return v;
}

void MotorDrive::applyMotor(uint8_t pwmPin, uint8_t dirA, uint8_t dirB, int pwmValue, bool invert) {
  pwmValue = clampPWM(pwmValue);
  if (invert) pwmValue = -pwmValue;

  if (pwmValue == 0) {
    digitalWrite(dirA, LOW);
    digitalWrite(dirB, LOW);
    analogWrite(pwmPin, 0);
    return;
  }

  if (pwmValue > 0) {
    digitalWrite(dirA, HIGH);
    digitalWrite(dirB, LOW);
    analogWrite(pwmPin, pwmValue);
  } else {
    digitalWrite(dirA, LOW);
    digitalWrite(dirB, HIGH);
    analogWrite(pwmPin, -pwmValue);
  }
}

void MotorDrive::move(int leftPWM, int rightPWM) {
  applyMotor(_lpwm, _ldirA, _ldirB, leftPWM, _invertLeft);
  applyMotor(_rpwm, _rdirA, _rdirB, rightPWM, _invertRight);
}
