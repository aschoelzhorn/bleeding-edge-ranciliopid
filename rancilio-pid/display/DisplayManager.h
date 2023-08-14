#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Wire.h>
#include "IDisplay.h"

#if (DISPLAY_HARDWARE < 4)
#define U8G2_DISPLAY
#include "U8g2Display.h"
#endif

#if (DISPLAY_HARDWARE == 4)
#define ST7735_DISPLAY
#include "ST7735Display.h"
#endif

#if (DISPLAY_HARDWARE == 3 || DISPLAY_HARDWARE == 4)
#include <SPI.h>
#endif

class DisplayManager {
public:
    DisplayManager();  // Constructor initializes the display instance
    // ... DisplayManager methods ...
    void displaymessage(State state, char* message1, char* message2);

private:
   IDisplay* display;  // Use a pointer to IDisplay to allow dynamic initialization
};

#endif // DISPLAYMANAGER_H
