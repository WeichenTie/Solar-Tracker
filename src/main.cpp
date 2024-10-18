#include <esp32-hal.h>
#include <HardwareSerial.h>
#include "LedLightSensor.hpp"

LEDLightSensor sensor1 = LEDLightSensor(36, 19);

void setup()
{
  Serial.begin(115200);
  analogSetAttenuation(ADC_0db);
  delay(1000);
}




void loop()
{
  sensor1.update();
  Serial.print(">LightRawA: ");
  Serial.println(sensor1.getRawData());
  Serial.print(">LightFilteredA: ");
  Serial.println(sensor1.getFilteredData());
  delayMicroseconds(1);
}