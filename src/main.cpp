#include <esp32-hal.h>
#include <HardwareSerial.h>
#include "LightSensor.hpp"
#include "Servo.hpp"
#include "PIDController.hpp"
LightSensor trSensor = LightSensor(13); // top right
LightSensor tlSensor = LightSensor(12); // top left

LightSensor brSensor = LightSensor(14); // bottom right
LightSensor blSensor = LightSensor(27); // bottom left

Servo servoWrist = Servo(26, 0);
Servo servoBase = Servo(25, 1);

PIDController wristController = PIDController(10, 0.000, 0.0f);
PIDController baseController = PIDController(0.75, 0.25, 0.0f);
void setup()
{
  Serial.begin(115200);
  delay(1000);
  trSensor.setMultipliers({0.85f, 0.0f, 0.0f, 0.0f}); // Set multipliers for compensation 
  // Aim to have 50% for top/bottom & right/left values
  baseController.zeroAndSetTarget(0.5f, 0.0f);
  wristController.zeroAndSetTarget(0.5f, 0.0f);
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

  // To prevent division by zero errors
  leftValue = leftValue <= 2.0f ? 1.0f : leftValue;
  rightValue = rightValue <= 2.0f ? 1.0f : rightValue;
  topValue = topValue <= 2.0f ? 1.0f : topValue;
  bottomValue = bottomValue <= 2.0f ? 1.0f : bottomValue;

  float topPercentage = topValue / (topValue + bottomValue);
  float leftPercentage = leftValue / (leftValue + rightValue);

  // Calculate the derived servo outputs
  float wristOut = wristController.compute(topPercentage);

  float baseOut = baseController.compute(leftPercentage);

  servoBase.setSpeed(baseOut);
  servoWrist.setSpeed(-wristOut);
  delay(10);
}