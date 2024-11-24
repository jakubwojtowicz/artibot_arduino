#ifndef PIREGULATOR_H
#define PIREGULATOR_H

#include <Arduino.h>

class PIRegulator
{
private:
    float Kp;       // Proportional gain
    float Ki;       // Integral gain
    float integral; // Integral accumulator

public:
    // Constructor
    PIRegulator(float kp, float ki);

    // Calculate the PI output
    int calculate(int targetSpeed, int measuredSpeed);

    // Reset the integral term
    void reset();
};

#endif // PIREGULATOR_H