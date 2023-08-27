#ifndef ST7789DISPLAY_H
#define ST7789DISPLAY_H

#include <TFT_eSPI.h>
#include <TFT_eWidget.h>
#include "IDisplay.h"

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
#define BLUE2GREEN 6

class ST7789Display : public IDisplay {
public:
    ST7789Display(TFT_eSPI& tftInstance);

    void init(void) override;
    void clearBuffer() override;
    void setPowerSave(uint32_t is_enabled) override;
    void setBitmapMode(uint32_t is_transparent) override;
    void drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) override;
    void drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmap) override;
    void setFont(FontType fontType) override;
    void setCursor(int16_t x, int16_t y) override;
    void print(float data, int digits) override;
    void print(char c) override;
    void print(const char* c) override;
    void println(const String &s) override;
    void drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) override;
    void sendBuffer() override;
    int getWidth() override;
    int getHeight() override;
    void clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) override;
    void printCentered(const char* c, uint16_t y) override;
    void printCentered(const char* line1, const char* line2, uint16_t y) override;
    void printRightAligned(const char* c, uint16_t y) override;
    void printRightAligned(float data, unsigned int digits, uint16_t y) override;

    void printTemperatures(float t1, float t2, bool steaming) override;

    Viewport getView(Area) override;
    void clearView(Area) override;

private:
    TFT_eSPI& tft;
    unsigned int topMargin = 10;
    int ringMeter(int value, int vmin, int vmax, int x, int y, int r, const char *units, byte scheme);
    unsigned int rainbow(byte value);
    float sineWave(int phase);

    void initViews();

    std::map<Area, Viewport> areaMap;
    Viewport bootlogo;
    Viewport bootmessage;
    Viewport statusmessage;
};

#endif // ST7789DISPLAY_H
