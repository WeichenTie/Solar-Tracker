// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6)
#include <esp32-hal.h>
#include <HardwareSerial.h>
const int ledInPinA = 36;
const int ledInPinB = 34;
const int ledDrainPinA = 19;
const int ledDrainPinB = 18;

// variable for storing the potentiometer value
float prevDataA = 0;
float prevDataB = 0;
void setup()
{
  Serial.begin(115200);
  analogSetAttenuation(ADC_0db);
  delay(1000);
}

void loop()
{
  pinMode(ledDrainPinA, INPUT);
  pinMode(ledDrainPinB, INPUT);
  delay(25);
  // Reading potentiometer value
  float dataRawA = float(analogRead(ledInPinA));
  float dataFilteredA = 0.95f * prevDataA + (1.0f - 0.95f) * dataRawA;
  prevDataA = dataFilteredA;
  Serial.print(">LightRawA: ");
  Serial.println(dataRawA);
  Serial.print(">LightFilteredA: ");
  Serial.println(dataFilteredA);

  float dataRawB = float(analogRead(ledInPinB));
  float dataFilteredB = 0.95f * prevDataB + (1.0f - 0.95f) * dataRawB;
  prevDataB = dataFilteredB;
  Serial.print(">LightRawB: ");
  Serial.println(dataRawB);
  Serial.print(">LightFilteredB: ");
  Serial.println(dataFilteredB);

  pinMode(ledDrainPinA, INPUT_PULLDOWN);
  pinMode(ledDrainPinB, INPUT_PULLDOWN);

  delayMicroseconds(1);
}