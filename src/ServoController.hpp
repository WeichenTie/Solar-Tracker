#include <esp32-hal-ledc.h>
#include "Servo.hpp"
#include "LedLightSensor.hpp"
class DirectionController
{
public:
    DirectionController(LEDLightSensor sensorA, LEDLightSensor sensorB, Servo servo)
        : m_SensorA(sensorA),
          m_SensorB(sensorB),
          m_Servo(servo) {
              // ledcSetup(m_PWMPin, 1111, 15);
          };
    // Sets the speed between -1 to 1;
    void compute() {
        const float delta = m_SensorA.getFilteredData() - m_SensorB.getFilteredData();
        if (delta > 0) {
            m_Servo.setSpeed(-1);
        } 
        else {
            m_Servo.setSpeed(1);
        }
    }

private:
    LEDLightSensor m_SensorA;
    LEDLightSensor m_SensorB;
    Servo m_Servo;
};
