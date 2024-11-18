#include "motor_control.h"

void setMotorDirection(char direction)
{
  if(direction == 'F')
  {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  }
  else if(direction == 'B')
  {
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  }
}

void setMotorSpeed(int target_speed)
{
  analogWrite(enA, calculatePI(target_speed, measureSpeed()));
}
