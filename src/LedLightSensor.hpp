#include <esp32-hal.h>
#include <string.h>
#include "Arduino.h"

class LEDLightSensor
{
public:
    LEDLightSensor(int inputPin, int drainPin) : m_InputPin(inputPin), m_DrainPin(drainPin)
    {
    }
    void setUpdateFrequency(float freq)
    {
        m_UpdateFrequency = freq;
    }
    void setName(String name) {
        m_Name = name;
    }
    void openDrain()
    {
        pinMode(m_DrainPin, INPUT_PULLDOWN); // Set to pull down which will drain the charge in the capacitors;
    }
    void closeDrain()
    {
        pinMode(m_DrainPin, INPUT);
    }
    void update()
    {
        const float now = (float)micros() / 1000000.0;
        if (now - m_LastUpdate < 1.0 / m_UpdateFrequency)
            return;

        m_RawData = float(analogRead(m_InputPin));
        m_FilteredData = 0.95f * m_FilteredData + (1.0f - 0.95f) * m_RawData;
    }

    float getFilteredData() { return m_FilteredData; }
    float getRawData() { return m_RawData; }

private:
    const int m_InputPin;
    const int m_DrainPin;
    float m_UpdateFrequency = 50;
    float m_LastUpdate = (float)micros() / 1000000.0;
    float m_FilteredData = 0.0;
    float m_RawData = 0.0;
    String m_Name = String();
};