#ifndef IDISPLAY_H
#define IDISPLAY_H

enum class FontType {
    Small,
    Normal,
    Big,
    OpenIconicArrow,
    OpenIconicEmbedded,
    OpenIconicThing,
    OpenIconicOther
};


class IDisplay {
public:
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
};

#endif // IDISPLAY_H