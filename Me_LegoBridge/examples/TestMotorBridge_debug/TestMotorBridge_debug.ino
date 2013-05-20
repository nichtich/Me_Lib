/*************************************************************************
* File Name          : TestMotorBridge_debug.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me - Lego 
                       Digital Bridge. The module is used to connect the 
                       NXT Lego Motor Driver to Arduino. The module can 
                       only be connected to the port 1, 2 of Me - Base 
                       Shield. One module can drive two Lego Motor.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include <Me_BaseShield.h>
#include <Me_I2cMaster.h>
#include <Me_LegoMotor.h>

// An instance of class for software master, using software I2C.
Me_LegoMotor legoMotor(PORT_1);

void setup(void)
{
    legoMotor.begin();
}
void loop(void)
{
    legoMotor.sendMotor2(0x31);
    delay(100);
    legoMotor.sendMotor2(0x32);
    delay(100);
}
