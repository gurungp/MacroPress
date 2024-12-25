#pragma once

#include "InputMonitor.h"
#include "Sequence.h"
#include "Spell.h"

// Shadow Fiend
CGEventRef ShadowFiend(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor,
                       CGEventRef &event);

static bool continueCombo = false;
static int castTime = 1280;

// Keyseqeunces
static std::vector<AdvancedButtonPress3> seqSF1 = {
    {{0, 12, 13, 14}, {}, 100, 20, 120}, // a (Silver edge,BKB,Manta,MOM),q,w,e
};
static std::vector<AdvancedButtonPress3> seqSF2 = {
    {{3, 201, 19}, {}, 100, 20, 50}, // f, left click, 2
    {{15}, {}, castTime, 20, 50},    // r
};
static std::vector<AdvancedButtonPress3> seqSF3 = {
    {{3, 201, 6, 19}, {}, 100, 20, 50}, // f, left click,z(BKB,Silver edge),2
    {{15}, {}, castTime, 20, 50},       // r
};
static std::vector<AdvancedButtonPress3> seqSF4 = {
    // adjust for cast animation reduction
    {{3, 201, 6, 19}, {}, 100, 20, 50}, // f, left click, z(BKB,silver edge),2 (hex)
    {{15}, {}, 350, 20, 50},            // r

};
static std::vector<AdvancedButtonPress3> seqSF5 = {
    // adjust for cast animation reduction
    {{3, 201, 19}, {}, 100, 20, 50}, // f, left click, 2(hex)
    {{15}, {}, 350, 20, 50},         // r

};
