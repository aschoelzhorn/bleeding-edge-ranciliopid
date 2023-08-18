#ifndef ST7789DISPLAY_H
#define ST7789DISPLAY_H

// #include <Adafruit_GFX.h>
// #include <Adafruit_ST7789.h>
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>
#include "IDisplay.h"

class ST7789Display : public IDisplay {
public:
    ST7789Display(TFT_eSPI& tftInstance);

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
    TFT_eSPI& tft;
};

#endif // ST7789DISPLAY_H
