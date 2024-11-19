#pragma once

#include "InputMonitor.h"
#include "Sequence.h"
#include "Spell.h"
#include <vector>

extern int seqInv_WaitTime;
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
static double TornadoLiftTime = 0;
static int current_InvokeLevel = 0;
static double current_InvokeCD = 7.0; // default CD Time of invoke

static double TornadoLiftTimes[] = {0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6};

struct activeSpell {
  int slot;
  Spell &spell;
};
// Invoker
CGEventRef Invoker(const InputMonitor &inputMonitor,
                   const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

void checkInvokeLevelAndSpellsAvailable();
void updateSequencesTimes();

static std::vector<AdvancedButtonPress2> casting;

static std::vector<AdvancedButtonPress2> seqInv1A = {
    //   {{13}, {}, 140, 20},               // w
    //   {{13}, {}, 270, 20},               // w
    //   {{14, 15}, {}, 370, 20},           // e, r
    //   {{14}, {}, 490, 20},               // e
    //   {{12}, {}, 623, 20},               // q
    //   {{15}, {}, seqInv1A_WaitTime, 20}, // r

};

static std::vector<AdvancedButtonPress2> seqInv1B = {
    //   {{17}, {58}, 140, 20},             // alt + t
    //   {{2}, {}, 270, 20},                // d
    //   {{12}, {}, 370, 20},               // q
    //   {{12}, {}, 470, 20},               // q
    //   {{15}, {}, 580, 20},               // r
    //   {{2}, {}, 690, 20},                // d
    //   {{14}, {}, 800, 20},               // e
    //   {{14}, {}, 915, 20},               // e
    //   {{13}, {}, 1030, 20},              // w
    //   {{15}, {}, seqInv1B_WaitTime, 20}, // r

};

static std::vector<AdvancedButtonPress2> seqInv2A = {
    //   {{13}, {}, 140, 20},               // w
    //   {{13}, {}, 270, 20},               // w
    //   {{13, 15}, {}, 370, 20},           // w, r
    //   {{12}, {}, 490, 20},               // q
    //   {{15}, {}, seqInv2A_WaitTime, 20}, // r

};

static std::vector<AdvancedButtonPress2> seqInv2B = {
    //   {{17}, {}, 140, 20},                          // t
    //   {{2}, {}, 270, 20},                           // d
    //   {{14}, {}, 370, 20},                          // e
    //   {{14}, {}, 490, 20},                          // e
    //   {{14}, {}, 623, 20},                          // e
    //   {{14}, {}, 730, 20},                          // e
    //   {{15}, {}, 850, 20},                          // r
    //   {{2}, {}, seqInv2B_TornadoTime, 20},          // d , casing sunstrike after the TornadoLiftTime
    //   {{12}, {}, (seqInv2B_TornadoTime + 100), 20}, // q
    //   {{12}, {}, (seqInv2B_TornadoTime + 200), 20}, // q
    //   {{15}, {}, (seqInv2B_WaitTime), 20},          // r

};

static std::vector<AdvancedButtonPress2> seqInv3A = {
    //   {{12}, {}, 140, 20},                   // q
    //   {{13}, {}, 270, 20},                   // w
    //   {{13, 15}, {}, 370, 20},               // w, r -> Tornado
    //   {{14}, {}, 490, 20},                   // e
    //   {{14}, {}, 600, 20},                   // e
    //   {{15}, {}, seqInv_WaitTime, 20},       // r -> Chaos Meter
    //   {{12}, {}, seqInv_WaitTime + 110, 20}, // q
    //   {{13}, {}, seqInv_WaitTime + 210, 20}, // w , preparing for  Deafening Blast
};
static std::vector<AdvancedButtonPress2> seqInv3B = {
    //   {{17}, {}, 140, 20},                                                   // t, tornado
    //   {{2}, {}, seqInv3A1_TornadoTime + 400, 20},                            // d, Chaos Meteor, The +400 is accounting for the
    //                                                                          // time taken for Tornado to take affect
    //   {{15}, {}, seqInv3A1_TornadoTime + 400 + 200, 20},                     // r
    //   {{2}, {}, seqInv3A1_TornadoTime + 400 + 1020, 20},                     // d , Deafening Blast
    //   {{13}, {}, seqInv3A1_TornadoTime + 400 + 1140, 20},                    // w
    //   {{14}, {}, seqInv3A1_TornadoTime + 400 + 1260, 20},                    // e
    //   {{15}, {}, seqInv3A1_TornadoTime + seqInv_WaitTime + 400 + 900, 20},   // r
    //   {{2}, {58}, seqInv3A1_TornadoTime + seqInv_WaitTime + 400 + 1020, 20}, // alt + d

};

static std::vector<AdvancedButtonPress2> seqInv4A = {};

static std::vector<AdvancedButtonPress2> seqInv4B = {};
