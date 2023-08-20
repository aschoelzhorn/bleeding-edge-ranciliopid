#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Wire.h>
#include "IDisplay.h"

#include "../userConfig.h"

#if (DISPLAY_HARDWARE == 4)
#define ST7789_DISPLAY
#include "ST7789Display.h"
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>
#else
#define U8G2_DISPLAY
#include "U8g2Display.h"
#endif

#if (DISPLAY_HARDWARE == 3)
#include <SPI.h>
#endif

class DisplayManager {
public:

#ifdef U8G2_DISPLAY
    DisplayManager(U8G2& u8g2Instance);
#endif

#ifdef ST7789_DISPLAY
    DisplayManager(TFT_eSPI& tftInstance);
#endif

    virtual void init();    
    virtual void clearBuffer();
    virtual void setPowerSave(uint32_t is_enabled);
    virtual void setBitmapMode(uint32_t is_transparent);
    virtual void drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap);
    virtual void drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmap);
    virtual void setFont(FontType fontType);
    virtual void setCursor(int16_t x, int16_t y);
    virtual void print(float data, int digits);
    virtual void print(char c);
    virtual void print(const char* c);
    virtual void println(const String &s);
    virtual void drawGlyph(uint8_t x, uint8_t y, uint8_t encoding);
    virtual void sendBuffer();

    virtual int getUTF8Width(const char *s);
    virtual int getWidth();
    virtual int getHeight();

private:
   IDisplay* display;  // Use a pointer to IDisplay to allow dynamic initialization
};

#endif // DISPLAYMANAGER_H
