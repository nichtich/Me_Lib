/*************************************************************************
* File Name          : UltrasonicRangerTank.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 3/26/2013
* Description        : Example for Advanced Kit. Use the motor driver on 
                       base shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include <Me_BaseShield.h>
#include <Me_UltrasonicSensor.h>
#include <Me_BaseShieldMotorDriver.h>

Me_BaseShieldMotorDriver baseShieldMotorDriver;// use M1 and M2 ports on BaseShield
Me_UltrasonicSensor ultraSensor(5); //Ultrasonic module can ONLY be connected to port 3, 4, 5, 6, 7, 8 of base shield.

int leftSpeed = 80;
int rightSpeed = 80;
boolean leftFlag,rightFlag;

void setup()
{
    // initialize BaseShield Motor Driver:
    baseShieldMotorDriver.begin();
    // initialize Ultrasonic Sensor:
    ultraSensor.begin();
    // initialize serial communication with computer:
    Serial.begin(9600);
    leftFlag=false;
    rightFlag=false;
}

void loop()
{
    int distance;
    distance = ultraSensor.distanceCm();
    if(distance>2 && distance <40) // turn
    {   
        if(!rightFlag && !leftFlag) // random turn
        {
            if(random(9)<5) leftFlag=true;
            else rightFlag=true;
        }
        if(leftFlag)
            baseShieldMotorDriver.runMotors(-leftSpeed,-rightSpeed);
        if(rightFlag)
            baseShieldMotorDriver.runMotors(leftSpeed,rightSpeed);
    } 
    else // Forward
    {
        leftFlag=false;
        rightFlag=false;
        baseShieldMotorDriver.runMotors(leftSpeed,-rightSpeed);
    }
    // Print the distance of Serial Port:
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(200); // the minimal measure interval is 200 milliseconds
}

