/*************************************************************************
* File Name          : RemoteControlDozer.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 3/26/2013
* Description        : Example for Advanced Kit. Use the motor driver on 
                       base shield. Arm motor use the Me-Motor Driver.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/

#include <Me_BaseShield.h>
#include <Me_MotorDriver.h>
#include <Me_InfraredReceiver.h>
#include <Me_BaseShieldMotorDriver.h>

Me_BaseShieldMotorDriver baseShieldMotorDriver;// use M1 and M2 ports on BaseShield
Me_MotorDriver motorDriver(PORT_1); 
Me_InfraredReceiver infraredReceiver;// use ME_PORT_4 in default

int leftSpeed = 64;
int rightSpeed = 64;
int armSpeed = 128;

void setup()
{
    // initialize serial communication with computer:
    Serial.begin(9600);
    // initialize BaseShield Motor Driver:
    baseShieldMotorDriver.begin();
    // initialize Motor Driver:
    motorDriver.begin();
    // initialize Infrared Receiver:
    infraredReceiver.begin();
    Serial.println("Start!");
}

void loop()
{
    int key = infraredReceiver.read();
    if(key>=0)
    {
        Serial.println(key);
        switch (key)
        {
            case IR_TEST_BUTTON:armUp();break;
            case IR_PLUS_BUTTON:runForward();break;
            case IR_RETURN_BUTTON:armDown();break;
            case IR_PREVIOUS_BUTTON:runLeft();break;
            case IR_PLAY_BUTTON:runStop();break;
            case IR_NEXT_BUTTON:runRight();break;
            case IR_MINUS_BUTTON:runBack();break;
            default:break;
        }
    }
}

void runForward()
{
    Serial.println("run forward");
    baseShieldMotorDriver.runMotors(leftSpeed,-rightSpeed);
}

void runLeft()
{
    Serial.println("run left");
    baseShieldMotorDriver.runMotors(-leftSpeed,-rightSpeed);
}
void runRight()
{
    Serial.println("run right");
    baseShieldMotorDriver.runMotors(leftSpeed,rightSpeed);
}
void runStop()
{
    Serial.println("run stop");
    baseShieldMotorDriver.stopMotors();
}

void runBack()
{
    Serial.println("run back");
    baseShieldMotorDriver.runMotors(-leftSpeed,rightSpeed);
}

void armUp()
{
    Serial.println("arm up");
    motorDriver.run(-armSpeed);
    delay(300);
    motorDriver.stop();
}

void armDown()
{
    Serial.println("arm down");
    motorDriver.run(armSpeed);
    delay(300);
    motorDriver.stop();
}
