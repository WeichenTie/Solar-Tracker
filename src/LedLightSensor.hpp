#include <esp32-hal.h>
#include <string.h>
#include "Arduino.h"

class LEDLightSensor
{
public:
    LEDLightSensor(int inputPin, int drainPin) : m_InputPin(inputPin), m_DrainPin(drainPin)
    {
    }

    void setName(String name)
    {
        m_Name = name;
    }

    void update()
    {
        const float now = (float)micros() / 1000000.0;
        if (now - m_LastDrain > 1.0 / DRAIN_FREQ)
        {
            openDrain();
            delayMicroseconds(1);
            closeDrain();
            m_LastDrain = now;
        }
        if (now - m_LastUpdate < 1.0 / UPDATE_FREQ)
            return;
        float reading = 0;
        for (int i = 0; i < SAMPLES_PER_UPDATE; i++)
        {
            reading += float(analogRead(m_InputPin));
        }
        m_RawData = reading / SAMPLES_PER_UPDATE;
        m_FilteredData = 0.95f * m_FilteredData + (1.0f - 0.95f) * m_RawData;
    }

    float getFilteredData() { return m_FilteredData; }
    float getRawData() { return m_RawData; }

private:
    void openDrain()
    {
        pinMode(m_DrainPin, INPUT_PULLDOWN); // Set to pull down which will drain the charge in the capacitors;
    }
    void closeDrain()
    {
        pinMode(m_DrainPin, INPUT);
    }
    const int m_InputPin;
    const int m_DrainPin;
    const float UPDATE_FREQ = 50;
    const float DRAIN_FREQ = 75;
    float m_LastUpdate = (float)micros() / 1000000.0;
    float m_LastDrain = (float)micros() / 1000000.0;
    float m_FilteredData = 0.0;
    float m_RawData = 0.0;
    const int SAMPLES_PER_UPDATE = 200;
    String m_Name = String();
};