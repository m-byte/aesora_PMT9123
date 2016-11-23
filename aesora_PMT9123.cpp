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
  i2cwrite((uint8_t)PMT9123_REGISTER_R_PRODUCT_ID);
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
  i2cwrite((uint8_t)PMT9123_REGISTER_R_RESOLUTION_STEP);
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
  i2cwrite((uint8_t)PMT9123_REGISTER_W_RESOLUTION_STEP);
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
void aesora_PMT9123::getDelta(int16_t *x, int16_t *y, uint8_t *mot) {
  uint8_t _x, _y, temp;

  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_R_MOTION);
  wire.endTransmission();

  // Read delta
  Wire.requestFrom(PMT9123_ADDRESS, 4);
  mot = i2cread();
  _x = i2cread();
  _y = i2cread();
  temp = i2cread();

  // Calculate
  x = _x | ((uint16_t)(temp & 0xF0) << 4) | (temp & 0x80) > 0 ? 0xF000 : 0;
  y = _y | ((uint16_t)(temp & 0x0F) << 8) | (temp & 0x08) > 0 ? 0xF000 : 0;
}

/**************************************************************************/
/*!
    @brief Gets delta in x
*/
/**************************************************************************/
int16_t aesora_PMT9123::getDeltaX(void) {
  int16_t x, y;
  uint8_t mot;

  getDelta(&x, &y, &mot);
  return x;
}

/**************************************************************************/
/*!
    @brief Gets delta in y
*/
/**************************************************************************/
int16_t aesora_PMT9123::getDeltaY(void) {
  int16_t x, y;
  uint8_t mot;

  getDelta(&x, &y, &mot);
  return y;
}

/**************************************************************************/
/*!
    @brief Gets surface quality
*/
/**************************************************************************/
uint8_t aesora_PMT9123::getSQual(void) {
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_R_SQUAL);
  wire.endTransmission();

  // Read squal
  Wire.requestFrom(PMT9123_ADDRESS, 1);
  return i2cread();
}

/**************************************************************************/
/*!
    @brief Gets shutter time in clock cycles
*/
/**************************************************************************/
uint16_t aesora_PMT9123::getShutter(void) {
  uint16_t ret = 0;
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_R_SHUTTER_MSB);
  wire.endTransmission();

  // Read shutter
  Wire.requestFrom(PMT9123_ADDRESS, 2);
  ret = i2cread();
  ret = ret << 8 | i2cread();
  return ret;
}

/**************************************************************************/
/*!
    @brief Gets maximum pixel value in frame
*/
/**************************************************************************/
uint8_t aesora_PMT9123::getPixelMax(void) {
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_R_PIXEL_MAX);
  wire.endTransmission();

  // Read max pixel
  Wire.requestFrom(PMT9123_ADDRESS, 1);
  return i2cread();
}

/**************************************************************************/
/*!
    @brief Gets average pixel value in frame
*/
/**************************************************************************/
uint8_t aesora_PMT9123::getPixelAvg(void) {
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_R_PIXEL_AVG);
  wire.endTransmission();

  // Read avg pixel
  Wire.requestFrom(PMT9123_ADDRESS, 1);
  return i2cread();
}

/**************************************************************************/
/*!
    @brief Gets minimum pixel value in frame
*/
/**************************************************************************/
uint8_t aesora_PMT9123::getPixelMin(void) {
  // Select register
  Wire.beginTransmission(PMT9123_ADDRESS);
  i2cwrite((uint8_t)PMT9123_REGISTER_R_PIXEL_MIN);
  wire.endTransmission();

  // Read min pixel
  Wire.requestFrom(PMT9123_ADDRESS, 1);
  return i2cread();
}
