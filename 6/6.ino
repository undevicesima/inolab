#include <Arduino.h>
#include <Servo.h>

#define PIN_SERVO 3
#define DELAY_5S      delay(5000)
#define DELAY_1S      delay(1000)
#define DELAY_500MS   delay(500)
#define DELAY_50MS    delay(50)
#define LED_PIN 11
uint32_t value_potentiometer;
uint32_t value_servo;
Servo myServo;
uint32_t hua = 180;
uint32_t enzd = 1023;
uint32_t leG = 225;
int c = 0;
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

void setLEDLevel(unsigned int pVal){
    // Wert auf PWM-Bereich umrechnen (0-255)
    // map(value, fromLow, fromHigh, toLow, toHigh)
    int brightness = map(pVal, 0, 1023, 0, 255);
    // LED-Helligkeit setzen
    analogWrite(LED_PIN, brightness);
}


void setup(){
  Serial.begin(9600);
  myServo.attach(PIN_SERVO);
  myServo.write(0);
  pinMode(LED_PIN,OUTPUT);
}

void outputValuesToConsole(){
  if(c > 10){
    c=0;
    Serial.print(",");
    Serial.print("potentiometer:");
    Serial.print(value_potentiometer);
    Serial.print(",");
    Serial.print("servo:");
    Serial.println(value_servo);
    Serial.print(",");
    Serial.print("LED:");
    Serial.print(value_potentiometer/4U);

  }
  c++;
}

void loop()
{
  value_potentiometer = getPotentiometerValue();
  convertPotiServo();
  setLEDLevel(value_potentiometer);
  outputValuesToConsole();
  setServoMotor(value_servo);
  delay(30);
}
