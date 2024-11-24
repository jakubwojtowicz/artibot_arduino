#include "PI.h"


// Constructor
PIRegulator::PIRegulator(float kp, float ki) : Kp(kp), Ki(ki), integral(0) {}

// Calculate the PI output
int PIRegulator::calculate(int targetSpeed, int measuredSpeed)
{
    int error = targetSpeed - measuredSpeed;

    // Update the integral
    integral += error;

    // Calculate the output
    float output = Kp * error + Ki * integral;

    // Apply output limits and anti-windup
    if (output > 255)
    {
        integral -= error; // Anti-windup
        output = 255;
    }
    else if (output < 0)
    {
        output = 0;
    }

    return static_cast<int>(output);
}

// Reset the integral term
void PIRegulator::reset()
{
    integral = 0;
}