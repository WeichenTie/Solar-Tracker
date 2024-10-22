#include <esp32-hal.h>
#include <string.h>
#include "Arduino.h"

class LEDLightSensor
{
public:
    LEDLightSensor(int inputPin) : m_InputPin(inputPin)
    {
    }

    void setName(String name)
    {
        m_Name = name;
    }

    void update()
    {
        const float now = (float)micros() / 1000000.0;
        if (now - m_LastUpdate < 1.0 / UPDATE_FREQ)
            return;
        float reading = 0;
        for (int i = 0; i < SAMPLES_PER_UPDATE; i++)
        {
            reading += float(analogRead(m_InputPin));
        }
        m_RawData = reading / SAMPLES_PER_UPDATE;
        m_FilteredData = 0.87f * m_FilteredData + (1.0f - 0.87f) * m_RawData;
    }

    float getFilteredData() { return m_FilteredData; }
    float getRawData() { return m_RawData; }

private:
    const int m_InputPin;
    const float UPDATE_FREQ = 50;
    float m_LastUpdate = (float)micros() / 1000000.0;
    float m_FilteredData = 0.0;
    float m_RawData = 0.0;
    const int SAMPLES_PER_UPDATE = 10;
    String m_Name = String();
};