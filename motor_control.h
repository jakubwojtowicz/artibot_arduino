#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "includes.h"

void setMotorDirection(char direction);
void setMotorSpeed(int target_speed);


#endif