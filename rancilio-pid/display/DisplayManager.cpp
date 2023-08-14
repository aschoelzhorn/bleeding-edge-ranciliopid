#include "DisplayManager.h"

DisplayManager::DisplayManager() {

#ifdef U8G2_DISPLAY
// Attention: refresh takes around 42ms (esp32: 26ms)!
#if (DISPLAY_HARDWARE == 1)
  U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, DISPLAY_I2C_SCL, DISPLAY_I2C_SDA); // e.g. 1.3"
#elif (DISPLAY_HARDWARE == 2)
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, DISPLAY_I2C_SCL, DISPLAY_I2C_SDA); // e.g. 0.96"
#else
// 23-MOSI 18-CLK
#define OLED_CS             5
#define OLED_DC             2
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, /* reset=*/U8X8_PIN_NONE); // e.g. 1.3"
#endif
    display = new U8g2Display(u8g2);
#endif

#ifdef ST7735_DISPLAY
    // Initialize your Adafruit_ST7735 instance
    // ...
    Adafruit_ST7735 tft(/* ... Pin configuration ... */);
    display = new ST7735Display(tft);
#endif
    // ... Initialize other variables ...
}

void DisplayManager::displaymessage(State state, char* message1, char* message2) {
    //display->clearScreen();
    // Implement displaying the state and messages on the display
    // For example, use display.showText(...) or other methods depending on your display class
}

// ... Implement other DisplayManager methods ...
