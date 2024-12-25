
#pragma once

#include "AdvancedKeyboardSimulator.h"
#include "InputMonitor.h"
#include "PlaySound.h"
#include "Sequence.h"
// Lone Druid
CGEventRef LoneDruid(const InputMonitor &inputMonitor,
                     const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

enum LD_Unit {
  DRUID,
  BEAR,
  BOTH
};

static LD_Unit currentUnit = DRUID; // 0 is Druid, 1 is Bear,2 both selected
// Key sequence for Lone Druid

static std::vector<AdvancedButtonPress3> seqDruidGen1 = {
    {{25}, {}, 50, 20, 40}, // Select Clone and Main Hero (9 Ctrl Group 9), primary selection
                            // is Druid

};
static std::vector<AdvancedButtonPress3> seqDruidGen2 = {
    {{22, 48, 200}, {}, 20, 20, 20}, // 6 ctrl group 6 , tab, right click,selects druid and bear and bear is primary selection
};

static std::vector<AdvancedButtonPress3> seqDruidGen3 = {

    {{23, 200, 20}, {}, 20, 20, 20}, // select bear , then right click, then 3
};
static std::vector<AdvancedButtonPress3> seqLD1A = {
    {{23, 17, 20}, {}, 50, 20, 40}, // 5,t,3
};

static std::vector<AdvancedButtonPress3> seqLD2a = {

    {{23, 0, 201, 22, 48}, {}, 20, 20, 20}, // 5 + a + left click + 6 + tab

};
static std::vector<AdvancedButtonPress3> seqLD2b = {

    {{23, 19, 22, 48}, {}, 20, 20, 20}, // 5 + 2 + 6 + tab

};

static std::vector<AdvancedButtonPress3> seqLD3 = {

    {{23}, {}, 20, 20, 20}, // 5

    {{0, 201, 1, 19, 200}, {56}, 80, 20, 50}, // shift + a,left click, s , 2 , right click

    //   {{1, 19, 200}, {56}, 650, 100}, // shift + s + 2 + right click
    {{20}, {}, 450, 20, 30}, // 3

    //  {{23}, {}, 140, 40},       // 5
    //  {{0, 201}, {56}, 300, 40}, // shift + a + left click

    //  {{1, 19}, {56}, 450, 40}, // shift + s + 2
    //  {{200}, {56}, 600, 40},   // shift + right click
    //  {{20}, {}, 720, 40},      // 3

};
static std::vector<AdvancedButtonPress3> seqLD4 = {
    {{23, 0, 201}, {}, 20, 20, 20},                         // 5+a+left click
    {{11, 6, 11, 19, 19, 1, 200, 22, 48}, {}, 170, 20, 80}, // b(cancel) + z +b  +2+ 2 + s + right click + 6

};
