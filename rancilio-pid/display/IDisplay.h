#ifndef IDISPLAY_H
#define IDISPLAY_H

#include <map>

#include "Viewport.h"

enum class FontType {
    Small,
    Normal,
    Big,
    OpenIconicArrow,
    OpenIconicEmbedded,
    OpenIconicThing,
    OpenIconicOther
};

enum class Area {
    BootLogo = 0,
    BootMessage = 1,
    ActionImage = 2, // like icon for heating, brewing, cleaning, ....
    StatusMessage = 3,
    StatusIcons = 4,
    ProfileIcon = 5,
    Temperature = 6,
    SoftwareUpdate = 7
};

class IDisplay {
public:
    virtual void init();
    virtual void clearBuffer();
    virtual void setPowerSave(uint32_t is_enabled);
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
    virtual void printBrewingInfo(unsigned long totalBrewTime, unsigned long brewTimer, unsigned int activeBrewTimeEndDetection, bool scaleEnabled, int currentWeight, float activeScaleSensorWeightSetPoint); // TODO: we could use a struct instead of 6 paramters, eg. "brewInfoData"
    virtual void printCountdown(unsigned int timer);

    virtual Viewport getView(Area);
    virtual void clearView(Area);
    virtual void fillView(Area view, uint32_t color);

    virtual void drawImageCentered(Area, int, int, const uint8_t *bitmap);
    virtual void drawImageCentered(Area, int, int, const uint16_t *bitmap);

    virtual void printCentered(Area, const char* c);
    virtual void printCentered(Area, const char* line1, const char* line2);

    virtual void drawBorder(Area);
};

#endif // IDISPLAY_H