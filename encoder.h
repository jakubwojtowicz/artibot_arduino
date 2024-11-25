#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
private:
    static constexpr uint16_t resolution = 374; // Encoder resolution
    static constexpr int impulsesArraySize = 11; // Size of the impulses array
    float impulses[impulsesArraySize];           // Array to store impulse times
    uint8_t currentImpulse;                     // Current index in the impulses array
    float savedTime;                            // Timestamp of the last interrupt
    float previousTime;                         // Timestamp of the previous interrupt
    float diameter_mm;                          // Wheel diameter
    bool newImpulseFlag;                        // Impulse flag 

    // Initialize the impulses array
    void initializeImpulses();

public:
    // Constructor
    Encoder(float diameter_mm);

    // Attach the encoder interrupt
    void attachInterruptHandler(uint8_t pin);

    // Interrupt handler (static to comply with attachInterrupt requirements)
    static void interruptHandler();

    // Process impulses
    void processImpulses();

    // Measure the speed RPM
    float measureSpeed();

    // Convert rpm to meters per second
    float rpmToMetersPerSecond(float rpm);

    // Convert meters per second to rpm
    float metersPerSecondToRpm(float speed_m_s);

};

#endif // ENCODER_H
