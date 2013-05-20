/*************************************************************************
* File Name          : TestServoDriver.ino
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/17/2013
* Description        : Test for Makeblock Electronic modules of Me -Servo 
                       Driver. The module can only be connected to the 
                       port 1, 2 of Me - Base Shield. One module can drive 
                       two servos.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_ServoDriver.h>
#include <Me_BaseShield.h>
#include <Servo.h>

/*
Class Me_ServoDriver has most of the functions from class Servo, 
see Me_ServoDriver.h for more details.
*/
Me_ServoDriver servoDriver(PORT_1);//can ONLY be PORT_1,PORT_2

int posStart = 30;
int posEnd = 150;
void setup()
{
    servoDriver.Servos_begin();
}

void loop()
{
    servoDriver.writeServo1(posStart);
    servoDriver.writeServo2(posStart);
    delay(1000);
    servoDriver.writeServo1(posEnd);
    servoDriver.writeServo2(posEnd);
    delay(1000);
}
