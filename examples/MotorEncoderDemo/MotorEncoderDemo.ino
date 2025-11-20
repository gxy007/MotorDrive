\
/*
  MotorEncoderDemo.ino
  Example for Arduino Mega (example pins - adapt to your wiring)

  - MotorDrive library controls two motors via PWM + two direction pins each.
  - EncoderDrive library reads two quadrature encoders and provides speed_robot(ms).
*/

#include <MotorDrive.h>
#include <EncoderDrive.h>

// Example motor pins for Mega:
// Left motor: PWM 5, dirA 22, dirB 23
// Right motor: PWM 6, dirA 24, dirB 25
MotorDrive motors(4, 32, 34, 5, 30, 36);

// Example encoder pins for Mega:
// Left encoder A,B -> 2,3
// Right encoder A,B -> 18,19
EncoderDrive enc(3, 2, 19, 18,
                  192,   // ticks per revolution (set to your encoder's value)
                  0.066, // wheel diameter in meters
                  0.127); // wheel base in meters

unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  motors.begin();
  enc.begin();
  motors.move(0,0);
  delay(200);
}

void loop() {
  // Simple forward motion
  motors.move(100, 100);

  // Update speeds if at least 200 ms elapsed
  SpeedReport r = enc.speed_robot(200);

  if (millis() - lastPrint > 500) {
    lastPrint = millis();
    Serial.print("Left m/s: "); Serial.print(r.left_m_s, 4);
    Serial.print("  Right m/s: "); Serial.print(r.right_m_s, 4);
    Serial.print("  Linear m/s: "); Serial.print(r.linear_m_s, 4);
    Serial.print("  Angular rad/s: "); Serial.println(r.angular_rad_s, 4);
  }
}
