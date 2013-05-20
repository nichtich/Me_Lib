/*************************************************************************
* File Name          : TestBaseShieldMotorDriver.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Makeblock Electronic modules of Base Shield. Pin 4, 
                       5, 6, and 7 are used by the onboard motor driver 
                       chip.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <Me_BaseShieldMotorDriver.h>
Me_BaseShieldMotorDriver baseShieldMotorDriver;

void setup()
{
    baseShieldMotorDriver.begin();
}

void loop()
{
    baseShieldMotorDriver.runMotor1(254);
    delay(1000);
    baseShieldMotorDriver.runMotor1(-254);
    delay(1000);
    baseShieldMotorDriver.stopMotor1();
    	
    baseShieldMotorDriver.runMotor2(254);
    delay(1000);
    baseShieldMotorDriver.runMotor2(-254);
    delay(1000);
    baseShieldMotorDriver.stopMotor2();
     
    baseShieldMotorDriver.runMotors(254,254);
    delay(1000);
    baseShieldMotorDriver.runMotors(-254,-254);
    delay(1000);
    
    baseShieldMotorDriver.stopMotors();
    delay(500);
}
