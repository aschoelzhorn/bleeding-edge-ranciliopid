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
#elif (DISPLAY_HARDWARE == 1) || (DISPLAY_HARDWARE == 2) || (DISPLAY_HARDWARE == 3)
#define U8G2_DISPLAY
#include "U8g2Display.h"
#else
#define NO_DISPLAY
#endif

#if (DISPLAY_HARDWARE == 3)
#include <SPI.h>
#endif

#if (DISPLAY_HARDWARE == 0)
#define NO_DISPLAY
#include "DummyDisplay.h"
#endif

class DisplayManager {
public:

#ifdef U8G2_DISPLAY
    DisplayManager(U8G2& u8g2Instance);
#endif

#ifdef ST7789_DISPLAY
    DisplayManager(TFT_eSPI& tftInstance);
#endif

#ifdef NO_DISPLAY
    DisplayManager();
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

    virtual int getWidth();
    virtual int getHeight();

    virtual void clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    virtual void printCentered(const char* c, uint16_t y);
    virtual void printCentered(const char* line1, const char* line2, uint16_t y);
    virtual void printRightAligned(const char* c, uint16_t y);
    virtual void printRightAligned(float data, unsigned int digits, uint16_t y);
    virtual void printTemperatures(float t1, float t2, bool steaming);

private:
   IDisplay* display;  // Use a pointer to IDisplay to allow dynamic initialization
};

#endif // DISPLAYMANAGER_H
