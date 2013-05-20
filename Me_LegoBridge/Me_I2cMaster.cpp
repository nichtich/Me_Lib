/******************************************************************************
* File Name          : Me_I2cMaster.h
* Modified           : Steve
* Version            : V1.0.0
* Date               : 2/21/2013
* Description        : Extra clock is needed before restart condition.
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
*******************************************************************************
* Me_I2cMaster.cpp based on Arduino I2cMaster Library
* Copyright (C) 2010 by William Greiman
* 
* This file is part of the Arduino I2cMaster Library
*
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This Library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with the Arduino I2cMaster Library.  If not, see
* <http://www.gnu.org/licenses/>.
*******************************************************************************/

//==============================================================================
// WARNING don't change Me_SoftI2cMaster unless you verify the change with a scope
//------------------------------------------------------------------------------
/**
 * Initialize SCL/SDA pins and set the bus high.
 *
 * \param[in] sdaPin The software SDA pin number.
 *
 * \param[in] sclPin The software SCL pin number.
 */
Me_SoftI2cMaster::Me_SoftI2cMaster(uint8_t sdaPin, uint8_t sclPin) {
  sdaPin_ = sdaPin;
  //sdaPin_ = 18;
  pinMode(sdaPin_, OUTPUT);
  digitalWrite(sdaPin_, HIGH);
  sclPin_ = sclPin;
  //sclPin_ = 19;
  pinMode(sclPin_, OUTPUT);
  digitalWrite(sclPin_, HIGH);
}
//------------------------------------------------------------------------------
/** Read a byte and send Ack if more reads follow else Nak to terminate read.
 *
 * \param[in] last Set true to terminate the read else false.
 *
 * \return The byte read from the I2C bus.
 */
uint8_t Me_SoftI2cMaster::read(uint8_t last) {
  
  uint8_t b = 0;
  // make sure pull-up enabled
  digitalWrite(sdaPin_, HIGH);
  pinMode(sdaPin_, INPUT);
  // read byte
  for (uint8_t i = 0; i < 8; i++) {
    // don't change this loop unless you verify the change with a scope
    b <<= 1;
    delayMicroseconds(I2C_DELAY_USEC);
    digitalWrite(sclPin_, HIGH);
    if (digitalRead(sdaPin_)) b |= 1;
    digitalWrite(sclPin_, LOW);
  }
  // send Ack or Nak
  pinMode(sdaPin_, OUTPUT);
  digitalWrite(sdaPin_, last);
  digitalWrite(sclPin_, HIGH);
  delayMicroseconds(I2C_DELAY_USEC);
  digitalWrite(sclPin_, LOW);
  digitalWrite(sdaPin_, LOW);
  return b;
}
//------------------------------------------------------------------------------
/** Issue a restart condition.
 *
 * \param[in] addressRW I2C address with read/write bit.
 *
 * \return The value true, 1, for success or false, 0, for failure.
 */
bool Me_SoftI2cMaster::restart(uint8_t addressRW) {
  int e;
  delayMicroseconds(I2C_DELAY_USEC);
  stop();
  delayMicroseconds(I2C_DELAY_USEC);
  
  digitalWrite(sdaPin_, HIGH);
  
  digitalWrite(sclPin_, LOW);
  delayMicroseconds(I2C_DELAY_USEC);
  digitalWrite(sclPin_, HIGH);
  delayMicroseconds(I2C_DELAY_USEC);
  
  
  e = start(addressRW);
  return e;
}

//------------------------------------------------------------------------------
/** Issue a start condition.
 *
 * \param[in] addressRW I2C address with read/write bit.
 *
 * \return The value true, 1, for success or false, 0, for failure.
 */
bool Me_SoftI2cMaster::start(uint8_t addressRW) {
  digitalWrite(sdaPin_, LOW);
  delayMicroseconds(I2C_DELAY_USEC);
  digitalWrite(sclPin_, LOW);
  
  return write(addressRW);
}
//------------------------------------------------------------------------------
  /**  Issue a stop condition. */
void Me_SoftI2cMaster::stop(void) {
  digitalWrite(sdaPin_, LOW);
  delayMicroseconds(I2C_DELAY_USEC);
  digitalWrite(sclPin_, HIGH);
  delayMicroseconds(I2C_DELAY_USEC);
  digitalWrite(sdaPin_, HIGH);
  delayMicroseconds(I2C_DELAY_USEC);
}
//------------------------------------------------------------------------------
/**
 * Write a byte.
 *
 * \param[in] data The byte to send.
 *
 * \return The value true, 1, if the slave returned an Ack or false for Nak.
 */
bool Me_SoftI2cMaster::write(uint8_t data) {
  // write byte
  for (uint8_t m = 0X80; m != 0; m >>= 1) {
    // don't change this loop unless you verify the change with a scope
    digitalWrite(sdaPin_, m & data);
    digitalWrite(sclPin_, HIGH);
    delayMicroseconds(I2C_DELAY_USEC);
    digitalWrite(sclPin_, LOW);
  }
  // get Ack or Nak
  pinMode(sdaPin_, INPUT);
  // enable pullup
  digitalWrite(sdaPin_, HIGH);
  digitalWrite(sclPin_, HIGH);
  uint8_t rtn = digitalRead(sdaPin_);
  digitalWrite(sclPin_, LOW);
  pinMode(sdaPin_, OUTPUT);
  digitalWrite(sdaPin_, LOW);
  return rtn == 0;
}
