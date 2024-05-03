#include "DisplayPageManager.h"

#include "DisplayPageTemperatureOnly.h" 
#include "DisplayPageMinimal.h" 
#include "DisplayPageStandard.h" 
//#include "DisplayPageScale.h" 

DisplayPageManager::DisplayPageManager(DisplayManager *instanceOfDisplayManager) {
    displayManager = instanceOfDisplayManager;
}

DisplayPage *DisplayPageManager::getPage(DisplayPageType pageType) {
    // return correct instance of DisplayPage
    switch (pageType) {
        case DisplayPageType::TemperatureOnly: {
            page = new DisplayPageTemperatureOnly(displayManager);
            break;
        }
        case DisplayPageType::Minimal: {
            page = new DisplayPageMinimal(displayManager);
            break;
        }
        case DisplayPageType::Scale: {
            //page = new DisplayPageScale(displayManager);
            break;
        }
        case DisplayPageType::Standard: {
            page = new DisplayPageStandard(displayManager);
            break;
        }
        default: {
            // error? or just use standard?
            // page = new DisplayPageStandard(displayManager);
            break;    
        }
    }

    return page;
}