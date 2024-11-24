#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

class MotorController
{
private:
    uint8_t in1;        // Motor direction pin 1
    uint8_t in2;        // Motor direction pin 2
    uint8_t enA;        // Motor PWM speed control pin

public:
    // Constructor
    MotorController(uint8_t in1Pin, uint8_t in2Pin, uint8_t enAPin);

    // Set motor direction ('F' for forward, 'B' for backward)
    void setDirection(char direction);

    // Set motor speed
    void setSpeed(int pwm);

    // Stop motor
    void stop();
};


#endif