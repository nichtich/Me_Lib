/******************************************************************************
* File Name          : Me_InfraredReceiver.h
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.0
* Date               : 4/18/2013
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

#ifndef ME_INFRARED_RECEIVER_H
#define ME_INFRARED_RECEIVER_H

#include <arduino.h>

#define DBG(x) Serial.print(x);
#define DBGLN(x) Serial.println(x);

// NEC protocol parameters
#define BUFFERSIZE 40
#define IR_NUM_BITS 32     // number of bits sent by IR remote
#define FirstLastBit 15      // divide 32 bits into two 15 bit chunks for integer variables. Ignore center two bits. they are all the same.
#define BIT_1_MSEC 1600           // Binary 1 threshold (Microseconds)
#define BIT_1_MSEC_MAX 2500
#define BIT_0_MSEC 450            // Binary 0 threshold (Microseconds)
#define START_PULSE_MSEC 4000 // Start bit threshold (Microseconds)
#define VERIFY_REMOTE 16128  // verifies first bits are 11111100000000. Different remotes may have different start codes

// Code table
#define IR_POWER_BUTTON 100
#define IR_MENU_BUTTON 102
#define IR_TEST_BUTTON 103
#define IR_PLUS_BUTTON 104
#define IR_RETURN_BUTTON 105
#define IR_PREVIOUS_BUTTON 106
#define IR_PLAY_BUTTON 107
#define IR_NEXT_BUTTON 108
#define IR_MINUS_BUTTON 109
#define IR_CLR_BUTTON 110
#define IR_BUTTON_0 0
#define IR_BUTTON_1 1
#define IR_BUTTON_2 2
#define IR_BUTTON_3 3
#define IR_BUTTON_4 4
#define IR_BUTTON_5 5
#define IR_BUTTON_6 6
#define IR_BUTTON_7 7
#define IR_BUTTON_8 8
#define IR_BUTTON_9 9

/*!
Receive remote codes from an IR remote. Interrupt 0 driven\n
Supports NEC protocol remote controls (most are NEC protocol)\n
*/
class Me_InfraredReceiver
{
 public:
  Me_InfraredReceiver();
  int16_t read();
  void begin();
  uint16_t pulseMsec[IR_NUM_BITS+5];
  int rawCode;
  
 private:
   virtual int decode(int key);
   void pulse_to_bits(unsigned char bits[], int numBits);
   int verifyRemote(unsigned char bits[]);
   int bits_to_int(unsigned char bits[], int zeroBitCnt);
};

#endif // ME_INFRARED_RECEIVER_H