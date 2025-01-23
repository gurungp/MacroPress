#pragma once

#include "InputMonitor.h"
#include "Sequence.h"
#include "Spell.h"
#include <vector>

extern int seqInv_WaitTime;
extern int seqInv_TornadoTime;
extern int seqInv2B_TornadoTime;
extern int seqInv3A1_TornadoTime;

static bool Set_Alacrity = false;
static bool Set_ForgedSpirits = false;
static bool Set_EMP = false;
static bool Set_Tornado = false;
static bool Set_ChaosMeteor = false;
static bool Set_DeafeningBlast = false;

static int SunStrikeDelay = 1700;   // ms
static int ChaosMeteorDelay = 1300; // ms
static double TornadoHitTime = 500; // ms
static double TornadoLiftTime = 0;
static int current_InvokeLevel = 0;
static double current_InvokeCD = 7.0; // default CD Time of invoke

static double TornadoLiftTimes[] = {0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.4};

enum Orbs {
  NoOrb = 0,
  Qs = 1,  // Quas
  Wx = 2,  // Wex
  Et = 30, // Exort
};
enum class SpellValues : int {
  NoSpell = 0,
  ColdSnap = Qs + Qs + Qs,       // 3
  EMP = Wx + Wx + Wx,            // 6
  SunStrike = Et + Et + Et,      // 90
  GhostWalk = Qs + Qs + Wx,      // 4
  IceWall = Qs + Qs + Et,        // 32
  Tornado = Wx + Wx + Qs,        // 5
  Alacrity = Wx + Wx + Et,       // 34
  ForgedSpirts = Et + Et + Qs,   // 61
  ChaosMeteor = Et + Et + Wx,    // 62
  DeafeningBlast = Qs + Wx + Et, // 33

};
static SpellValues setTornadoDelaySpell = SpellValues::NoSpell;

struct pressModerator {
  bool pressed = false;
  std::chrono::time_point<std::chrono::system_clock> lastPressedTime;
};

static void (*castingFunc)() = NULL;
static void altQcasting();
static void altQprep();

static void altWcasting();
static void altWprep();

static void altEcasting();
static void altEprep();

static void alt2casting();
static void alt2prep();

static void alt3casting();
static void alt3prep();

static void alt4casting();
static void alt4prep();

// Invoker
CGEventRef Invoker(const InputMonitor &inputMonitor, const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

void updateSequencesTimes();
static std::vector<AdvancedButtonPress3> seqInv4b = {};

static std::vector<AdvancedButtonPress3> seqInvSelectAll = {
    {{9}, {}, 10, 20, 50}, // v

};

static std::vector<AdvancedButtonPress3> seqInvPressD = {
    {{2}, {}, 10, 20, 50}, // d

};
static std::vector<AdvancedButtonPress3> seqInvPressT = {
    {{17}, {}, 10, 20, 50}, // t

};
static std::vector<AdvancedButtonPress3> seqInvPressTD = {
    {{17, 2}, {}, 10, 10, 80}, // t d

};
static std::vector<AdvancedButtonPress3> seqInvPressDT = {
    {{2, 17}, {}, 10, 10, 80}, // d t

};

static std::vector<AdvancedButtonPress3> seqInvPressR = {
    {{15}, {}, 10, 10, 40}, // r

};
static std::vector<AdvancedButtonPress3> seqInvPressAltT = {
    {{17}, {58}, 10, 10, 40}, // alt+t

};

static std::vector<AdvancedButtonPress3> seqInvPress2 = {
    {{19}, {}, 10, 10, 50}, // 2

};

static std::vector<AdvancedButtonPress3> seqInvPressS = {
    {{1}, {}, 10, 10, 50}, // s

};

static std::vector<AdvancedButtonPress3> SunStrikePrep = {
    {{14, 14, 14}, {}, 10, 20, 30},
};
static std::vector<AdvancedButtonPress3> ColdSnapPrep = {

    {{12, 12, 12}, {}, 10, 20, 30}, // q,q,q

};
static std::vector<AdvancedButtonPress3> EMPPrep = {

    {{13, 13, 13}, {}, 10, 20, 30}, // w,w,w

};

static std::vector<AdvancedButtonPress3> ChaosMeteorPrep = {

    {{13, 14, 14}, {}, 10, 20, 30}, // w,e,e -> Chaos Meteor
};
static std::vector<AdvancedButtonPress3> seqInvAlacrity = {
    {{13, 13, 14, 15}, {}, 10, 20, 30}, // w,w,e,r -> Alacrity
};
static std::vector<AdvancedButtonPress3> seqInvForgedSpirits = {
    {{14, 14, 12, 15}, {}, 10, 20, 30}, // e,e,q,r -> Forged Spirits
};
static std::vector<AdvancedButtonPress3> seqInvColdSnap = {

    {{12, 12, 12, 15}, {}, 10, 20, 30}, // q,q,q,r

};
static std::vector<AdvancedButtonPress3> seqGhostWalk = {};
static std::vector<AdvancedButtonPress3> seqInvDeafeningBlast = {

    {{13, 14, 12, 15}, {}, 10, 20, 30}, // w,e,q,r
};
static std::vector<AdvancedButtonPress3> seqInvSunStrike = {
    {{14, 14, 14, 15}, {}, 10, 20, 30},
};
static std::vector<AdvancedButtonPress3> seqInvTornado = {

    {{13, 13, 12, 15}, {}, 10, 20, 30}, // w,w,q,r -> Tornado
};
static std::vector<AdvancedButtonPress3> seqInvChaosMeteor = {

    {{13, 14, 14, 15}, {}, 10, 20, 30}, // w,e,e,r -> Chaos Meteor
};
static std::vector<AdvancedButtonPress3> seqInvIceWall = {};
static std::vector<AdvancedButtonPress3> seqInvEMP = {

    {{13, 13, 13, 15}, {}, 10, 20, 30}, // w,w,w,r
};

static std::vector<AdvancedButtonPress3> seqInv1ExecuteA = {};
static std::vector<AdvancedButtonPress3> seqInv1ExecuteB = {};
