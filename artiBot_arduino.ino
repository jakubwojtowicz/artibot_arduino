/*
<Info>
  <Title> ArtiBot motor speed measurement and regulation. </Title> 
  <Author> Jakub Wójtowicz </Author>
  <Creation Date> 05.12.2023 </Creation Date>
  <Last update> 24.11.2024 </Last update>
</Info>
<Motor info>
  <Max rpm> 220 </Max rpm> 
  <Min rpm> 30 </Min rpm>
  <Encoder resolution> 374 </Encoder resolution>
</Motor info>
*/
#include <Servo.h>
#include "motor_control.h"
#include "encoder.h"
#include "PI.h"

#define enA 5
#define in1 6
#define in2 7
#define ENC 3
#define SERVO 11
#define BOUDRATE 9600 

float target_speed = 0.0;
float measured_speed = 0.0;
float measured_speed_ms = 0.0;
int plot_const_l = 0;
int plot_const_h = 1;
int pwm = 0;
uint8_t target_servo_pos = 90;

Servo servo;  
Encoder encoder(66);
PIRegulator motorRegulator(0.2,0.15);
MotorController motorController(in1, in2, enA);

void setup() 
{
  Serial.begin(BOUDRATE);
  servo.attach(SERVO);
  encoder.attachInterruptHandler(ENC);
}

void loop() 
{
  getInputValues();
  servo.write(target_servo_pos);
  motorController.setDirection(target_speed>0 ? 'F':'B');
  measured_speed = encoder.measureSpeed();
  pwm = motorRegulator.calculate(encoder.metersPerSecondToRpm(abs(target_speed)), measured_speed);
  motorController.setSpeed(pwm);

  plot();
}

void plot()
{
  measured_speed_ms = encoder.rpmToMetersPerSecond(measured_speed);
  Serial.print(plot_const_l);
  Serial.print(",");
  Serial.print(target_speed);
  Serial.print(",");
  Serial.print(measured_speed_ms);
  Serial.print(",");
  Serial.println(plot_const_h);
}

void getInputValues()
{
  if(Serial.available()>0)
  {
    char cCo=Serial.read();
    if(cCo == 'V')
    {
      target_speed = Serial.parseFloat();
      if(target_speed == 0)
      {
        motorRegulator.reset();
      }
    }
    else if(cCo == 'S')
    {
      target_servo_pos = Serial.parseInt();
    }
  }
}


