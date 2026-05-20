#include <Arduino.h>
#include <Servo.h>

#define PIN_SERVO 3
#define DELAY_5S      delay(5000)
#define DELAY_1S      delay(1000)
#define DELAY_500MS   delay(500)
#define DELAY_50MS    delay(50)

uint32_t value_potentiometer;
uint32_t value_servo;
Servo myServo;
uint32_t hua = 180;
uint32_t enzd = 1023;

bool setServoMotor(unsigned int pAngle)
{
  if (pAngle > 360)
    return false;

  myServo.write(pAngle);
  return true;
}

uint32_t getPotentiometerValue(){
  uint32_t sensorValue = analogRead(A0); // 0 -1023
  return sensorValue;
}


void convertPotiServo(){
  value_servo =(value_potentiometer * hua) / enzd;
}

void setup(){
  Serial.begin(9600);
  myServo.attach(PIN_SERVO);
  myServo.write(0);
}

void loop()
{
  value_potentiometer = getPotentiometerValue();
  convertPotiServo();
  delay(30);
  Serial.println(value_servo);
  delay(1);
  Serial.print("P: ");
  Serial.println(value_potentiometer);
  Serial.println(setServoMotor(value_servo));
}
