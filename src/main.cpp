#include <esp32-hal.h>
#include <HardwareSerial.h>
#include "LedLightSensor.hpp"
#include "Servo.hpp"
LEDLightSensor tlSensor = LEDLightSensor(39);
LEDLightSensor blSensor = LEDLightSensor(36);
LEDLightSensor trSensor = LEDLightSensor(34);
LEDLightSensor brSensor = LEDLightSensor(35);

Servo servoWrist = Servo(12, 0);
Servo servoBase = Servo(14, 1);
void setup()
{
  Serial.begin(115200);
  delay(1000);
}
void loop()
{
  tlSensor.update();
  blSensor.update();
  trSensor.update();
  brSensor.update();

  float leftValue = tlSensor.getFilteredData() + blSensor.getFilteredData();
  float rightValue = trSensor.getFilteredData() + brSensor.getFilteredData();

  float topValue = tlSensor.getFilteredData() + trSensor.getFilteredData();
  float bottomValue = blSensor.getFilteredData() + brSensor.getFilteredData();

  float topPercentage = topValue / (topValue + bottomValue);
  float leftPercentage = leftValue / (leftValue + rightValue);

  if (topPercentage > 0.55)
  {
    servoWrist.setSpeed(0.2);
  }
  else if (topPercentage < 0.45)
  {
    Serial.println(-1);
  }
  else
  {
    servoWrist.setSpeed(0);
  }

  if (leftPercentage > 0.55)
  {
    servoBase.setSpeed(-0.065);
  }
  else if (leftPercentage < 0.45)
  {
    servoBase.setSpeed(0.045);
  }
  else
  {
    servoBase.setSpeed(0);
  }

  delayMicroseconds(1);
}