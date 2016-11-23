/**************************************************************************/
/*!
    @file     aesora_PMT9123.h
    @author   Matthias Breithaupt (Aesora)
    @license  BSD (see license.txt)

    This is a library for the Aesora PMT9123 breakout board

    @section  HISTORY

    v0.1  - Pre-release
*/
/**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include "aesora_PMT9123.h"

static uint8_t i2cread(void) {
  uint8_t x;
  #if ARDUINO >= 100
  x = Wire.read();
  #else
  x = Wire.receive();
  #endif
  //Serial.print("0x"); Serial.println(x, HEX);
  return x;
}


static void i2cwrite(uint8_t x) {
  #if ARDUINO >= 100
  Wire.write((uint8_t)x);
  #else
  Wire.send(x);
  #endif
}

/**************************************************************************/
/*!
    @brief  Instantiates a new PMT9123 class
*/
/**************************************************************************/
aesora_PMT9123::aesora_PMT9123() {
  _resolution = 0;
}

/**************************************************************************/
/*!
    @brief  Sets the HW up (reads resolution value, etc.)
*/
/**************************************************************************/
void aesora_PMT9123::begin() {
  Wire.begin();

  // Read the resolution (this value is used to calculate real distances)
  getResolution();
}


/**************************************************************************/
/*!
    @brief  Checks for a valid product id
*/
/**************************************************************************/
bool aesora_PMT9123::checkID() {
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_PRODUCT_ID);
  wire.endTransmission();

  // Read product id and compare
  Wire.requestFrom(PMT9123_ADDRESS, 1);
  return i2cread() == PMT9123_PRODUCT_ID;
}

/**************************************************************************/
/*!
    @brief  Gets the resolution setting
*/
/**************************************************************************/
uint8_t aesora_PMT9123::getResolution() {
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_RESOLUTION_STEP);
  wire.endTransmission();

  // Read resolution
  Wire.requestFrom(PMT9123_ADDRESS, 1);
  _resolution = i2cread();
  return _resolution;
}

/**************************************************************************/
/*!
    @brief  Sets the resolution setting
*/
/**************************************************************************/
void aesora_PMT9123::setResolution(uint8_t value) {
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_RESOLUTION_STEP);
  i2cwrite(value);
  wire.endTransmission();

  // Store new setting
  _resolution = value;
}

/**************************************************************************/
/*!
    @brief  Gets the delta in x and y
*/
/**************************************************************************/
void aesora_PMT9123::getDelta(uint16_t *x, uint16_t *y) {
  uint8_t _x, _y, temp;

  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_DELTA_X_LSB);
  wire.endTransmission();

  // Read delta
  Wire.requestFrom(PMT9123_ADDRESS, 3);
  _x = i2cread();
  _y = i2cread();
  temp = i2cread();

  // Calculate
  x = _x | ((uint16_t)(temp & 0xF0) << 4)	// might also be the other way around
  y = _y | ((uint16_t)(temp & 0x0F) << 8)
}

/**************************************************************************/
/*!
    @brief Gets delta in x
*/
/**************************************************************************/
uint16_t aesora_PMT9123::getDeltaX(void) {
  uint16_t x, y;

  getDelta(&x, &y);
  return x;
}

/**************************************************************************/
/*!
    @brief Gets delta in y
*/
/**************************************************************************/
uint16_t aesora_PMT9123::getDeltaY(void) {
  uint16_t x, y;

  getDelta(&x, &y);
  return y;
}
