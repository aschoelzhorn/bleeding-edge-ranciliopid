#include "DisplayManager.h"

#ifdef U8G2_DISPLAY
DisplayManager::DisplayManager(U8G2& u8g2Instance) {
    display = new U8g2Display(u8g2Instance);
}
#endif

#ifdef ST7789_DISPLAY
DisplayManager::DisplayManager(TFT_eSPI& tftInstance) {
    display = new ST7789Display(tftInstance);
}
#endif

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

void DisplayManager::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
    display->drawImage(x, y, w, h, bitmap);
}

void DisplayManager::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmap) {
    display->drawImage(x, y, w, h, bitmap);
}

void DisplayManager::setFont(FontType fontType) {
    display->setFont(fontType);
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

int DisplayManager::getWidth() {
    return display->getWidth();
}

int DisplayManager::getHeight() {
    return display->getHeight();
}
