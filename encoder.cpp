#include "encoder.h"

const uint16_t resolution = 374;
float saved_time;
float previous_time;
const int impulses_array_size = 11;
float impulses[impulses_array_size];
uint8_t current_impulse;

void attachEncoderInterrupt()
{
  attachInterrupt(digitalPinToInterrupt(ENC), encoderInterrupt, RISING);
  initializeImpulses();
}

void encoderInterrupt()
{
  saved_time = micros();
  impulses[current_impulse] = (saved_time - previous_time)/1000000.0;
  previous_time = saved_time;
  current_impulse ++;
  if(current_impulse >= impulses_array_size)
  {
    current_impulse = 0;
  }
}

float measureSpeed()
{
  float sum = 0.0;
  for(int i = 0; i < impulses_array_size; i++)
  {
    sum += impulses[i];
  }
  if(sum == 0)
  {
    return 0;
  }

  float avg_speed = sum/(float)impulses_array_size;

  //if wheels are not spining
  if((micros()-previous_time)/1000000.0 > avg_speed*2)
  {
    return 0;
  }

  //return speed in rpm
  return (60.0/(float)resolution) / avg_speed;
}

void initializeImpulses()
{
  for(int i = 0; i< impulses_array_size; i++)
  {
    impulses[i] = 0.0;
  }
}