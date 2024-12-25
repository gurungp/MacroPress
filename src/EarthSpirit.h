
#pragma once

#include "AdvancedKeyboardSimulator.h"
#include "InputMonitor.h"

// Earth Spirit
CGEventRef EarthSpirit(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor,
                       CGEventRef &event);

//--------------Earth-Spirit------------------

static std::vector<AdvancedButtonPress3> ESpirit1 = {

    {{3, 201, 19}, {}, 20, 20, 40}, // f + left click + 2
    {{12}, {}, 160, 20, 680},       // q

    {{13}, {}, 900, 20, 30},   // w
    {{2}, {58}, 1100, 20, 35}, // d
                               //  {2, 79, 1380, 50},  // d

    //    {6, 1120, 55},  // z
    //   {1, 1300, 60},  // s=1
    //    {15, 1490, 54}  // r

};

static std::vector<AdvancedButtonPress3> ESpirit2 = {
    // {56,100,55}, // shift
    {{19, 2, 14, 13}, {}, 20, 20, 100}, // 2,d,e,w
    {{12}, {}, 850, 20, 700},           // q

};

static std::vector<AdvancedButtonPress3> ESpirit3 = {
    {{3, 201, 19, 17}, {}, 20, 20, 40}, // f + left click + 2+t(Scepter)
    {{12}, {}, 250, 20, 660},           //  q
    {{13}, {}, 1050, 20, 40},           // w
    {{2}, {58}, 1120, 20, 40},          // d

};
