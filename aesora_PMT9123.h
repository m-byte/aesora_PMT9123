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

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define PMT9123_ADDRESS			(0x00)    // don't know this yet
/*=========================================================================*/

/*=========================================================================
    PRODUCT ID
    -----------------------------------------------------------------------*/
    #define PMT9123_PRODUCT_ID			(0x41)
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    #define PMT9123_REGISTER_PRODUCT_ID		(0x00)
    #define PMT9123_REGISTER_REVISION_ID	(0x01)
    #define PMT9123_REGISTER_MOTION		(0x02)
    #define PMT9123_REGISTER_DELTA_X_LSB	(0x03)
    #define PMT9123_REGISTER_DELTA_Y_LSB	(0x04)
    #define PMT9123_REGISTER_DELTA_XY_MSB	(0x05)
    #define PMT9123_REGISTER_SQUAL		(0x06)
    #define PMT9123_REGISTER_SHUTTER_UPPER	(0x07)
    #define PMT9123_REGISTER_SHUTTER_LOWER	(0x08)
    #define PMT9123_REGISTER_PIXEL_MAX		(0x09)
    #define PMT9123_REGISTER_PIXEL_AVG		(0x0A)
    #define PMT9123_REGISTER_PIXEL_MIN		(0x0B)
    #define PMT9123_REGISTER_PERFORMANCE	(0x11)
    #define PMT9123_REGISTER_RUN_DOWNSHIFT	(0x14)
    #define PMT9123_REGISTER_REST1_RATE		(0x15)
    #define PMT9123_REGISTER_REST1_DOWNSHIFT	(0x16)
    #define PMT9123_REGISTER_REST2_RATE		(0x17)
    #define PMT9123_REGISTER_REST2_DOWNSHIFT	(0x18)
    #define PMT9123_REGISTER_REST3_RATE		(0x19)
    #define PMT9123_REGISTER_REST3_DOWNSHIFT	(0x1A) // not documented.. does this exist?
    #define PMT9123_REGISTER_OBSERVATION	(0x1D)
    #define PMT9123_REGISTER_FRAME_CAPTURE1	(0x24)
    #define PMT9123_REGISTER_FRAME_CAPTURE2	(0x25)
    #define PMT9123_REGISTER_POWER_UP_RESET	(0x3A)
    #define PMT9123_REGISTER_SHUTDOWN		(0x3B)
    #define PMT9123_REGISTER_ENABLE_REGWRITE	(0x41)
    #define PMT9123_REGISTER_RESOLUTION_STEP	(0x48)
    #define PMT9123_REGISTER_ORIENTATION	(0x4D)
/*=========================================================================*/

class aesora_PMT9123{
 public:
  aesora_PMT9123();
  void begin(void);
  bool checkID(void);
  uint8_t getResolution(void);
  void setResolution(uint8_t);
  uint16_t getDeltaX(void);
  uint16_t getDeltaY(void);
  void getDelta(uint16_t *X, uint16_t *Y);

 private:
  uint8_t _resolution;
};
