/*
 * @Author: your name
 * @Date: 2021-09-18 21:18:59
 * @LastEditTime: 2021-10-11 18:06:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \receiveClient_v8\.pio\libdeps\esp32doit-devkit-v1\TFT_eSPI\User_Setups\Setup7_ST7735_128x128.h
 */
// See SetupX_Template.h for all options available

#define ST7735_DRIVER

// #include <../../../../S-Clock/include/globalConfig.h>
#include "../../../include/globalConfig.h"

// #define INITR_GREENTAB128 // For 128 x 128 display

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts


#define SMOOTH_FONT


// #define SPI_FREQUENCY  20000000
#define SPI_FREQUENCY  27000000

// #define SPI_TOUCH_FREQUENCY  2500000


// #define SUPPORT_TRANSACTIONS
