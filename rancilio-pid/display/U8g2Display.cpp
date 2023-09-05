#include "U8g2Display.h"
#include "../userConfig.h"

#include <float.h>

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

  initViews();    
}

void U8g2Display::initViews() {
    int logowidth  = 45;

    MyPoint p1 = MyPoint((this->getWidth() - logowidth) / 2, 0);
    MyPoint p2 = MyPoint(0, logowidth);

    bootlogo = Viewport(p1, this->getHeight() / 2, 10);
    bootmessage = Viewport(MyPoint((this->getWidth() - logowidth) / 2, 0), 10, 10);
    statusmessage = Viewport(MyPoint((this->getWidth() - logowidth) / 2, 0), 10, 10);

    areaMap = {
        {Area::BootLogo, this->bootlogo},
        {Area::BootMessage, this->bootmessage},
        {Area::StatusMessage, this->statusmessage},
    };        
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

void U8g2Display::clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    u8g2.setDrawColor(0);
    u8g2.drawBox(x, y, w, h);
    u8g2.sendBuffer();
    u8g2.setDrawColor(1);
    u8g2.sendBuffer();
}

void U8g2Display::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
    u8g2.drawXBMP(x, y, w, h, bitmap);
    u8g2.sendBuffer();
}

void U8g2Display::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmap) {
    //u8g2.drawXBMP(x, y, w, h, bitmap); // TODO: show not supported image
}

void U8g2Display::setFont(FontType fontType) {
    if (fontType == FontType::Small) {
        u8g2.setFont(u8g2_font_profont10_tf);
    } else if (fontType == FontType::Normal) {
        u8g2.setFont(u8g2_font_profont11_tf);
    } else if (fontType == FontType::Big) {
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

int U8g2Display::getWidth() {
    return u8g2.getDisplayWidth();
}

int U8g2Display::getHeight() {
    return u8g2.getDisplayHeight();
}

void U8g2Display::printCentered(const char* c, uint16_t y) {
    int textWidth = u8g2.getStrWidth(c);
    int centerX = (u8g2.getWidth() - textWidth) / 2;
    u8g2.setCursor(centerX, y);
    u8g2.print(c);
    u8g2.sendBuffer();
}

void U8g2Display::printCentered(const char* line1, const char* line2, uint16_t y) {
    int leading = 1;
    
    int textWidth = u8g2.getStrWidth(line1);
    int centerX = (u8g2.getWidth() - textWidth) / 2;
    u8g2.setCursor(centerX, y);
    u8g2.print(line1);

    textWidth = u8g2.getStrWidth(line2);
    centerX = (u8g2.getWidth() - textWidth) / 2;
    int yPos = y + u8g2.getMaxCharHeight() + leading;
    u8g2.setCursor(centerX, yPos);
    u8g2.print(line2);

    u8g2.sendBuffer();
}

void U8g2Display::printRightAligned(const char* c, uint16_t y) {
    int posX = u8g2.getWidth() - u8g2.getStrWidth(c);
    u8g2.setCursor(posX, y);
    u8g2.print(c);
    u8g2.sendBuffer();
}

void U8g2Display::printRightAligned(float data, unsigned int digits, uint16_t y) {
    int dataDigits = 0;
    if (data - 100 > -FLT_EPSILON) {
        dataDigits = 3;
    } else {
        dataDigits = 2;
    }
    
    int charWidth = u8g2.getStrWidth("0"); // Width of a single character
    int numWidth = charWidth * (dataDigits + 1 + digits); // Include decimal point

    int posX = u8g2.getWidth() - numWidth;
    u8g2.setCursor(posX, y);
    u8g2.print(data, digits);
    u8g2.sendBuffer();
}

void U8g2Display::printTemperatures(float input, float setPoint, bool steaming) {
  unsigned int align_right;
  const unsigned int align_right_2digits = u8g2.getWidth() - 56; // TODO replace these magic numbers, what is 56?
  const unsigned int align_right_3digits = u8g2.getWidth() - 56 - 12; // TODO replace these magic numbers, what is 56 and what is 12?

  if (input - 100 > -FLT_EPSILON) {
    align_right = align_right_3digits;
  } else {
    align_right = align_right_2digits;
  }
  setFont(FontType::Big);
  u8g2.setCursor(align_right, 3);
  u8g2.print(input, 1);
  setFont(FontType::Small);
  u8g2.print((char)176);
  u8g2.println("C");
  setFont(FontType::OpenIconicEmbedded);
  u8g2.drawGlyph(align_right - 11, 3 + 6, 0x0046);

  // if (Input <= *activeSetPoint + 5 || activeState == State::SteamMode) { //only show setpoint if we are not steaming
  if (!steaming) {
    if (setPoint >= 100) {
      align_right = align_right_3digits;
    } else {
      align_right = align_right_2digits;
    }
    setFont(FontType::Big);
    u8g2.setCursor(align_right, 20);
    u8g2.print(setPoint, 1);
    setFont(FontType::Small);
    u8g2.print((char)176);
    u8g2.println("C");
    setFont(FontType::OpenIconicOther);
    u8g2.drawGlyph(align_right - 11, 20 + 6, 0x047);  // small circle in circle
  }
}

Viewport U8g2Display::getView(Area area) {
    return areaMap[area];
}

void U8g2Display::clearView(Area area) {
    Viewport view = getView(area);
    clearRect(view.getUpperLeft().X, view.getUpperLeft().Y, view.getWidth(), view.getHeight());
}

void U8g2Display::fillView(Area area, uint32_t color) {
    Viewport view = getView(area);

    if (color != 0) {
        color = 1;
    }
    
    u8g2.setDrawColor(color);
    u8g2.drawBox(view.getUpperLeft().X, view.getUpperLeft().Y, view.getWidth(), view.getHeight());
    u8g2.sendBuffer();
}

void U8g2Display::drawImageCentered(Area area, const uint8_t *bitmap) {
    Viewport view = getView(area);
    drawImage(view.getUpperLeft().X, view.getUpperLeft().Y, 45, 45, bitmap); // TODO: replace 45
}

void U8g2Display::drawImageCentered(Area area, const uint16_t *bitmap) {
    Viewport view = getView(area);
    drawImage(view.getUpperLeft().X, view.getUpperLeft().Y, 45, 45, bitmap); // TODO: replace 45
}