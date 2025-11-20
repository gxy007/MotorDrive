\
#ifndef MotorDrive_h
#define MotorDrive_h

#include <Arduino.h>

class MotorDrive {
public:
  MotorDrive(uint8_t left_pwm_pin, uint8_t left_dir_pin_a, uint8_t left_dir_pin_b,
             uint8_t right_pwm_pin, uint8_t right_dir_pin_a, uint8_t right_dir_pin_b,
             bool invert_left = false, bool invert_right = false);

  void begin();
  void move(int leftPWM, int rightPWM);
  void setInversion(bool invert_left, bool invert_right);

private:
  uint8_t _lpwm, _ldirA, _ldirB, _rpwm, _rdirA, _rdirB;
  bool _invertLeft, _invertRight;
  void applyMotor(uint8_t pwmPin, uint8_t dirA, uint8_t dirB, int pwmValue, bool invert);
  int clampPWM(int v);
};

#endif
