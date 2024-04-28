#ifndef DISPLAYPAGEMANAGER_H
#define DISPLAYPAGEMANAGER_H

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

#endif // DISPLAYPAGEMANAGER_H
