#include "ST7735Display.h"

ST7735Display::ST7735Display(Adafruit_ST7735& tftInstance) : tft(tftInstance) {}

void ST7735Display::init() {
    
}

void ST7735Display::clearBuffer() {
    tft.fillScreen(ST7735_BLACK);  // Clear the screen
}

void ST7735Display::setPowerSave(uint32_t is_enabled) {
    tft.enableSleep(is_enabled);
}

void ST7735Display::setBitmapMode(uint32_t is_transparent) {
    // Implement bitmap mode using tft, if applicable
}

void ST7735Display::drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
    tft.drawBitmap(x, y, bitmap, w, h, ST7735_WHITE);  // Draw bitmap
}

void ST7735Display::setFont(const uint8_t *font) {
    //tft.setFont(font);  // Set the font
}

void ST7735Display::setCursor(int16_t x, int16_t y) {
    tft.setCursor(x, y);  // Set the cursor position
}

void ST7735Display::print(float data, int digits) {
    tft.print(data, digits);  // Print float data
}

void ST7735Display::print(char c) {
    tft.print(c);  // Print a character
}

void ST7735Display::print(const char* c) {
    tft.print(c);  // Print a string
}

void ST7735Display::println(const String &s) {
    tft.println(s);  // Print a string followed by a newline
}

void ST7735Display::drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) {
    // Implement drawing a glyph using tft, if applicable
}

void ST7735Display::sendBuffer() {
    // No need to send a buffer for this library
}

int ST7735Display::getUTF8Width(const char *s) {
    // Implement getting the width of a UTF-8 string using tft, if applicable
}

int ST7735Display::getWidth() {
    return 240;
}

int ST7735Display::getHeight() {
    return 240;
}