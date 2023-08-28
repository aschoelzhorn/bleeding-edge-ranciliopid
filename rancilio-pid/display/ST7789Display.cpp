#include "ST7789Display.h"
#include "../userConfig.h"

#include <float.h>





ST7789Display::ST7789Display(TFT_eSPI& tftInstance) : tft(tftInstance) {
}

void ST7789Display::init() {
    tft.init();
    tft.fillScreen(TFT_BLACK);
#if (ROTATE_DISPLAY == 0)
    tft.setRotation(0);
#elif 
    tft.setRotation(3);
#endif    

    initViews();
}

void ST7789Display::initViews() {
    int logo_width  = 45;

    int width = getWidth();
    int height = getHeight();

    int status_icon_height = 15;

    bootlogo = Viewport(MyPoint(0, 0), width, height / 2);
    bootmessage = Viewport(MyPoint(0, height / 2), width, height / 2);
    
    actionimage = Viewport(MyPoint(0, 0), width / 2, height / 2);
    temperature = Viewport(MyPoint(width / 2, 0), width / 2, height / 2);
    
    statusmessage = Viewport(MyPoint(0, height / 2), width, (height/2)-status_icon_height);
    statusicons = Viewport(MyPoint(0, height - status_icon_height), width, status_icon_height);

    areaMap = {
        {Area::BootLogo, this->bootlogo},
        {Area::BootMessage, this->bootmessage},
        
        {Area::ActionImage, this->actionimage},
        {Area::Temperature, this->temperature},
        {Area::StatusMessage, this->statusmessage},
        {Area::StatusIcons, this->statusicons},
        
    };    
}

void ST7789Display::clearBuffer() {
   tft.fillScreen(TFT_BLACK);
}

void ST7789Display::sendBuffer() {
    // No need to send a buffer for this library
}

void ST7789Display::setPowerSave(uint32_t is_enabled) {
    //tft.enableSleep(is_enabled);
}

void ST7789Display::setBitmapMode(uint32_t is_transparent) {
    // Implement bitmap mode using tft, if applicable
}

void ST7789Display::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap) {
   tft.drawXBitmap(x, y, bitmap, w, h, TFT_WHITE);  // Draw bitmap
}

void ST7789Display::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *bitmap) {
    tft.setSwapBytes(true); // swap the byte order for pushImage() - corrects endianness
    tft.pushImage(x,y,w,h,bitmap);
    tft.setSwapBytes(false);
}

void ST7789Display::setFont(FontType fontType) {
    if (fontType == FontType::Small) {
       tft.setFreeFont(&FreeSans9pt7b);
    } else if (fontType == FontType::Normal) {
       tft.setFreeFont(&FreeSans12pt7b);
    } else if (fontType == FontType::Big) {
       tft.setFreeFont(&FreeSans18pt7b);
    } else if (fontType == FontType::OpenIconicArrow) {
         tft.setFreeFont(&FreeMono12pt7b);
    } else if (fontType == FontType::OpenIconicEmbedded) {
        tft.setFreeFont(&FreeMono12pt7b);
    } else if (fontType == FontType::OpenIconicThing) {
        tft.setFreeFont(&FreeMono12pt7b);
    } else if (fontType == FontType::OpenIconicOther) {
        tft.setFreeFont(&FreeMono12pt7b);
    }  
}

void ST7789Display::setCursor(int16_t x, int16_t y) {
    tft.setCursor(x, y);  // Set the cursor position
}

void ST7789Display::print(float data, int digits) {
    tft.drawFloat(data, digits, tft.getCursorX(), tft.getCursorY());  // Print float data
}

void ST7789Display::print(char c) {
    tft.drawChar(c, tft.getCursorX(), tft.getCursorY());  // Print a character
}

void ST7789Display::print(const char* c) {
    tft.drawString(c, tft.getCursorX(), tft.getCursorY());  // Print a string
}

void ST7789Display::println(const String &s) {
    tft.drawString(s, tft.getCursorX(), tft.getCursorY());  // Print a string followed by a newline
}

void ST7789Display::drawGlyph(uint8_t x, uint8_t y, uint8_t encoding) {
    // Implement drawing a glyph using tft, if applicable
}

void ST7789Display::clearRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    tft.fillRect(x, y, w, h, TFT_BLACK);
}

int ST7789Display::getWidth() {
    return tft.width();
}

int ST7789Display::getHeight() {
    return tft.height();
}

void ST7789Display::printCentered(const char* c, uint16_t y) {
    int posX = tft.width() / 2; // Calculate the center X position
    tft.setTextDatum(TC_DATUM);
    tft.drawString(c, posX, y);  // Print a string
}

void ST7789Display::printCentered(const char* line1, const char* line2, uint16_t y) {
    int posX = tft.width() / 2;
    tft.setTextDatum(TC_DATUM);
    tft.drawString(line1, posX, y);
    tft.drawString(line2, posX, y + tft.fontHeight());
}

void ST7789Display::printRightAligned(const char* c, uint16_t y) {
    int posX = tft.width() - tft.textWidth(c);
    tft.drawString(c, posX, y);
}

void ST7789Display::printRightAligned(float data, unsigned int digits, uint16_t y) {
    int dataDigits = 0;
    if (data - 100 > -FLT_EPSILON) {
        dataDigits = 3;
    } else {
        dataDigits = 2;
    }
    int charWidth = tft.textWidth("0"); // Width of a single character
    int numWidth = charWidth * (dataDigits + 1 + digits); // Include decimal point
    int posX = tft.width() - numWidth;
    tft.drawFloat(data, digits, posX, y);
}

void ST7789Display::printTemperatures(float input, float setPoint, bool steaming) {
    int xpos = 120;
    int ypos = 10;
    int radius = 52;

    ringMeter(input, 0, setPoint, xpos, ypos, radius, "C", BLUE2GREEN);
}

// #########################################################################
//  Draw the meter on the screen, returns x coord of righthand side
// #########################################################################
int ST7789Display::ringMeter(int value, int vmin, int vmax, int x, int y, int r, const char *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
  
  x += r; y += r;   // Calculate coords of centre of ring

  int w = r / 3;    // Width of outer ring is 1/4 of radius
  
  int angle = 150;  // Half the sweep angle of meter (300 degrees)

  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v

  byte seg = 6; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 12; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Variable to save "value" text colour from scheme and set default
  int colour = TFT_BLUE;
 
  // Draw colour blocks every inc degrees
  for (int i = -angle+inc/2; i < angle-inc/2; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      switch (scheme) {
        case 0: colour = TFT_RED; break; // Fixed colour
        case 1: colour = TFT_GREEN; break; // Fixed colour
        case 2: colour = TFT_BLUE; break; // Fixed colour
        case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
        case 4: colour = rainbow(map(i, -angle, angle, 70, 127)); break; // Green to red (high temperature etc)
        case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
        case 6: colour = rainbow(map(i, -angle, angle, 0, 63)); break; // Blue to green (water temperature etc)        
        default: colour = TFT_BLUE; break; // Fixed colour
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      //text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 3; if (value > 999) len = 5;
  dtostrf(value, len, 0, buf);
  buf[len] = ' '; buf[len+1] = 0; // Add blanking space and terminator, helps to centre text too!
  // Set the text colour to default
  tft.setTextSize(1);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // Uncomment next line to set the text colour to the last segment value!
  tft.setTextColor(colour, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  // Print value, if the meter is large then use big font 8, othewise use 4
  if (r > 84) {
    tft.setTextPadding(55*3); // Allow for 3 digits each 55 pixels wide
    tft.drawString(buf, x, y, 8); // Value in middle
  }
  else {
    tft.setTextPadding(3 * 14); // Allow for 3 digits each 14 pixels wide
    tft.drawString(buf, x, y, 4); // Value in middle
  }
  tft.setTextSize(1);
  tft.setTextPadding(0);
  // Print units, if the meter is large then use big font 4, othewise use 2
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  if (r > 84) tft.drawString(units, x, y + 60, 4); // Units display
  else tft.drawString(units, x, y + 15, 2); // Units display

  // Calculate and return right hand side x coordinate
  return x + r;
}

unsigned int ST7789Display::rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

// #########################################################################
// Return a value in range -1 to +1 for a given phase angle in degrees
// #########################################################################
float ST7789Display::sineWave(int phase) {
  return sin(phase * 0.0174532925);
}

Viewport ST7789Display::getView(Area area) {
    return areaMap[area];
}

void ST7789Display::clearView(Area area) {
    Viewport view = getView(area);
    clearRect(view.getUpperLeft().X, view.getUpperLeft().Y, view.getWidth(), view.getHeight());
}

void ST7789Display::fillView(Area area, uint32_t color) {
    Viewport view = getView(area);
    tft.fillRect(view.getUpperLeft().X, view.getUpperLeft().Y, view.getWidth(), view.getHeight(), color);
}

