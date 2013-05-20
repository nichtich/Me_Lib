/*************************************************************************
* File Name          : TestInfaredReceiver.ino
* Author             : Evan
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/19/2013
* Description        : Example for Makeblock Electronic modules of Me - 
                       Infrared Receiver. The module can ONLY be connected 
                       to the port  4 of Me - Base Shield. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Me_BaseShield.h>
#include <Me_InfraredReceiver.h>

/*
Note: As the code need to use interrupt 0, it works only when the Me - 
Infrared Receiver module is connected to the port 4(PORT_4) of Me - 
Base Shield.
*/
Me_InfraredReceiver infraredReceiver; 
void setup()
{
    infraredReceiver.begin();
    Serial.begin(9600);
}

void loop()
{
    int key = infraredReceiver.read();
    if(key>=0)
    {
        switch (key)
        {
            case IR_POWER_BUTTON: Serial.println("POWER_BUTTON");break;
            case IR_MENU_BUTTON: Serial.println("MENU_BUTTON");break;
            case IR_TEST_BUTTON: Serial.println("TEST_BUTTON");break;
            case IR_PLUS_BUTTON: Serial.println("PLUS_BUTTON");break;
            case IR_RETURN_BUTTON: Serial.println("RETURN_BUTTON");break;
            case IR_PREVIOUS_BUTTON: Serial.println("PREVIOUS_BUTTON");break;
            case IR_PLAY_BUTTON: Serial.println("PLAY_BUTTON");break;
            case IR_NEXT_BUTTON: Serial.println("NEXT_BUTTON");break;
            case IR_MINUS_BUTTON: Serial.println("MINUS_BUTTON");break;
            case IR_CLR_BUTTON: Serial.println("CLR_BUTTON");break;
            case IR_BUTTON_0: Serial.println("BUTTON_0");break;
            case IR_BUTTON_1: Serial.println("BUTTON_1");break;
            case IR_BUTTON_2: Serial.println("BUTTON_2");break;
            case IR_BUTTON_3: Serial.println("BUTTON_3");break;
            case IR_BUTTON_4: Serial.println("BUTTON_4");break;
            case IR_BUTTON_5: Serial.println("BUTTON_5");break;
            case IR_BUTTON_6: Serial.println("BUTTON_6");break;
            case IR_BUTTON_7: Serial.println("BUTTON_7");break;
            case IR_BUTTON_8: Serial.println("BUTTON_8");break;
            case IR_BUTTON_9: Serial.println("BUTTON_9");break;
            default:break;
        }
    }
}

