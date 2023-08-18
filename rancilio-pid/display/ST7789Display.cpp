#include "ST7789Display.h"

ST7789Display::ST7789Display(TFT_eSPI& tftInstance) : tft(tftInstance) {}

void ST7789Display::init() {
    
}

void ST7789Display::clearBuffer() {
    tft.fillScreen(TFT_BLACK);  // Clear the screen
}

void ST7789Display::setPowerSave(uint32_t is_enabled) {
    //tft.enableSleep(is_enabled);
}

void ST7789Display::setBitmapMode(uint32_t is_transparent) {
    // Implement bitmap mode using tft, if applicable
}

void ST7789Display::drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
    tft.drawBitmap(x, y, bitmap, w, h, TFT_WHITE);  // Draw bitmap
}

void ST7789Display::setFont(FontType fontType) {
    // if (fontType == FontType::Font10) {
    //     tft.setFont(u8g2_font_profont10_tf);
    // } else if (fontType == FontType::Font11) {
    //     tft.setFont(u8g2_font_profont11_tf);
    // } else if (fontType == FontType::Font22) {
    //     tft.setFont(u8g2_font_profont22_tf);
    // } else if (fontType == FontType::OpenIconicArrow) {
    //     tft.setFont(u8g2_font_open_iconic_arrow_1x_t);
    // } else if (fontType == FontType::OpenIconicEmbedded) {
    //     tft.setFont(u8g2_font_open_iconic_embedded_1x_t);
    // } else if (fontType == FontType::OpenIconicThing) {
    //     tft.setFont(u8g2_font_open_iconic_thing_1x_t);
    // } else if (fontType == FontType::OpenIconicOther) {
    //     tft.setFont(u8g2_font_open_iconic_other_1x_t);
    // }  
}

void ST7789Display::setCursor(int16_t x, int16_t y) {
    tft.setCursor(x, y);  // Set the cursor position
}

void ST7789Display::print(float data, int digits) {
    tft.print(data, digits);  // Print float data
}

void ST7789Display::print(char c) {
    tft.print(c);  // Print a character
}

void ST7789Display::print(const char* c) {
    tft.print(c);  // Print a string
}

void ST7789Display::println(const String &s) {
    tft.println(s);  // Print a string followed by a newline
}

void ST7789Display::drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) {
    // Implement drawing a glyph using tft, if applicable
}

void ST7789Display::sendBuffer() {
    // No need to send a buffer for this library
}

int ST7789Display::getUTF8Width(const char *s) {
    // Implement getting the width of a UTF-8 string using tft, if applicable
}

int ST7789Display::getWidth() {
    return 240;
}

int ST7789Display::getHeight() {
    return 240;
}