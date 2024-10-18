#include <esp32-hal-ledc.h>
class Servo
{
public:
    Servo(int pwmPin) : m_PWMPin(pwmPin) {
        // ledcSetup(m_PWMPin, 1111, 15);
    };
    // Sets the speed between -1 to 1;
    void setSpeed(float value) {

    }
private:
    const int m_PWMPin;
    const static int MAX_PWM;
    const static int MIN_PWM;
};
