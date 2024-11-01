#include <esp32-hal-ledc.h>
#include "Arduino.h"
#include "Helpers.hpp"
class Servo
{
public:
    Servo(int pwmPin, int channel) : m_PWMPin(pwmPin), m_Channel(channel)
    {
        ledcSetup(m_Channel, 400, 16);
        ledcAttachPin(m_PWMPin, m_Channel);
    };
    // Sets the speed of the servo
    void setSpeed(float value)
    {
        value = constrain(value, -0.99, 0.99);
        uint16_t output = static_cast<uint16_t>(Helpers::remap(-1.0f, 1.0f, MIN_PWM, MAX_PWM, value));
        ledcWrite(m_Channel, output);
    }

private:
    const int m_PWMPin;
    const int m_Channel;
    // PWM tunings for FS90 servo @ 400hz + 16 bits resolution
    const static uint16_t MAX_PWM = 60030;
    const static uint16_t MIN_PWM = 18612;
    const static uint16_t STOP_PWM = 39321;
};