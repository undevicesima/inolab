#include <Arduino.h>
#include <Servo.h>

#define PIN_SERVO 3
#define DELAY_5S      delay(5000)
#define DELAY_1S      delay(1000)
#define DELAY_500MS   delay(500)
#define DELAY_50MS    delay(50)
#define LED_PIN A1
uint32_t value_potentiometer;
uint32_t value_servo;
Servo myServo;
uint32_t hua = 180;
uint32_t enzd = 1023;
uint32_t leG = 225;

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

void setLEDLevel(unsigned int val){
  analogWrite(LED_PIN,((val)/4U));
  Serial.print("mhh "); 
  Serial.println(((val)/4U));
}


void setup(){
  Serial.begin(9600);
  myServo.attach(PIN_SERVO);
  myServo.write(0);
  pinMode(LED_PIN,OUTPUT);
}

void outputValuesToConsole(){

  Serial.print("P: ");
  Serial.println(value_potentiometer);
  Serial.print("Servo: ");
  Serial.println(value_servo);
  Serial.print("success: ");
  Serial.println(setServoMotor(value_servo));

}

void loop()
{
  value_potentiometer = getPotentiometerValue();
  convertPotiServo();
  delay(30);
  setLEDLevel(value_potentiometer);
}
