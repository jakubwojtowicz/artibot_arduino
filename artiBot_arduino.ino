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
  <Max m/s> 0.7 </Max m/s> 
  <Min m/s> 0.15 </Min m/s>
  <Encoder resolution> 374 </Encoder resolution>
</Motor info>
<Servo info>
  <Max left> -70 </Max left> 
  <Min right> 70 </Min right>
</Servo info>
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
uint8_t target_servo_pos = 110;

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
  getInputValuesFromROS();
  if(target_speed == 0)
  {
    motorController.stop();
    motorRegulator.reset();
  }
  else
  {
    motorController.setDirection(target_speed > 0 ? 'F':'B');
    measured_speed = encoder.measureSpeed();
    int pwm = motorRegulator.calculate(encoder.metersPerSecondToRpm(abs(target_speed)), measured_speed);
    motorController.setSpeed(pwm);
  }
  servo.write(target_servo_pos);
}

void getInputValuesFromROS()
{
  // Check if data is available on serial
  if (Serial.available() > 0) {
    // Read the incoming data
    String command = Serial.readStringUntil('\n');  // Read until newline
    int mIndex = command.indexOf('M');
    int aIndex = command.indexOf('A');

    if (mIndex != -1 && aIndex != -1) {
      // Split the command into servo position and motor speed
      String motorStr = command.substring(mIndex + 1, aIndex);
      String servoStr = command.substring(aIndex + 1);

      motorStr.trim();
      servoStr.trim();

      // Convert the strings to integers
      target_servo_pos = servoStr.toInt() + 110;
      target_speed = motorStr.toFloat();
    }
  }
}


void getInputValues()
{
  if(Serial.available()>0)
  {
    char cCo=Serial.read();
    if(cCo == 'V')
    {
      target_speed = Serial.parseFloat();
    }
    else if(cCo == 'S')
    {
      target_servo_pos = Serial.parseInt() + 110;
    }
  }
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



