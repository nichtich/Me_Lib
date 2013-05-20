/*************************************************************************
* File Name          : LineFinderRobot.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 3/26/2013
* Description        : Example for Starter Kit. Use the motor driver on base shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <Me_BaseShieldMotorDriver.h>
#include <Me_LineFinder.h>

Me_BaseShieldMotorDriver baseShieldMotorDriver;// use M1 and M2 ports on BaseShield
Me_LineFinder lineFinder(PORT_5); //Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield.

void setup()
{         
    // initialize serial communication with computer:
    Serial.begin(9600);
    // initialize BaseShield Motor Driver:
    baseShieldMotorDriver.begin();
}

void loop()
{
    int sensorState = lineFinder.readSensors();
    // Sensor 1 and sensor 2 all in the black line.
    if(sensorState == S1_IN_S2_IN)
    {
        Serial.println("Forward.");
        baseShieldMotorDriver.runMotors(64,-64);
    }
    // Sensor 1 in the black line and sensor 2 outside the black line.
    if(sensorState == S1_IN_S2_OUT)
    {
        Serial.println("Turn left.");
        baseShieldMotorDriver.runMotor1(-32);
    }
    // Sensor 1 outside the black line and sensor 2 in the black line.
    if(sensorState == S1_OUT_S2_IN)
    {
        Serial.println("Turn right.");
        baseShieldMotorDriver.runMotor2(32);
    }
    // Two sensors all outside the black line.
    if(sensorState == S1_OUT_S2_OUT)
    {
        Serial.println("Stop.");
        baseShieldMotorDriver.stopMotors();
    }
}
