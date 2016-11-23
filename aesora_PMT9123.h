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
    #define PMT9123_REGISTER_R_PRODUCT_ID		(0x00)
    #define PMT9123_REGISTER_R_REVISION_ID	(0x01)
    #define PMT9123_REGISTER_R_MOTION		(0x02)
    #define PMT9123_REGISTER_W_MOTION		(0x02)
    #define PMT9123_REGISTER_R_DELTA_X_LSB	(0x03)
    #define PMT9123_REGISTER_R_DELTA_Y_LSB	(0x04)
    #define PMT9123_REGISTER_R_DELTA_XY_MSB	(0x05)
    #define PMT9123_REGISTER_R_SQUAL		(0x06)
    #define PMT9123_REGISTER_R_SHUTTER_MSB	(0x07)
    #define PMT9123_REGISTER_R_SHUTTER_LSB	(0x08)
    #define PMT9123_REGISTER_R_PIXEL_MAX		(0x09)
    #define PMT9123_REGISTER_R_PIXEL_AVG		(0x0A)
    #define PMT9123_REGISTER_R_PIXEL_MIN		(0x0B)
    #define PMT9123_REGISTER_R_PERFORMANCE	(0x11)
    #define PMT9123_REGISTER_W_PERFORMANCE	(0x11)
    #define PMT9123_REGISTER_R_RUN_DOWNSHIFT	(0x14)
    #define PMT9123_REGISTER_W_RUN_DOWNSHIFT	(0x14)
    #define PMT9123_REGISTER_R_REST1_RATE		(0x15)
    #define PMT9123_REGISTER_W_REST1_RATE		(0x15)
    #define PMT9123_REGISTER_R_REST1_DOWNSHIFT	(0x16)
    #define PMT9123_REGISTER_W_REST1_DOWNSHIFT	(0x16)
    #define PMT9123_REGISTER_R_REST2_RATE		(0x17)
    #define PMT9123_REGISTER_W_REST2_RATE		(0x17)
    #define PMT9123_REGISTER_R_REST2_DOWNSHIFT	(0x18)
    #define PMT9123_REGISTER_W_REST2_DOWNSHIFT	(0x18)
    #define PMT9123_REGISTER_R_REST3_RATE		(0x19)
    #define PMT9123_REGISTER_W_REST3_RATE		(0x19)
    #define PMT9123_REGISTER_R_OBSERVATION	(0x1D)
    #define PMT9123_REGISTER_W_OBSERVATION	(0x1D)
    #define PMT9123_REGISTER_R_FRAME_CAPTURE1	(0x24)
    #define PMT9123_REGISTER_W_FRAME_CAPTURE1	(0x24)
    #define PMT9123_REGISTER_R_FRAME_CAPTURE2	(0x25)
    #define PMT9123_REGISTER_W_FRAME_CAPTURE2	(0x25)
    #define PMT9123_REGISTER_W_POWER_UP_RESET	(0x3A)
    #define PMT9123_REGISTER_W_SHUTDOWN		(0x3B)
    #define PMT9123_REGISTER_W_ENABLE_REGWRITE	(0x41)
    #define PMT9123_REGISTER_R_RESOLUTION_STEP	(0x48)
    #define PMT9123_REGISTER_W_RESOLUTION_STEP	(0x48)
    #define PMT9123_REGISTER_R_ORIENTATION	(0x4D)
    #define PMT9123_REGISTER_W_ORIENTATION	(0x4D)
/*=========================================================================*/

class aesora_PMT9123{
 public:
  aesora_PMT9123();
  void begin(void);
  bool checkID(void);
  uint8_t getResolution(void);
  void setResolution(uint8_t);
  int16_t getDeltaX(void);
  int16_t getDeltaY(void);
  void getDelta(int16_t *X, int16_t *Y);
  uint8_t getSQual(void);
  uint16_t getShutter(void);
  uint8_t getPixelMax(void);
  uint8_t getPixelAvg(void);
  uint8_t getPixelMin(void);
  

 private:
  uint8_t _resolution;
};
