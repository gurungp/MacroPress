
#pragma once

#include "InputMonitor.h"
#include "Sequence.h"
#include "Spell.h"

CGEventRef ArcWarden(const InputMonitor &inputMonitor,
                     const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

static bool continueCombo = false;

static std::vector<AdvancedButtonPress3> seqArcB1a = {

    {{15}, {}, 100, 20, 50}, // r

};

static std::vector<AdvancedButtonPress3> seqArcB1b = {
    {{23, 14}, {}, 100, 20, 50},    // 5, select clone, e
    {{12, 200}, {56}, 220, 20, 50}, // q,right click
                                    //  {{25},{},240,20,50}, // 9 (Ctrl group 9), select both hero
};
static std::vector<AdvancedButtonPress3> seqArcB2 = {

};

//  Selects main hero and then presses q and e

static std::vector<AdvancedButtonPress3> seqArcB3 = {
    {{20, 12}, {}, 140, 20, 50}, // 3 , q
    {{14, 25}, {}, 350, 20, 50}, // e , 9
};
