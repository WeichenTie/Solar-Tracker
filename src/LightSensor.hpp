#include <esp32-hal.h>
#include <string.h>
#include "Arduino.h"



class LightSensor
{

    struct Multipliers {
        float a1;
        float a2;
        float a3;
        float a4;
    };
public:
    LightSensor(int inputPin) : m_InputPin(inputPin) {
    }

    void setMultipliers(Multipliers multiplier) {
        m_Multipliers = multiplier;
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
        // Take multiple samples
        float reading = 0;
        for (int i = 0; i < SAMPLES_PER_UPDATE; i++)
        {
            reading += float(analogRead(m_InputPin));
        }
        m_RawData = reading / SAMPLES_PER_UPDATE;

        // Software error correction
        m_RawData = m_Multipliers.a4 * pow(m_RawData, 4) + m_Multipliers.a3 * pow(m_RawData, 3) + m_Multipliers.a2 * pow(m_RawData, 2) +  m_RawData * m_Multipliers.a1;
        // Butterworth filter
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
    Multipliers m_Multipliers = Multipliers{1.0f, 0.0f, 0.0f, 0.0f};
};