/******************************************************************************
* File Name          : Me_InfraredReceiver.cpp
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/17/2013
* Description        : Class for Makeblock Electronic modules of Me-Infrared 
                       Receiver. Me-Infrared Receiver can ONLY be connected to 
                       PORT_4 when use this lib.
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************
* This is distributed under the the GNU General Public License.
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*******************************************************************************/

#include "Me_InfraredReceiver.h"
#include "IRMapping.h"
#include <Me_BaseShield.h>

volatile int idx;
volatile unsigned long pulseEnd[BUFFERSIZE];
unsigned char bits[BUFFERSIZE];
extern void inline pulseFalling();

Me_InfraredReceiver::Me_InfraredReceiver() {}

void Me_InfraredReceiver::begin()
{
     Me_BaseShield::begin();
     attachInterrupt(0, pulseFalling,FALLING);
}

/*!
Wait for a keypress from the IR remote, and return the integer mapping of that key\n
Returns -1 if nothing available.  Returns raw command number if mapping is not recognized.
 */
int16_t Me_InfraredReceiver::read()
{
    int i, count, numBits;
    delay(50);

    /*if (idx > 1 ){
    DBG("Bits rcvd=");
    DBGLN(idx);
    }*/

    noInterrupts();  //  CRITICAL SECTION >>>>>>>>>>
    numBits = idx;

    // Wait for Interrupt routine to collect pulses
    if (numBits < IR_NUM_BITS){
        interrupts();  //  NON CRITICAL SECTION <<<<<<<<<
        //return(errorCode=ERROR_NO_DATA);  // No data available
        return -1;
    }

    if (numBits > IR_NUM_BITS+1){
        numBits = IR_NUM_BITS+1;
    }

    // Calc length of pulses and store in pulseMsec[]
    for (i=0;i<=numBits;i++)
    {
        {
           // if (pulseEnd[i+1] - pulseEnd[i] < START_PULSE_MSEC)  // Ignore pulse if too long
                pulseMsec[i] = pulseEnd[i+1] - pulseEnd[i];
        }
    }

    idx=0;  // Set ISR buffer to get next command

    interrupts();  //  NON CRITICAL SECTION <<<<<<<<<

    pulse_to_bits(bits, numBits);     // Convert the pulses to bits - long pulse=1, short=0
    count = verifyRemote(bits);       // Make sure it was a valid msg
    rawCode =  bits_to_int(bits, count);  // Return the key pressed
    //Serial.print("Raw Val=")
    //Serial.println(rawCode);

    return(decode(rawCode));
}


/*
  IR pulses encode binary "0" as a short pulse, and binary "1"
 as a long pulse.  Given an array containing pulse lengths,
 convert this to an array containing binary values
 */

void Me_InfraredReceiver::pulse_to_bits(unsigned char bits[], int numBits)
{
    for(int i = 0; i < numBits; i++)
    {      
        if(pulseMsec[i] > BIT_1_MSEC  && pulseMsec[i] < BIT_1_MSEC_MAX) //is it a 1?
        {
            bits[i] = 1;
        }
        else if(pulseMsec[i] > BIT_0_MSEC && pulseMsec[i] < BIT_1_MSEC_MAX) //is it a 0?
        {
            bits[i] = 0;
        }
        // else data is invalid...
        else {
            bits[i] = 2;
            if (pulseMsec[i] > BIT_1_MSEC_MAX && pulseMsec[i]< START_PULSE_MSEC) Serial.println("Not NEC Protocol?]");
        //errorCode = ERROR_CHECKSUM;
        }
    }
}

/*
 Remote sends an ID code in the first 14 check bits - we currently don't verify it
 */

int Me_InfraredReceiver::verifyRemote(unsigned char bits[])
{
    int result = 0;
    int bitValue = 1;
    int zeroBitCount =0;

    //Convert bits to integer
    for(int i = 0 ; i < (FirstLastBit) ; i++)
    {
        if(bits[i] == 1)
        {
            result += bitValue;

            // Find location of first 1 bit
            if(zeroBitCount==0) {
                zeroBitCount=i;
            }
        }

        bitValue *= 2;  // Binary value doubles with each bit
    }

    // Currently doesnt verify ID, just skip it
    return(zeroBitCount);
}

/*
  convert an array of binary values to a single base-10 integer
 */

int Me_InfraredReceiver::bits_to_int(unsigned char bits[], int zeroBitCnt)
{
    int result = 0;
    int bitValue = 1;

    //Convert bits to integer
    for(int i = (IR_NUM_BITS-FirstLastBit+zeroBitCnt-8) ; i < IR_NUM_BITS+zeroBitCnt-8 ; i++)
    {
        if(bits[i] == 1)
            result += bitValue;

        bitValue *= 2;
    }

    return result;
}

// Interrupt Handler is called whenever there is a  falling signal on the pin
void inline pulseFalling()
{
    // Every transition,  record time so we can measure pulse length
    pulseEnd[idx++] =  micros();

    // Ignore Start pulses
    if (idx == 2 && (pulseEnd[idx-1] - pulseEnd[idx-2] > START_PULSE_MSEC) )
    {
        pulseEnd[idx-2] = pulseEnd[idx-1];
        idx--;  // Received a start pulse (first pulse longer than MSG_START, ignore
    }

    // Make sure we dont overrun buffer
    if (idx>BUFFERSIZE) idx = 0;
}

//! Decode specific remote-control keys - change IRMapping.h with values for your Remote
int Me_InfraredReceiver::decode(int key)
{
        switch (key)
    {
    case RAW_POWER_BUTTON:  // turns on/off power
        return(POWER_BUTTON);
        break;
    case RAW_UNKOWN_BUTTON:  // 
        return(UNKOWN_BUTTON);
        break;
    case RAW_MENU_BUTTON:  // 
        return(MENU_BUTTON);
        break;
    case RAW_TEST_BUTTON:  // 
        return(TEST_BUTTON);
        break;
    case RAW_PLUS_BUTTON:  // 
        return(PLUS_BUTTON);
        break;
    case RAW_RETURN_BUTTON:  // 
        return(RETURN_BUTTON);
        break;
    case RAW_PREVIOUS_BUTTON:  // 
        return(PREVIOUS_BUTTON);
        break;
    case RAW_PLAY_BUTTON:  // 
        return(PLAY_BUTTON);
        break;
    case RAW_NEXT_BUTTON:  // 
        return(NEXT_BUTTON);
        break;
    case RAW_MINUS_BUTTON:  // 
        return(MINUS_BUTTON);
        break;
    case RAW_CLR_BUTTON:  // 
        return(CLR_BUTTON);
        break;
    case RAW_0:  // 0
        return(0);
        break;
    case RAW_1:  // 1
        return(1);
        break;
    case RAW_2:  // 2
        return(2);
        break;
    case RAW_3:  // 3
        return(3);
        break;
    case RAW_4:  // 4
        return(4);
        break;
    case RAW_5:  // 5
        return(5);
        break;
    case RAW_6:  // 6
        return(6);
        break;
    case RAW_7:  // 7
        return(7);
        break;
    case RAW_8:  // 8
        return(8);
        break;
    case RAW_9:  // 9
        return(9);
        break;
    default:
        Serial.println("Unrecognized Code");
        return(key);  // return unrecognized raw key
        break;
    }
}
