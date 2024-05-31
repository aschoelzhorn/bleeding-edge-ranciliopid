/**
 * @file pinmapping.h
 *
 * @brief Default GPIO pin mapping
 *
 */

#pragma once

/**
 * Input Pins
 */

// Switches/Buttons
#define PIN_POWERSWITCH 39
#define PIN_BREWSWITCH  34
#define PIN_STEAMSWITCH 35
#define PIN_WATERSWITCH 36

#define PIN_ROTARY_DT  4 // Rotary encoder data pin
#define PIN_ROTARY_CLK 3 // Rotary encoder clock pin
#define PIN_ROTARY_SW  5 // Rotary encoder switch

// Sensors
#define PIN_TEMPSENSOR  16
#define PIN_WATERSENSOR 23
#define PIN_HXDAT       32 // Brew scale data pin 1
#define PIN_HXDAT2      25 // Brew scale data pin 2
#define PIN_HXCLK       33 // Brew scale clock pin

/**
 * Output pins
 */

// Relays
#define PIN_VALVE  17
#define PIN_PUMP   27
#define PIN_HEATER 2

// LEDs
#define PIN_STATUSLED 26
#define PIN_BREWLED   19
#define PIN_STEAMLED  1

// Periphery
#define PIN_ZC 18 // Dimmer circuit Zero Crossing

/**
 * Bidirectional Pins
 */
#define PIN_I2CSCL 21
#define PIN_I2CSDA 22

/**
 * TFT Display, needs FEATURE_SCALE 0
 * for GMT130 ST7789 240x240 use
 */
#define PIN_TFT_MOSI 33 // PIN_HXCLK
#define PIN_TFT_SCLK 25 // PIN_HXDAT2
#define PIN_TFT_CS   -1 // -1 not connected
#define PIN_TFT_DC   32 // PIN_HXDAT
#define PIN_TFT_RST  4  // PIN_ROTARY_DT, should be 15

/**
 * These settings work with GMT020-02 Ver1.1 320*240 (ST7789)
* #define PIN_TFT_MOSI 33
* #define PIN_TFT_SCLK 25
* #define PIN_TFT_CS   14
* #define PIN_TFT_DC   32
* #define PIN_TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST
*/
