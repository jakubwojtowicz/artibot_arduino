#include "PI.h"

//#PI Regulator
float Kp = 0.2;
float Ki = 0.15;
float integral = 0;

int calculatePI(int target_speed, int measured_speed)
{
  int error = target_speed - measured_speed;
  //calculate integral - short method 
  integral += error;

  float output = Kp * error + Ki * integral;

  //output = target_speed;
  //regulator limitations
  if (output > 255)
  {
      //anti windup
      integral -= error;
      output = 255;
  }

  else if (output <= 0)
  {
      output = 0;
  }

  return output;
}

void resetPI()
{
  integral = 0;
}