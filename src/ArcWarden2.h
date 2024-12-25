

#pragma once

#include "InputMonitor.h"
#include "PlaySound.h"
#include "Sequence.h"
#include "Spell.h"
#include <chrono>

enum ArcWardenUnits {
  ARCWARDEN,
  CLONE,
  BOTH,
  ILLUSIONS,
  CLONE_AND_ILLUSIONS
};
static bool TempestAlive = false;
static bool altR_Combo = false;
static ArcWardenUnits switchHero = ARCWARDEN;   // 0 for main hero , 1 for clone
static ArcWardenUnits selectedUnit = ARCWARDEN; // 0 is Main hero, 1 is the clone,2 is main and clone, 3 is illusions only
                                                // 4 is clone and illusions

static const char *selectedUnitNames[] = {"Main Hero", "Clone", "Main and Clone", "Illusions", "Clone and Illusions"};

CGEventRef ArcWarden2(const InputMonitor &inputMonitor,
                      const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

static std::vector<AdvancedButtonPress3> seqArcGen = {
    {{25}, {}, 20, 20, 20}, // Select Clone and Main Hero

};
static std::vector<AdvancedButtonPress3> seqArcSwitch1a = {
    {{20, 20}, {}, 20, 20, 20}, // Select Main Hero

};
static std::vector<AdvancedButtonPress3> seqArcSwitch1b = {
    {{23, 23}, {}, 20, 20, 20}, // Select Clone

};

static std::vector<AdvancedButtonPress3> seqArcSelectMain = {
    {{20}, {}, 20, 20, 20}, // Select Main Hero

};
static std::vector<AdvancedButtonPress3> Arc1a = {
    {{20, 12, 25, 48}, {}, 20, 20, 30}, // 3,q,9,tab

};
static std::vector<AdvancedButtonPress3> Arc1b = {

    {{23, 12, 25, 48}, {}, 20, 20, 30}, // 5,q,9,tab
};
static std::vector<AdvancedButtonPress3> Arc2a = {
    {{20, 13, 25, 48}, {}, 20, 20, 80}, // 3,w,9,tab

};
static std::vector<AdvancedButtonPress3> Arc2b = {
    {{23, 13, 25, 48}, {}, 20, 20, 80}, // 5,w,9,tab

};
static std::vector<AdvancedButtonPress3> Arc3a = {
    {{20, 14, 25, 48}, {}, 20, 20, 30}, // 3,e,9,tab

};
static std::vector<AdvancedButtonPress3> Arc3b = {
    {{23, 14, 25, 48}, {}, 20, 20, 30}, // 5,e,9,tab

};
static std::vector<AdvancedButtonPress3> seqArc4a = {
    {{15}, {}, 20, 20, 20}, // r (Cast R)

    {{23}, {}, 80, 20, 40}, // 5 (Select Clone)
};

static std::vector<AdvancedButtonPress3> seqArc4b = {
    {{14}, {}, 20, 20, 40},         // e
    {{12, 200}, {56}, 110, 20, 40}, // shift + q, right click
    {{20}, {}, 290, 20, 30},        // 3 , select main hero
};

static std::vector<AdvancedButtonPress3> Arc5 = {
    {{23}, {}, 20, 20, 30},                                         // 5
    {{20}, {56}, 80, 30},                                           // shift + 3 (Adding main hero so that both are selected and clone is focused)
    {{19, 1, 23, 14, 20, 12, 23, 12, 20, 14, 25}, {}, 160, 20, 50}, // 2,s,5,e,3,q,5,q,3,e,9
};

static std::vector<AdvancedButtonPress3> Arc6 = {

    {{25, 48, 13, 0, 20, 0, 25}, {}, 20, 20, 50}, // 9,tab,w,a,3,a,9
};
