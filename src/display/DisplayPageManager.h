#pragma once

#include "templates/IDisplayPage.h"
#include "DisplayManager.h"

class DisplayPageManager {
public:
    DisplayPageManager(DisplayManager *instanceOfDisplayManager);

    IDisplayPage *getPage(DisplayPageType pageType);
private:
    IDisplayPage *page;
    DisplayManager *displayManager;
};
