/*
<Info>
  <Title> ArtiBot motor speed measurement and regulation. </Title> 
  <Author> Jakub Wójtowicz </Author>
  <Creation Date> 05.12.2023 </Creation Date>
</Info>
<Motor settings>
  <Max rpm> 220 </Max rpm> 
  <Min rpm> 30 </Min rpm>
  <Encoder resolution> 374 </Encoder resolution>
</Motor settings>
*/

#include "includes.h"
#include <Servo.h>
#include <TimerOne.h>

int target_speed = 0;
char target_direction = 'F';
int target_servo_pos = 97;
void setup() 
{
  Serial.begin(BOUDRATE);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  attachServo();
  //attachEncoderInterrupt();
}

void loop() 
{
  getInputValues();
  setServoPos(target_servo_pos);
  setMotorDirection(target_direction);
  //setMotorSpeed(target_speed);
  analogWrite(enA, target_speed);
  printVariables();
}

void printVariables()
{
  Serial.print("TargetSpeed:");
  Serial.print(target_speed);
  Serial.print(",");
  Serial.print("Direction:");
  Serial.print(target_direction == 'F' ? "Forward" : "Backwards");
  Serial.print(",");
  Serial.print("TargetServoPos:");
  Serial.println(target_servo_pos);
}

void getInputValues()
{
  if(Serial.available()>0)
  {
    char cCo=Serial.read();
    if(cCo == 'V')
    {
      target_speed = Serial.parseInt();
      if(target_speed == 0)
      {
        resetPI();
      }
    }
    if(cCo == 'D')
    {
      target_direction = Serial.read();
    }
    else if(cCo == 'R')
    {
      resetPI();
    }
    else if(cCo == 'S')
    {
      target_servo_pos = Serial.parseInt();
    }
  }
}

Servo servo;  
int goal_pos = 97; 
int actual_pos = 97;
int inc = 5;

void attachServo()
{
  servo.attach(SERVO);
  servo.write(goal_pos);
}

void setServoPos(int position)
{
  goal_pos = position;
  if(actual_pos == goal_pos)
  {
    return;
  }
  if(abs(actual_pos-goal_pos)<inc)
  {
    actual_pos = goal_pos;
  }
  else if(actual_pos < goal_pos)
  {
    actual_pos+=inc;
  }
  else if(actual_pos > goal_pos)
  {
    actual_pos-=inc;
  }
  servo.write(actual_pos);
}


