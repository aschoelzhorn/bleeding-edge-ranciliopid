#include "DisplayPageManager.h"

// TODO: should only contain pages for correct display type (oled or tft)

#include "templates/DisplayPageStandard.h"
#include "templates/DisplayPageMinimal.h" 
#include "templates/DisplayPageTemperatureOnly.h" 
#include "templates/DisplayPageScale.h"
#include "templates/DisplayPageColor.h" 
#include "templates/DisplayPageColorMinimal.h" 

DisplayPageManager::DisplayPageManager(DisplayManager *instanceOfDisplayManager) {
    displayManager = instanceOfDisplayManager;
}

IDisplayPage *DisplayPageManager::getPage(DisplayPageType pageType) {
    // return correct instance of DisplayPage, instead if using switch/case, we could use an dictionary, make the code easier
    switch (pageType) {
        case DisplayPageType::Standard: {
            page = new DisplayPageStandard(displayManager);
            break;
        }
        case DisplayPageType::Minimal: {
            page = new DisplayPageMinimal(displayManager);
            break;
        }
        case DisplayPageType::TemperatureOnly: {
            page = new DisplayPageTemperatureOnly(displayManager);
            break;
        }
        case DisplayPageType::Scale: {
            page = new DisplayPageScale(displayManager);
            break;
        }
        case DisplayPageType::Color: {
            page = new DisplayPageColor(displayManager);
            break;
        }
        case DisplayPageType::ColorMinimal: {
            page = new DisplayPageColorMinimal(displayManager);
            break;
        }        
        default: {
            // error? or just use standard?
            // page = new DisplayPageStandard(displayManager);
            break;    
        }
    }

    page->initViews();
    return page;
}