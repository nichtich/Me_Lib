/******************************************************************************
* File Name          : Me_ServoDriver.cpp
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
* Description        : Class for Makeblock Electronic modules of Me-Servo 
                       Driver. The module can only be connected to the port 1, 
                       2 of Me - Base Shield. One module can drive two servos.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************/

#include "Me_ServoDriver.h"

Me_ServoDriver::Me_ServoDriver()
{
	servo1Pin = mePort[PORT_1].innersidePin;
	servo2Pin = mePort[PORT_1].outsidePin;
	initialPos1 = 90;
	initialPos2 = 90;
}

Me_ServoDriver::Me_ServoDriver(int portNum)
{
	if(portNum > 0 && portNum < 3)
	{
		servo1Pin = mePort[portNum].innersidePin;
		servo2Pin = mePort[portNum].outsidePin;
	}
	initialPos1 = 90;
	initialPos2 = 90;
}

void Me_ServoDriver::Servos_begin()
{
	Me_BaseShield::begin();
	servo1.attach(servo1Pin);
	servo2.attach(servo2Pin);
	writeServo1(initialPos1);
	writeServo2(initialPos2);
}

void Me_ServoDriver::Servo1_begin()
{
	Me_BaseShield::begin();
	servo1.attach(servo1Pin);
	pinMode(servo2Pin,OUTPUT);
}

void Me_ServoDriver::Servo2_begin()
{
	Me_BaseShield::begin();
	servo2.attach(servo2Pin);
	pinMode(servo1Pin,OUTPUT);
}

void Me_ServoDriver::detachServo1()
{
	servo1.detach();
}

void Me_ServoDriver::detachServo2()
{
	servo2.detach();
}

void Me_ServoDriver::detachAll()
{
	servo1.detach();
	servo2.detach();
}

void Me_ServoDriver::writeServo1(int value)
{
	servo1.write(value);
}

void Me_ServoDriver::writeServo2(int value)
{
	servo2.write(value);
}

void Me_ServoDriver::writeServo1Microseconds(int value)
{
	servo1.writeMicroseconds(value);
}

void Me_ServoDriver::writeServo2Microseconds(int value)
{
	servo2.writeMicroseconds(value);
}

int Me_ServoDriver::readServo1()
{
	return servo1.read();
}

int Me_ServoDriver::readServo2()
{
	return servo2.read();
}

int Me_ServoDriver::readServo1Microseconds()
{
	return servo1.readMicroseconds();
}

int Me_ServoDriver::readServo2Microseconds()
{
	return servo2.readMicroseconds();
}

bool Me_ServoDriver::servo1Attached()
{
	return servo1.attached();
}

bool Me_ServoDriver::servo2Attached()
{
	return servo2.attached();
}

