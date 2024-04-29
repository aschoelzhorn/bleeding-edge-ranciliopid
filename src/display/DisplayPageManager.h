#pragma once

#include "DisplayPage.h"
#include "DisplayManager.h"

class DisplayPageManager {
public:
    DisplayPageManager(DisplayManager *instanceOfDisplayManager);

    DisplayPage *getPage(DisplayPageType pageType);
private:
    DisplayPage *page;
    DisplayManager *displayManager;
};
