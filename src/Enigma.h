

#pragma once

#include "ArcWarden2.h"
#include "InputMonitor.h"
#include "Sequence.h"

CGEventRef Enigma(const InputMonitor &inputMonitor,
                  const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

enum class EnigmaUnits {
  ENIGMA,
  EIDOLON,
  ALL
};

static EnigmaUnits unitSelected = EnigmaUnits::ENIGMA;

static std::vector<AdvancedButtonPress3> seqEnigma1 = {
    {{3, 201, 14, 15}, {}, 30, 20, 40}, // f(Blink), left click,e,r

};

static std::vector<AdvancedButtonPress3> seqEnigma2 = {
    {{3, 201, 14, 6, 15}, {}, 30, 20, 120}, // f(Blink), left click,e,z,r
};
static std::vector<AdvancedButtonPress3> seqEnigma3 = {
    {{3, 201}, {}, 30, 20, 40},               // f(Blink), left click
    {{12, 19, 14, 13, 20}, {}, 240, 20, 100}, // q,2,e,w,3

};

static std::vector<AdvancedButtonPress3> seqEnigma4 = {
    {{3, 201}, {}, 30, 20, 40},          // f(Blink), left click
    {{14, 6, 15}, {}, 240, 20, 100},     // e,z, r
    {{0, 6, 14, 15}, {}, 4592, 20, 100}, // a(refresher),z,e,r
};

static std::vector<AdvancedButtonPress3> selectEnigma1 = {
    {{21, 200, 20}, {}, 10, 20, 30}, // 4,right click,3

};

static std::vector<AdvancedButtonPress3> selectEnigma2 = {
    {{9, 200}, {}, 10, 20, 30}, // v,right click

};

static std::vector<AdvancedButtonPress3> selectEnigma3 = {
    {{9}, {}, 70, 20, 70}, // v

};
static std::vector<AdvancedButtonPress3> selectEnigma4 = {
    {{9}, {}, 400, 20, 60}, // v

};
