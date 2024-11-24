#include "motor_control.h"

// Constructor
MotorController::MotorController(uint8_t in1Pin, uint8_t in2Pin, uint8_t enAPin)
    : in1(in1Pin), in2(in2Pin), enA(enAPin)
{
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enA, OUTPUT);
}

// Set motor direction
void MotorController::setDirection(char direction)
{
    if (direction == 'B') // Forward
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }
    else if (direction == 'F') // Backward
    {
        digitalWrite(in2, LOW);
        digitalWrite(in1, HIGH);
    }
}

// Set motor speed
void MotorController::setSpeed(int pwm)
{
    analogWrite(enA, pwm);
}
