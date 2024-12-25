
#pragma once

#include "InputMonitor.h"
#include "Sequence.h"

CGEventRef SkyWrath(const InputMonitor &inputMonitor,
                    const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

static std::vector<AdvancedButtonPress3> seqSky1 = {
    {{14}, {}, 100, 20, 50},      // e
    {{13, 12}, {}, 350, 20, 100}, // w,q
};

static std::vector<AdvancedButtonPress3> seqSky2 = {
    {{14}, {}, 100, 20, 50},          // e
    {{13, 12, 15}, {}, 350, 20, 180}, // w,q,r
};
static std::vector<AdvancedButtonPress3> seqSky3 = {
    {{19, 14}, {}, 100, 20, 70},      // 2(Hex,Athos/Glepnir),e
    {{15, 13, 12}, {}, 350, 20, 180}, // r,w,q
};

static std::vector<AdvancedButtonPress3> seqSky4 = {
    {{1, 19, 14}, {}, 100, 20, 100},  //  s(Ethereal Blade),2(Hex,Athos/Glepnir),e
    {{15, 13, 12}, {}, 620, 20, 180}, // r,w,q
};
static std::vector<AdvancedButtonPress3> seqSky5 = {

    {{0, 201}, {}, 100, 20, 50},      // a(Soul Burn/Other Items), left click
    {{1, 19, 14}, {}, 300, 20, 100},  //  s(Ethereal Blade),2(Hex,Athos/Glepnir),e
    {{15, 13, 12}, {}, 720, 20, 180}, // r,w,q

};

static std::vector<AdvancedButtonPress3> seqSky6 = {
    {{3, 201, 0, 201}, {}, 100, 20, 100}, // f(Blink), left click, a(Soul Burn/Other Items), left click
    {{1, 19, 14}, {}, 590, 20, 100},      //  s(Ethereal Blade),2(Hex,Athos/Glepnir),e
    {{15, 13, 12}, {}, 950, 20, 180},     // r,w,q
};
