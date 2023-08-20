#include "ST7789Display.h"
#include "../userConfig.h"

ST7789Display::ST7789Display(TFT_eSPI& tftInstance) : tft(tftInstance) {
}

void ST7789Display::init() {
    tft.begin();
#if (ROTATE_DISPLAY == 0)
    tft.setRotation(0);
#elif 
    tft.setRotation(3);
#endif    
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

void ST7789Display::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
   tft.drawXBitmap(x, y, bitmap, w, h, TFT_WHITE);  // Draw bitmap
}

void ST7789Display::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmap) {
    tft.setSwapBytes(true);                      // swap the byte order for pushImage() - corrects endianness
    tft.fillScreen(TFT_BLACK);
    tft.pushImage(x,y,w,h,bitmap);
    tft.setSwapBytes(false);
}

void ST7789Display::setFont(FontType fontType) {
    if (fontType == FontType::Small) {
       tft.setFreeFont(&FreeSans12pt7b);
    } else if (fontType == FontType::Normal) {
       tft.setFreeFont(&FreeSans18pt7b);
    } else if (fontType == FontType::Big) {
       tft.setFreeFont(&FreeSans24pt7b);
    } else if (fontType == FontType::OpenIconicArrow) {
         tft.setFreeFont(&FreeMono12pt7b);
    } else if (fontType == FontType::OpenIconicEmbedded) {
        tft.setFreeFont(&FreeMono12pt7b);
    } else if (fontType == FontType::OpenIconicThing) {
        tft.setFreeFont(&FreeMono12pt7b);
    } else if (fontType == FontType::OpenIconicOther) {
        tft.setFreeFont(&FreeMono12pt7b);
    }  
}

void ST7789Display::setCursor(int16_t x, int16_t y) {
    tft.setCursor(x, y);  // Set the cursor position
}

void ST7789Display::print(float data, int digits) {
    tft.drawFloat(data, digits, tft.getCursorX(), tft.getCursorY());  // Print float data
}

void ST7789Display::print(char c) {
    tft.drawChar(c, tft.getCursorX(), tft.getCursorY());  // Print a character
}

void ST7789Display::print(const char* c) {
    tft.drawString(c, tft.getCursorX(), tft.getCursorY());  // Print a string
}

void ST7789Display::println(const String &s) {
    tft.drawString(s, tft.getCursorX(), tft.getCursorY());  // Print a string followed by a newline
}

void ST7789Display::drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) {
    // Implement drawing a glyph using tft, if applicable
}

void ST7789Display::sendBuffer() {
    // No need to send a buffer for this library
}

int ST7789Display::getUTF8Width(const char *s) {
    return 8;// Implement getting the width of a UTF-8 string using tft, if applicable
}

int ST7789Display::getWidth() {
    return 240;
}

int ST7789Display::getHeight() {
    return 240;
}