/*************************************************************************
* File Name          : TestSlaveBluetoothBySoftSerial.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 12/12/2012
* Description        : Example for Makeblock Electronic modules of Me -  
                       Bluetooth. The module can only be connected to the 
                       port 3, 4, 5, 6, 7 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <SoftwareSerial.h>
#include <Me_Bluetooth.h>

/*
Blue module can only be connected to port 3, 4, 5, 6, 7 of base shield.
When connected to port 5, Serial.print function can not be used, and 
the code can be uploaded to the Arduino only when there's no module
connected to port 5 physicaly.
*/
Me_Bluetooth bluetooth(3);

void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);
    Serial.println("Bluetooth Start!");
}

void loop()
{
    char inDat;
    char outDat;
    if(bluetooth.available())
    {
        inDat = bluetooth.read();
        Serial.print(inDat);
    }
    if(Serial.available())
    {
        outDat = Serial.read();
        bluetooth.write(outDat);
    }
}

