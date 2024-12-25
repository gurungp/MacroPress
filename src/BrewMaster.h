#pragma once

#include "InputMonitor.h"
#include "Sequence.h"

CGEventRef BrewMaster(const InputMonitor &inputMonitor,
                      const KeyboardMonitor &keyboardMonitor, CGEventRef &event);
static std::vector<AdvancedButtonPress3> seqBrewGen = {
    {{20}, {}, 100, 20, 60}, // 3
};

static std::vector<AdvancedButtonPress3> seqBrew1 = {
    {{23, 12, 20}, {}, 100, 20, 80}, // 5,q,3
};

static std::vector<AdvancedButtonPress3> seqBrew2a = {
    {{22}, {}, 100, 20, 60},        // 6 (ctrl-grp 6) selects wind
    {{12, 13}, {56}, 290, 20, 110}, // q,w
    {{29}, {}, 630, 20, 60},        //  0(ctrl-grp 0 , selects everyone except wind)

};
static std::vector<AdvancedButtonPress3> seqBrew2b = {
    {{22, 14, 25}, {}, 100, 20, 100}, // 6,e,9(ctrl-grp 9), selects wind and earth for escape
};
static std::vector<AdvancedButtonPress3> seqBrew2c = {
    {{39}, {}, 100, 20, 100}, // '(ctrl-grp '), selects Void and Fire
};

static std::vector<AdvancedButtonPress3> seqBrew3 = {

    {{28}, {}, 100, 20, 60}, // 8

    {{12}, {56}, 230, 20, 660}, // q

    {{200}, {56}, 1030, 20, 60}, // right click,
    {{41}, {}, 1260, 20, 60},    //;(ctrl-grp ; , selects everyone except void)

};
static std::vector<AdvancedButtonPress3> seqBrew4 = {
    {{3, 201}, {}, 100, 20, 100},    // f(Blink), left click
    {{19, 1, 13}, {}, 432, 20, 100}, // 2, s, w

};
static std::vector<AdvancedButtonPress3> seqBrew5 = {
    {{3, 201}, {}, 100, 20, 100},       // f(Blink), left click
    {{19, 1, 6, 13}, {}, 432, 20, 100}, // 2, s, z(BKB),w
};
