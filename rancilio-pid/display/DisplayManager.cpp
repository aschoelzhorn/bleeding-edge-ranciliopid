#include "DisplayManager.h"

DisplayManager::DisplayManager() {

#ifdef U8G2_DISPLAY
// Attention: refresh takes around 42ms (esp32: 26ms)!
#if (DISPLAY_HARDWARE == 1)
  U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, DISPLAY_I2C_SCL, DISPLAY_I2C_SDA); // e.g. 1.3"
#elif (DISPLAY_HARDWARE == 2)
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, DISPLAY_I2C_SCL, DISPLAY_I2C_SDA); // e.g. 0.96"
#else
// 23-MOSI 18-CLK
#define OLED_CS             5
#define OLED_DC             2
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, /* reset=*/U8X8_PIN_NONE); // e.g. 1.3"
#endif
    display = new U8g2Display(u8g2);
#endif

#ifdef ST7735_DISPLAY
    // Initialize your Adafruit_ST7735 instance
    // ...
    Adafruit_ST7735 tft(/* ... Pin configuration ... */);
    display = new ST7735Display(tft);
#endif

    // ... Initialize other variables ...
    width = display->width;
    height = display->height;
}

void DisplayManager::init() {
    display->init();
}

void DisplayManager::clearBuffer() {
    display->clearBuffer();
}

void DisplayManager::setPowerSave(uint32_t is_enabled) {
    display->setPowerSave(is_enabled);
}

void DisplayManager::setBitmapMode(uint32_t is_transparent) {
    display->setBitmapMode(is_transparent);
}

void DisplayManager::drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
    display->drawXBMP(x, y, w, h, bitmap);
}

void DisplayManager::setFont(const uint8_t *font) {
    display->setFont(font);
}

void DisplayManager::setCursor(int16_t x, int16_t y) {
    display->setCursor(x, y);
}

void DisplayManager::print(float data, int digits) {
    display->print(data, digits);
}

void DisplayManager::print(char c) {
    display->print(c);
}

void DisplayManager::print(const char* c) {
    display->print(c);
}

void DisplayManager::println(const String &s) {
    display->println(s);
}

void DisplayManager::drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) {
    display->drawGlyph(x, y, encoding);
}

void DisplayManager::sendBuffer() {
    display->sendBuffer();
}

int DisplayManager::getUTF8Width(const char *s) {
    return display->getUTF8Width(s);
}
