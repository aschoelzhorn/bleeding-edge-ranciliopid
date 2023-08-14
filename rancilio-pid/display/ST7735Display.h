#ifndef ST7735DISPLAY_H
#define ST7735DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "DisplayBase.h"
#include "IDisplay.h"

class ST7735Display : public DisplayBase, public IDisplay {
public:
    ST7735Display(Adafruit_ST7735& tftInstance);
 void displaymessage(State state, char* message1, char* message2) override;
private:
    Adafruit_ST7735& tft;
};

#endif // ST7735DISPLAY_H
