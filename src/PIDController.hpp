#pragma once

#include "Arduino.h"

// PI is probably enough, too much noise for derivative to work reliably
class PIDController
{
public:
    PIDController(float kp, float ki, float kd) : kp(kp), ki(ki), kd(kd) {}

    // Compute the output signal required from the current/actual value.
    float compute(float input)
    {
        curr_time = micros();
        dt = static_cast<float>(curr_time - prev_time) / 1e6;
        prev_time = curr_time;

        error = setpoint - (input - zero_ref);
        derivative = (error - prev_error) / dt;
        integral = constrain(integral + error * dt, -100.0f, 100.0f);
        prev_error = error;

        output = error * kp + derivative * kd + integral * ki;
        return output;
    }

    // Function used to return the last calculated error.
    // The error is the difference between the desired position and current position.
    void tune(float p, float i, float d)
    {
        kp = p;
        ki = i;
        kd = d;
    }
    float getError()
    {
        return error;
    }
    // This must be called before trying to achieve a setpoint.
    // The first argument becomes the new zero reference point.
    // Target is the setpoint value.
    void zeroAndSetTarget(float zero, float target)
    {
        prev_time = micros();
        zero_ref = zero;
        setpoint = target;
    }

private:
    uint32_t prev_time, curr_time = micros();
    float dt;
    float kp, ki, kd;
    float error, derivative;
    float integral = 0;
    float output = 0;
    float prev_error = 0;
    float setpoint = 0;
    float zero_ref = 0;
};
