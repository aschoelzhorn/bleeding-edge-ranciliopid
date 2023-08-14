#ifndef U8G2DISPLAY_H
#define U8G2DISPLAY_H

#include <U8g2lib.h>
#include "DisplayBase.h"
#include "IDisplay.h"

// #include "../display.h"

class U8g2Display : public DisplayBase, public IDisplay {
public:
    U8g2Display(U8G2& u8g2Instance);
     void displaymessage(State state, char* message1, char* message2) override;

private:
    U8G2& u8g2;

    void u8g2_init(void);
    void u8g2_prepare(void);
    bool screenSaverCheck();
    void displaymessage_helper(State activeState, char* displaymessagetext, char* displaymessagetext2);
};

#endif // U8G2DISPLAY_H
