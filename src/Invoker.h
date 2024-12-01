#pragma once

#include "InputMonitor.h"
#include "Queue.h"
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
static double TornadoLiftTime = 0;
static int current_InvokeLevel = 0;
static double current_InvokeCD = 7.0; // default CD Time of invoke

static double TornadoLiftTimes[] = {0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6};

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

struct CombinationState {

  int m_numOfQuas = 0;
  int m_numOfWex = 0;
  int m_numOfExort = 0;

  SpellValues m_Slot1 = SpellValues::NoSpell;
  SpellValues m_Slot2 = SpellValues::NoSpell;

  bool checkIfSameCombination(CombinationState cs) {
    if (m_numOfExort == cs.m_numOfExort and m_numOfWex == cs.m_numOfWex and m_numOfQuas == cs.m_numOfQuas) {
      return true;
    } else {
      return false;
    }
  }

  int SpellTotal() {
    return (m_numOfWex * 2) + m_numOfQuas + (m_numOfExort * 30);
  }

  static const char *getSpellName(int val) {
    switch (val) {
    case 0:
      return "No Spell";
    case 6:
      return "EMP";
    case 3:
      return "Cold Snap";
    case 90:
      return "Sun Strike";
    case 4:
      return "Ghost Walk";
    case 32:
      return "Ice Wall";
    case 5:
      return "Tornado";
    case 34:
      return "Alacrity";
    case 61:
      return "Forged Spirits";
    case 62:
      return "Chaos Meteor";
    case 33:
      return "Deafening Blast";
    default:
      return "Undefined Number";
    }
  }
};

static Queue<Orbs> orbsState(3);
// Invoker
CGEventRef Invoker(const InputMonitor &inputMonitor, const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

void printCurrentOrbAndSlotState();
void checkInvokeLevelAndSpellsAvailable();
void updateSequencesTimes();
bool checkAndSetMainCombinationSlot();
void SetCurrentOrbsCount();

static CombinationState mainCombState; // The main combination state to keep track of Slot Spells
static CombinationState currCombState; // Combination State to keep track of current Orbs only

static std::vector<AdvancedButtonPress3> casting;

static std::vector<AdvancedButtonPress3> seqInv_Cnl_attk = {

    {{11, 200}, {}, 70, 20, 50},

};
static std::vector<AdvancedButtonPress3> seqInv1a = {};
static std::vector<AdvancedButtonPress3> seqInv1b = {};
static std::vector<AdvancedButtonPress3> seqInv1c = {};
static std::vector<AdvancedButtonPress3> seqInv1d = {};
static std::vector<AdvancedButtonPress3> seqInv1e = {};
static std::vector<AdvancedButtonPress3> seqInv2a = {};
static std::vector<AdvancedButtonPress3> seqInv2b = {};
static std::vector<AdvancedButtonPress3> seqInv3a = {};
static std::vector<AdvancedButtonPress3> seqInv3b = {};
static std::vector<AdvancedButtonPress3> seqInv4a = {};
static std::vector<AdvancedButtonPress3> seqInv4b = {};

static std::vector<AdvancedButtonPress3> seqInv_test = {};
static std::vector<AdvancedButtonPress3> seqInv_testB = {};
