#pragma once

#include "../userConfig.h"

#if DISPLAY_HARDWARE == 4

enum class Area {
    BootLogo = 0,
    BootMessage = 1,
    Statusbar,
    Header,

    ActionImage = 2, // like icon for heating, brewing, cleaning, ....
    // StatusMessage = 3,
    // StatusIcons = 4,
    // ProfileIcon = 5,
    Temperature = 6,
    // SoftwareUpdate = 7,
    
    // //test for clever coffee minimal template
    Progressbar,
    BrewTime
};

#else

enum class Area {
    Statusbar,
    Progressbar,
    Temperature,
    BrewTime
};
#endif

