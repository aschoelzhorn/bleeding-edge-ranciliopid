#include "ST7789Display.h"
#include "../userConfig.h"

#include <float.h>

ST7789Display::ST7789Display(TFT_eSPI& tftInstance) : tft(tftInstance) {
}

void ST7789Display::init() {
    tft.init();
    tft.fillScreen(TFT_BLACK);
#if (ROTATE_DISPLAY == 0)
    tft.setRotation(0);
#elif 
    tft.setRotation(3);
#endif    
}

void ST7789Display::clearBuffer() {
   tft.fillScreen(TFT_BLACK);
}

void ST7789Display::sendBuffer() {
    // No need to send a buffer for this library
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
    tft.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    tft.pushImage(x,y,w,h,bitmap);
    tft.setSwapBytes(false);
}

void ST7789Display::setFont(FontType fontType) {
    if (fontType == FontType::Small) {
       tft.setFreeFont(&FreeSans9pt7b);
    } else if (fontType == FontType::Normal) {
       tft.setFreeFont(&FreeSans12pt7b);
    } else if (fontType == FontType::Big) {
       tft.setFreeFont(&FreeSans18pt7b);
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

void ST7789Display::clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    tft.fillRect(x, y, w, h, TFT_BLACK);
}

int ST7789Display::getWidth() {
    return tft.width();
}

int ST7789Display::getHeight() {
    return tft.height();
}

void ST7789Display::printCentered(const char* c, uint16_t y) {
    int posX = tft.width() / 2; // Calculate the center X position
    tft.setTextDatum(TC_DATUM);
    tft.drawString(c, posX, y);  // Print a string
}

void ST7789Display::printCentered(const char* line1, const char* line2, uint16_t y) {
    int posX = tft.width() / 2;
    tft.setTextDatum(TC_DATUM);
    tft.drawString(line1, posX, y);
    tft.drawString(line2, posX, y + tft.fontHeight());
}

void ST7789Display::printRightAligned(const char* c, uint16_t y) {
    int posX = tft.width() - tft.textWidth(c);
    tft.drawString(c, posX, y);
}

void ST7789Display::printRightAligned(float data, unsigned int digits, uint16_t y) {
    int dataDigits = 0;
    if (data - 100 > -FLT_EPSILON) {
        dataDigits = 3;
    } else {
        dataDigits = 2;
    }
    int charWidth = tft.textWidth("0"); // Width of a single character
    int numWidth = charWidth * (dataDigits + 1 + digits); // Include decimal point
    int posX = tft.width() - numWidth;
    tft.drawFloat(data, digits, posX, y);
}

void ST7789Display::printTemperatures(float input, float setPoint, bool steaming) {
    setFont(FontType::Big);
    printRightAligned(input, 1, 0 + topMargin);
//   setFont(FontType::Small);
//   tft.print((char)176);
//   tft.println("C");
//   setFont(FontType::OpenIconicEmbedded);
//   tft.drawGlyph(align_right - 11, 3 + 6, 0x0046);

  // if (Input <= *activeSetPoint + 5 || activeState == State::SteamMode) { //only show setpoint if we are not steaming
    if (!steaming) {
        setFont(FontType::Big);
        printRightAligned(setPoint, 1, tft.fontHeight());
    // setFont(FontType::Small);
    // tft.print((char)176);
    // tft.println("C");
    // setFont(FontType::OpenIconicOther);
    //tft.drawGlyph(align_right - 11, 20 + 6, 0x047);  // small circle in circle
    }    
}

