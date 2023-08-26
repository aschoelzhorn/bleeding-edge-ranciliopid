#include "DummyDisplay.h"

DummyDisplay::DummyDisplay() {
}

void DummyDisplay::init() {
}

void DummyDisplay::clearBuffer() {
}

void DummyDisplay::sendBuffer() {
}

void DummyDisplay::setPowerSave(uint32_t is_enabled) {
}

void DummyDisplay::setBitmapMode(uint32_t is_transparent) {
}

void DummyDisplay::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
}

void DummyDisplay::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmap) {
}

void DummyDisplay::setFont(FontType fontType) {
}

void DummyDisplay::setCursor(int16_t x, int16_t y) {
}

void DummyDisplay::print(float data, int digits) {
}

void DummyDisplay::print(char c) {
}

void DummyDisplay::print(const char* c) {
}

void DummyDisplay::println(const String &s) {
}

void DummyDisplay::drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) {
}

void DummyDisplay::clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
}

int DummyDisplay::getWidth() {
    return 1;
}

int DummyDisplay::getHeight() {
    return 1;
}

void DummyDisplay::printCentered(const char* c, uint16_t y) {
}

void DummyDisplay::printCentered(const char* line1, const char* line2, uint16_t y) {
}

void DummyDisplay::printRightAligned(const char* c, uint16_t y) {
}

void DummyDisplay::printRightAligned(float data, unsigned int digits, uint16_t y) {
}

void DummyDisplay::printTemperatures(float t1, float t2, bool steaming) {
}

