#include "display_test.h"

#include "ImageDictionary.h"


ImageDictionary images;


void display_test_setup() {
    Serial.begin(115200);
    Serial.println("display_test_setup");
    display.init();
    Serial.println();

    Viewport bootLogo = display.getView(Area::BootLogo);
    Viewport bootMessage = display.getView(Area::BootMessage);
    Viewport statusMessage = display.getView(Area::StatusMessage);
    Viewport statusIcons = display.getView(Area::StatusIcons);
    Viewport actionImage = display.getView(Area::ActionImage);
    Viewport temperature = display.getView(Area::Temperature);

    Serial.println("Area::BootLogo, TFT_BLUE");
    Serial.println(bootLogo.getDebugString());
    display.fillView(Area::BootLogo, TFT_BLUE);
    Serial.println();

    delay(200);
    Serial.println("Area::BootMessage, TFT_GREEN");
    Serial.println(bootMessage.getDebugString());
    display.fillView(Area::BootMessage, TFT_GREEN);
    Serial.println();

    delay(200);
    Serial.println("clear");
    display.clearBuffer();
    Serial.println();
    delay(200);

    Serial.println("Area::ActionImage, TFT_RED");
    Serial.println(actionImage.getDebugString());
    display.fillView(Area::ActionImage, TFT_RED);
    Serial.println();

    Serial.println("Area::Temperature, TFT_DARKGREY");
    Serial.println(temperature.getDebugString());
    display.fillView(Area::Temperature, TFT_DARKGREY);    
    Serial.println();

    Serial.println("Area::StatusMessage, TFT_ORANGE");
    Serial.println(statusMessage.getDebugString());
    display.fillView(Area::StatusMessage, TFT_ORANGE);    
    Serial.println();

    Serial.println("Area::StatusIcons, TFT_WHITE");
    Serial.println(statusIcons.getDebugString());
    display.fillView(Area::StatusIcons, TFT_WHITE);
    delay(200);
    Serial.println();

    // images.init();
}

void display_test_loop() {

    display.clearBuffer();

// showBootLogo()
//   //int posX = (display.getWidth() - logo_width) / 2;

int logowidth = 216;
int logoheight = 131;


// const unsigned char* retrievedData = images.getImage(StatusImage::Clean);
// if (retrievedData != nullptr) {
//     Serial.println("retrievedData != nullptr");
// } else {
//     Serial.println("retrievedData == nullptr !!!!!");
// }
//display.drawImage(0, 0, 45, 45, retrievedData);

MyPoint p1 = display.getView(Area::BootLogo).getUpperLeft();
display.drawImage(p1.X, p1.Y, logowidth, logoheight, images.getLogo(StatusImage::MachineLogo));
//display.drawImage(p1.X, p1.Y, ecm_logo_width, ecm_logo_height, ecm_logo_bits);
//uint16_t* image_data = images.getLogo(StatusImage::MachineLogo);

//const uint16_t* dataPointer = images.logoDictionary[StatusImage::MachineLogo];
//const uint16_t* actualData = dataPointer;
//display.drawImage(p1.X, p1.Y, logowidth, logoheight, actualData);

//display.drawImage(p1.X, p1.Y, 45, 45, images.getImage(StatusImage::Brewing));
//   // this could also be changed to something like
//display.drawImageCentered(ViewPort, image);

delay(1000);

// // hideBootLogo()
//   int posX = (display.getWidth() - logo_width) / 2;
//   display.clearRect(posX, 0, logo_width, logo_height);

//   delay(1000);
}
