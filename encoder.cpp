#include "encoder.h"

// Static member variables (if required by attachInterrupt)
Encoder* encoderInstance = nullptr; // Pointer to a single Encoder instance for ISR compatibility

// Constructor
Encoder::Encoder(float wheelDiameter) : diameter_mm(wheelDiameter), currentImpulse(0), savedTime(0), previousTime(0), newImpulseFlag(false)
{
    initializeImpulses();
}

// Initialize the impulses array
void Encoder::initializeImpulses()
{
    for (int i = 0; i < impulsesArraySize; i++)
    {
        impulses[i] = 0.0;
    }
}

// Attach the encoder interrupt
void Encoder::attachInterruptHandler(uint8_t pin)
{
    encoderInstance = this; // Set the instance for the static ISR
    attachInterrupt(digitalPinToInterrupt(pin), interruptHandler, RISING);
}

// Static interrupt handler
void Encoder::interruptHandler()
{
    if (encoderInstance)
    {
        // Record timestamp and increment counter
        encoderInstance->savedTime = micros();
        encoderInstance->newImpulseFlag = true; // Set a flag to process in the main loop
    }
}

// Process impulses
void Encoder::processImpulses()
{
    if (newImpulseFlag)
    {
        impulses[currentImpulse] = (savedTime - previousTime) / 1000000.0;
        previousTime = savedTime;

        currentImpulse++;
        if (currentImpulse >= impulsesArraySize)
        {
            currentImpulse = 0;
        }

        newImpulseFlag = false; // Clear the flag
    }
}

// Measure the speed in RPM
float Encoder::measureSpeed()
{
    float sum = 0.0;
    for (int i = 0; i < impulsesArraySize; i++)
    {
        sum += impulses[i];
    }

    if (sum == 0)
    {
        return 0.0;
    }

    float avgSpeed = sum / (float)impulsesArraySize;

    // If wheels are not spinning
    if ((micros() - previousTime) / 1000000.0 > avgSpeed * 2)
    {
        return 0.0;
    }

    // Return speed in RPM
    return (60.0 / (float)resolution) / avgSpeed;
}

// Convert rpm to meters per second
float Encoder::rpmToMetersPerSecond(float rpm)
{
    float circumference_m = PI * (diameter_mm / 1000.0); // Convert diameter from mm to meters
    return (rpm * circumference_m) / 60.0; // Convert to m/s
}

// Convert meters per second to rpm
float Encoder::metersPerSecondToRpm(float speed_m_s)
{
    float circumference_m = PI * (diameter_mm / 1000.0); // Convert diameter from mm to meters
    return (speed_m_s * 60.0) / circumference_m; // Convert to RPM
}
