#ifndef U8G2DISPLAY_H
#define U8G2DISPLAY_H

#include <U8g2lib.h>
#include "IDisplay.h"

// #include "../display.h"

class U8g2Display : public IDisplay {
public:
    U8g2Display(U8G2& u8g2Instance);
    
    void init(void) override;
    void clearBuffer() override;
    void setPowerSave(uint32_t is_enabled) override;
    void setBitmapMode(uint32_t is_transparent) override;
    void drawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) override;
    void setFont(FontType fontType) override;
    void setCursor(int16_t x, int16_t y) override;
    void print(float data, int digits) override;
    void print(char c) override;
    void print(const char* c) override;
    void println(const String &s) override;
    void drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) override;
    void sendBuffer() override;
    int getUTF8Width(const char *s) override;
    int getWidth() override;
    int getHeight() override;

private:
    U8G2& u8g2;

    void prepare();
};

#endif // U8G2DISPLAY_H
