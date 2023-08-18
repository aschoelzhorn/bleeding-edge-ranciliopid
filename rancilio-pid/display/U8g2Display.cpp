#include "U8g2Display.h"

#include "../userConfig.h"

U8g2Display::U8g2Display(U8G2& u8g2Instance) : u8g2(u8g2Instance) {}

void U8g2Display::init(void) {
#ifdef ESP32
#if (DISPLAY_HARDWARE == 3)
  u8g2.setBusClock(600000);
#else
  u8g2.setBusClock(2000000);
#endif
#endif
  u8g2.begin();
  prepare();
  u8g2.setFlipMode(ROTATE_DISPLAY);
  u8g2.clearBuffer();
}

void U8g2Display::prepare(void) {
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.setPowerSave(0);
}

void U8g2Display::clearBuffer() {
    u8g2.clearBuffer();
}

void U8g2Display::setPowerSave(uint32_t is_enabled) {
    if (is_enabled) {
        u8g2.setPowerSave(1);  // Enable power save
    } else {
        u8g2.setPowerSave(0);  // Disable power save
    }
}

void U8g2Display::setBitmapMode(uint32_t is_transparent) {
    if (is_transparent) {
        u8g2.setBitmapMode(1);  // Enable transparent bitmap mode
    } else {
        u8g2.setBitmapMode(0);  // Disable transparent bitmap mode
    }
}

void U8g2Display::drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
    u8g2.drawXBMP(x, y, w, h, bitmap);
}

void U8g2Display::setFont(FontType fontType) {
    if (fontType == FontType::Font10) {
        u8g2.setFont(u8g2_font_profont10_tf);
    } else if (fontType == FontType::Font11) {
        u8g2.setFont(u8g2_font_profont11_tf);
    } else if (fontType == FontType::Font22) {
        u8g2.setFont(u8g2_font_profont22_tf);
    } else if (fontType == FontType::OpenIconicArrow) {
        u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
    } else if (fontType == FontType::OpenIconicEmbedded) {
        u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t);
    } else if (fontType == FontType::OpenIconicThing) {
        u8g2.setFont(u8g2_font_open_iconic_thing_1x_t);
    } else if (fontType == FontType::OpenIconicOther) {
        u8g2.setFont(u8g2_font_open_iconic_other_1x_t);
    }    
}

void U8g2Display::setCursor(int16_t x, int16_t y) {
    u8g2.setCursor(x, y);
}

void U8g2Display::print(float data, int digits) {
    u8g2.print(data, digits);
}

void U8g2Display::print(char c) {
    u8g2.print(c);
}

void U8g2Display::print(const char* c) {
    u8g2.print(c);
}

void U8g2Display::println(const String &s) {
    u8g2.println(s);
}

void U8g2Display::drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) {
    u8g2.drawGlyph(x, y, encoding);
}

void U8g2Display::sendBuffer() {
    u8g2.sendBuffer();
}

int U8g2Display::getUTF8Width(const char *s) {
    return u8g2.getUTF8Width(s);
}

int U8g2Display::getWidth() {
    return u8g2.getDisplayWidth();
}

int U8g2Display::getHeight() {
    return u8g2.getDisplayHeight();
}
