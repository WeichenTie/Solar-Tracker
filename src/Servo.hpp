#include <esp32-hal-ledc.h>
#include "Arduino.h"
#include "Helpers.hpp"
class Servo
{
public:
    Servo(int pwmPin, int channel) : m_PWMPin(pwmPin), m_Channel(channel)
    {
        ledcSetup(m_Channel, 400, 16);
        ledcAttachPin(pwmPin, 0);
    };
    // Sets the speed between -1 to 1;
    void setSpeed(float value)
    {
        uint16_t output = static_cast<uint16_t>(Helpers::remap(-1.0f, 1.0f, MIN_PWM, MAX_PWM, value));
        ledcWrite(0, output);
    }

private:
    const int m_PWMPin;
    const int m_Channel;
    const static int MAX_PWM = 60030;
    const static int MIN_PWM = 18612;
    const static int STOP_PWM = 39321;
};