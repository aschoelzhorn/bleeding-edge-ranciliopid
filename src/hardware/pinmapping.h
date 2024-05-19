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
#define PIN_TEMPSENSOR  32
#define PIN_WATERSENSOR 23 // 23 used by display

#define PIN_HXDAT       16 // Brew scale data pin 1
#define PIN_HXDAT2      25 // Brew scale data pin 2
#define PIN_HXCLK       33 // Brew scale clock pin // 33 used by display

/**
 * Output pins
 */

// Relays
#define PIN_VALVE  17
#define PIN_PUMP   27 // 27 used by display
#define PIN_HEATER 13

// LEDs
#define PIN_STATUSLED 26
#define PIN_BREWLED   19
#define PIN_STEAMLED  1

// Periphery
#define PIN_ZC 18 // Dimmer circuit Zero Crossing  // 18 used by display

/**
 * Bidirectional Pins
 */
#define PIN_I2CSCL 22
#define PIN_I2CSDA 21
