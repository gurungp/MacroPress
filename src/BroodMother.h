
#pragma once

#include "InputMonitor.h"
#include "Sequence.h"
#include <Security/cssmconfig.h>

CGEventRef BroodMother(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

static uint8 selectUnits = 0; // 0 BroodMother, 1 All the others

static std::vector<AdvancedButtonPress3> seqBroodSelect1 = {

    {{20}, {}, 20, 20, 20}, // 3
};

static std::vector<AdvancedButtonPress3> seqBroodSelect2 = {

    {{21}, {}, 20, 20, 20}, // 4
};
static std::vector<AdvancedButtonPress3> seqBroodSelect3 = {

    {{9}, {}, 20, 20, 20}, // v (Select All)
};
static std::vector<AdvancedButtonPress3> seqBroodSelect4 = {

    {{9, 200, 20}, {}, 50, 20, 40}, // v (Select All),right click
};
static std::vector<AdvancedButtonPress3> seqBroodSelect5 = {

    {{20, 200}, {}, 50, 20, 40}, // 3 (Select All),right click
};

static std::vector<AdvancedButtonPress3> seqBrood1 = {

    {{19, 1, 15}, {}, 30, 20, 50}, // 2,s,r
};

static std::vector<AdvancedButtonPress3> seqBrood2 = {

    {{19, 1, 0, 15, 12}, {}, 30, 20, 50}, // 2,s,a(manta),r,q
};
static std::vector<AdvancedButtonPress3> seqBrood3 = {

    {{19, 1, 0, 6, 15, 12}, {}, 30, 20, 50}, // 2,s,a(manta),z(BKB),r,q
};
