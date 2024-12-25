

#pragma once

#include "InputMonitor.h"
#include "Sequence.h"

CGEventRef Meepo(const InputMonitor &inputMonitor,
                 const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

static uint16_t currentMeepoIndex = 0;
static uint16_t currentMeepo[] = {20, 23, 22, 26, 28}; // 3,5,6,7,8
static int currentMeepoNum = 1;

static std::vector<AdvancedButtonPress3> seqMeepoGen = {
    {{9}, {}, 100, 20, 100}, // v (Select all)

};

static std::vector<AdvancedButtonPress3> seqMeepo1 = {
    {{12, 48}, {}, 100, 20, 100}, // q, tab
};

static std::vector<AdvancedButtonPress3> seqMeepo2 = {};

static std::vector<AdvancedButtonPress3> seqMeepo2a = {
    {{20, 13, 23, 13, 9}, {}, 100, 20, 90}, // 3,w,5,w,v

};

static std::vector<AdvancedButtonPress3> seqMeepo2b = {

    {{20, 13, 23, 13, 22, 13, 9}, {}, 100, 20, 90}, // 3,w,5,w,6,w,v
};
static std::vector<AdvancedButtonPress3> seqMeepo2c = {

    {{20, 13, 23, 13, 22, 13, 26, 13, 9}, {}, 100, 20, 90}, // 3,w,5,w,6,w,7,w,v
};

static std::vector<AdvancedButtonPress3> seqMeepo2d = {

    {{20, 13, 23, 13, 22, 13, 26, 13, 28, 13, 9}, {}, 100, 20, 90}, // 3,w,5,w,6,w,7,w,8,w,v
};
static std::vector<AdvancedButtonPress3> seqMeepo3 = {};
static std::vector<AdvancedButtonPress3> seqMeepo3a = {
    {{23, 13}, {}, 100, 20, 70},                // 5,w
    {{20, 3, 201, 9, 19, 1}, {}, 350, 20, 100}, // 3, f(Blink),2,s

};
static std::vector<AdvancedButtonPress3> seqMeepo3b = {
    {{23, 13, 22, 13}, {}, 100, 20, 70},        // 5,w,6,w
    {{20, 3, 201, 9, 19, 1}, {}, 500, 20, 100}, // 3, f(Blink),2,s

};
static std::vector<AdvancedButtonPress3> seqMeepo3c = {

    {{23, 13, 22, 13, 26, 13}, {}, 100, 20, 70}, // 5,w,6,w,7,w
    {{20, 3, 201, 9, 19, 1}, {}, 640, 20, 100},  // 3, f(Blink),2,s

};
static std::vector<AdvancedButtonPress3> seqMeepo3d = {
    {{23, 13, 22, 13, 26, 13, 28, 13}, {}, 100, 20, 70}, // 5,w,6,w,7,w,8,w
    {{20, 3, 201, 9, 19, 1}, {}, 780, 20, 100},          // 3, f(Blink),2,s

};

static std::vector<AdvancedButtonPress3> seqMeepo4 = {};
static std::vector<AdvancedButtonPress3> seqMeepo4a = {
    {{20, 3, 201, 19, 1}, {}, 100, 20, 90}, // 3, f(Blink),2,s

    {{23, 13, 9, 0}, {}, 520, 20, 70}, // 5,w,v,a

};
static std::vector<AdvancedButtonPress3> seqMeepo4b = {
    {{20, 3, 201, 19, 1}, {}, 100, 20, 90}, // 3, f(Blink),2,s

    {{23, 13, 22, 13, 9, 0}, {}, 520, 20, 70}, // 5,w,6,w,v,a

};
static std::vector<AdvancedButtonPress3> seqMeepo4c = {
    {{20, 3, 201, 19, 1}, {}, 100, 20, 90}, // 3, f(Blink),2,s

    {{23, 13, 22, 13, 26, 13, 9, 0}, {}, 520, 20, 70}, // 5,w,6,w,7,w,v,a

};
static std::vector<AdvancedButtonPress3> seqMeepo4d = {

    {{20, 3, 201, 19, 1}, {}, 100, 20, 90},                    // 3, f(Blink),2,s
    {{23, 13, 22, 13, 26, 13, 28, 13, 9, 0}, {}, 520, 20, 70}, // 5,w,6,w,7,w,8,w,v,a

};
static std::vector<AdvancedButtonPress3> *meepoSequences1[] = {&seqMeepo2, &seqMeepo2a, &seqMeepo2b, &seqMeepo2c, &seqMeepo2d};

static std::vector<AdvancedButtonPress3> *meepoSequences2[] = {&seqMeepo3, &seqMeepo3a, &seqMeepo3b, &seqMeepo3c, &seqMeepo3d};

static std::vector<AdvancedButtonPress3> *meepoSequences3[] = {&seqMeepo4, &seqMeepo4a, &seqMeepo4b, &seqMeepo4c, &seqMeepo4d};
