/******************************************************************************
* File Name          : Me_LegoMotor.h
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

#include <Arduino.h>
#include <Me_BaseShield.h>
#include <Me_I2cMaster.h>


#ifndef Me_LegoMotor_h
#define Me_LegoMotor_h
	
#define LEGO_MOTOR_BRIDGE_ADDR_1 0x04	
#define LEGO_MOTOR_BRIDGE_ADDR_2 0x08

class Me_LegoMotor
{
public:
	Me_LegoMotor();
	//portNum can only be 1 & 2
	Me_LegoMotor(int portNum);
	void begin();
	void sendMotor1(unsigned char sendData);
	void sendMotor2(unsigned char sendData);
private:
	int port;
	Me_SoftI2cMaster softI2cMaster;
};
#endif

