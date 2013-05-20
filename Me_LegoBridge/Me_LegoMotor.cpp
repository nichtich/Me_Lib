/******************************************************************************
* File Name          : Me_LegoMotor.cpp
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me -  Lego 
                       Digital Bridge. The module is used to connect the NXT 
                       Lego Motor Driver to Arduino. The module can only be 
                       connected to the port 1, 2 of Me - Base Shield. One 
                       module can drive two Lego Motor.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_LegoMotor.h"

//default port is PORT_1
Me_LegoMotor::Me_LegoMotor():softI2cMaster(mePort[PORT_1].innersidePin, mePort[PORT_1].outsidePin)
{
	port = PORT_1;
}

Me_LegoMotor::Me_LegoMotor(int portNum):softI2cMaster(mePort[portNum].innersidePin, mePort[portNum].outsidePin)
{
	port = portNum;
}

void Me_LegoMotor::begin()
{
	Me_BaseShield::begin();
	pinMode(mePort[port].innersidePin, OUTPUT);
	pinMode(mePort[port].outsidePin, OUTPUT);
	digitalWrite(mePort[port].innersidePin, HIGH);
	digitalWrite(mePort[port].outsidePin, HIGH);
}

void Me_LegoMotor::sendMotor1(unsigned char sendData)
{
	  // issue a start condition, send device address
  softI2cMaster.start(LEGO_MOTOR_BRIDGE_ADDR_1);

    // send the data
  softI2cMaster.write(sendData);
  
  	// issue a stop condition
  softI2cMaster.stop();

}

void Me_LegoMotor::sendMotor2(unsigned char sendData)
{
	  // issue a start condition, send device address
  softI2cMaster.start(LEGO_MOTOR_BRIDGE_ADDR_2);

    // send the data
  softI2cMaster.write(sendData);
  
  	// issue a stop condition
  softI2cMaster.stop();
}