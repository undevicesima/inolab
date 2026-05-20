#include <Arduino.h>
#include <Servo.h>

#define PIN_SERVO 3
#define DELAY_5S      delay(5000)
#define DELAY_1S      delay(1000)
#define DELAY_500MS   delay(500)
#define DELAY_50MS    delay(50)

uint16_t angle;
Servo myServo;

bool setServoMotor(unsigned int pAngle)
{
  if (pAngle > 360)
    return false;

  myServo.write(pAngle);
  return true;
}

void setup()
{
  myServo.attach(PIN_SERVO);
  myServo.write(0);
  angle = 0;
}

void loop()
{
  setServoMotor(90 * (m++) % 4);
  DELAY_5S;
}
