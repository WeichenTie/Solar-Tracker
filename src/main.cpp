#include <esp32-hal.h>
#include <HardwareSerial.h>
#include "LedLightSensor.hpp"
#include "Servo.hpp"
LEDLightSensor topSensor = LEDLightSensor(36, 32);
LEDLightSensor bottomSensor = LEDLightSensor(39, 33);

Servo servoWrist = Servo(12, 0);
void setup()
{
  Serial.begin(115200);
  analogSetAttenuation(ADC_2_5db);
  delay(1000);
}
void loop()
{
  topSensor.update();
  Serial.print(">Sensor1LightRawA: ");
  Serial.println(topSensor.getRawData());
  Serial.print(">Sensor1LightFilteredA: ");
  Serial.println(topSensor.getFilteredData());

  bottomSensor.update();
  Serial.print(">Sensor2LightRawB: ");
  Serial.println(bottomSensor.getRawData());
  Serial.print(">Sensor2LightFilteredB: ");
  Serial.println(bottomSensor.getFilteredData());
  float topPercentage = (topSensor.getFilteredData() / (topSensor.getFilteredData() + bottomSensor.getFilteredData()));

  if (topPercentage > 0.575)
  {
    servoWrist.setSpeed(-0.5);
  }
  else if (topPercentage < 0.425)
  {
    servoWrist.setSpeed(0.5);
  }
  else
  {
    servoWrist.setSpeed(0);
  }

  delayMicroseconds(1);
}