#include <Arduino.h>
#include <Servo.h>

#define PIN_SERVO 3
#define DELAY_5S      delay(5000)
#define DELAY_1S      delay(1000)
#define DELAY_500MS   delay(500)
#define DELAY_50MS    delay(50)

uint16_t value_potentiometer;
uint16_t angle;
Servo myServo;

bool setServoMotor(unsigned int pAngle)
{
  if (pAngle > 360)
    return false;

  myServo.write(pAngle);
  return true;
}

uint16_t getPotentiometerValue(){
  uint16_t sensorValue = analogRead(A0); // 0 -1023
  // print out the value you read:
  Serial.println(sensorValue);
  return sensorValue;
  }

byte m = 0;
void setup(){
  Serial.begin(9600);
  myServo.attach(PIN_SERVO);
  myServo.write(0);
  angle = 0;
}

void loop()
{
  value_potentiometer = getPotentiometerValue();
  delay(30);
}
