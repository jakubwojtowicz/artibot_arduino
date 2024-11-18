#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "includes.h"

void attachEncoderInterrupt();
void encoderInterrupt();
float measureSpeed();
void initializeImpulses();

#endif