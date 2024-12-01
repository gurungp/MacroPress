

#pragma once

#include "Invoker.h"
#include "PlaySound.h"
#include "Queue.h"
#include "Sequence.h"
#include "Spell.h"
#include "button_key_States.h"
#include <cstddef>

static Spell Blink{15.45};
static Spell Quas{0, 1, 2, 3, 4, 5, 6, 7, 8};
static Spell Wex{0, 1, 2, 3, 4, 5, 6, 7, 8};
static Spell Exort{0, 1, 2, 3, 4, 5, 6, 7, 8};

static Spell InvokeSpell{6.95, 6.65, 6.35, 6.05, 5.75, 5.45, 5.15, 4.85,
                         4.55, 4.25, 3.95, 3.65, 3.35, 3.05, 2.75,
                         2.45, 2.15, 1.85, 1.55, 1.25, 0.95};
static Spell IceWall{23.45};
static Spell EMP{27.45};
static Spell Alacrity({15.45});
static Spell ForgedSpirits{27.45};
static Spell ChaosMeter{50.45};
static Spell DeafeningBlast{36.45};
static Spell ColdSnap{18.45};
static Spell GhostWalk{32.45};
static Spell SunStrike{23.45};
static Spell Tornado{27.0};

int seqInv_WaitTime;       // default global Wait time for invoke spell
int seqInv_TornadoTime;    // default global tornado wait time
int seqInv2B_TornadoTime;  // = (int)((TornadoLiftTime * 1000) + 865);            // 865 is the offset from where it begins
int seqInv3A1_WaitTime;    // = (int)((InvokeSpell.m_cooldown * 1000) + 370 + 330); // 370 + (600-270), and this is the offset
int seqInv3A1_TornadoTime; // = (int)((TornadoLiftTime * 1000) + 140);

PlaySound soundPlayer;
// Invoker
CGEventRef
Invoker(const InputMonitor &inputMonitor,
        const KeyboardMonitor &keyboardMonitor,
        CGEventRef &event) { // this event is the same from the
                             // eventCallBack of main.cpp

  // alt + right click
  //  if (keyboardMonitor.isAltKeyPressed() && inputMonitor.isRightClicked()) {
  //    // std::cout << "alt and right click" << std::endl;
  //    // to avoid alt modifier to linger when the sequence of presses
  //    // are being executed
  //    avoidModifierKey(event, kCGEventFlagMaskAlternate); // avoid or unpress
  //    // Alt modifier key

  //
  //    runSequence(seqLC1);
  //    return nullptr; // return nullptr or null event to avoid the click being
  //                    // processed as
  //    // the click will be done in the runSequence
  //  }
  //
  // alt + e
  //
  //

  // LEARNING
  if (keyStates[kVK_ANSI_P].state) {
    Quas.learnSpell(nullptr);
    if (Quas.m_spellLevel >= 8)
      TornadoLiftTime = TornadoLiftTimes[8];
    else
      TornadoLiftTime = TornadoLiftTimes[Quas.m_spellLevel];

    if (ColdSnap.m_spellLevel == 0)
      ColdSnap.learnSpell(nullptr);

    checkInvokeLevelAndSpellsAvailable();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_L].state) {
    Wex.learnSpell(nullptr);

    if (EMP.m_spellLevel == 0)
      EMP.learnSpell(nullptr);

    checkInvokeLevelAndSpellsAvailable();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_K].state) {
    Exort.learnSpell(nullptr);

    if (SunStrike.m_spellLevel == 0)
      SunStrike.learnSpell(nullptr);

    checkInvokeLevelAndSpellsAvailable();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_I].state and keyboardMonitor.isAltKeyPressed()) {
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      ColdSnap.useTalent(5.0);
      //  checkInvokeLevelAndSpellsAvailable();
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_I].state) {

    Tornado.useTalent(4.0);
    //  checkInvokeLevelAndSpellsAvailable();
    return nullptr;
  }

  // UNSET OCTARINE
  if (keyStates[kVK_ANSI_O].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Quas.m_spellLevel > 0 && Wex.m_spellLevel > 0 and Exort.m_spellLevel > 0) {

        soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Octarine Off.mp3");
        IceWall.setOctarine(false);
        EMP.setOctarine(false);
        SunStrike.setOctarine(false);
        Tornado.setOctarine(false);
        Alacrity.setOctarine(false);
        ForgedSpirits.setOctarine(false);
        DeafeningBlast.setOctarine(false);
        ChaosMeter.setOctarine(false);
        ColdSnap.setOctarine(false);
        GhostWalk.setOctarine(false);

        for (int i = 0; i < InvokeSpell.m_spellCDTimes.size(); i++)
        // To Reverse it we first Subtract the added time and then only Set Octarine to false
        {
          InvokeSpell.m_spellCDTimes[i] = InvokeSpell.m_spellCDTimes[i] - 0.065;
        }

        InvokeSpell.setOctarine(false);
        updateSequencesTimes();
      }
    });
    t.detach();

    return nullptr;
  }
  // SET OCTARINE
  if (keyStates[kVK_ANSI_O].state) {
    // Temp Function
    printCurrentOrbAndSlotState();
    if (Quas.m_spellLevel > 0 && Wex.m_spellLevel > 0 and Exort.m_spellLevel > 0) {

      soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Octarine On.mp3");
      IceWall.setOctarine(true);
      EMP.setOctarine(true);
      SunStrike.setOctarine(true);
      Tornado.setOctarine(true);
      Alacrity.setOctarine(true);
      ForgedSpirits.setOctarine(true);
      DeafeningBlast.setOctarine(true);
      ChaosMeter.setOctarine(true);
      ColdSnap.setOctarine(true);
      GhostWalk.setOctarine(true);
      InvokeSpell.setOctarine(true);

      for (int i = 0; i < InvokeSpell.m_spellCDTimes.size(); i++)
      // Manually adding few milliseconds because just setting Octarine will correctly determine
      // the cooldown, but practical there are some delays or precedence
      {
        InvokeSpell.m_spellCDTimes[i] = InvokeSpell.m_spellCDTimes[i] + 0.065;
      }
      updateSequencesTimes();
    }
    return nullptr;
  }

  // CANCEL ATTACK
  //  if (keyStates[kVK_ANSI_C].state) {
  //    CGEventSetType(event, kCGEventKeyUp);
  //
  //    std::thread t([] {
  //      while (keyStates[kVK_ANSI_C].state) { // until alt is released, don't run the sequence
  //      }
  //      runSequence3(seqInv_Cnl_attk);
  //    });
  //    t.detach();
  //
  //    return nullptr;
  //  }

  // Prepare Combo 1
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    updateSequencesTimes();
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Alacrity.onCoolDown() or ForgedSpirits.onCoolDown() or InvokeSpell.onCoolDown()) {
        soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        Set_Alacrity = true;
        Set_ForgedSpirits = true;

        if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 && Exort.m_spellLevel > 0) {

          //          InvokeSpell.castSpell(nullptr);
          runSequence3(seqInv1a);
          casting = seqInv1b;
        }
      }
    });
    t.detach();

    return nullptr;
  }
  // Prepare Combo 4B
  if (keyStates[kVK_ANSI_4].state && keyboardMonitor.isAltKeyPressed()) {

    updateSequencesTimes();
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 && Exort.m_spellLevel > 0) {

        runSequence3(seqInv4a);
        ChaosMeter.castSpell(nullptr);
        EMP.castSpell(nullptr);

        casting = seqInv4b;
      }
    });
    t.detach();

    return nullptr;
  }
  // Prepare Combo 2
  if (keyStates[kVK_ANSI_W].state && keyboardMonitor.isAltKeyPressed()) {
    CGEventSetType(event, kCGEventKeyUp);

    updateSequencesTimes();
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (EMP.onCoolDown() or Tornado.onCoolDown() or InvokeSpell.onCoolDown()) {
        soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        Set_EMP = true;
        Set_Tornado = true;

        if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0) {
          // InvokeSpell.castSpell(nullptr);
          std::cout << "Invoke Spell on Cooldown: " << InvokeSpell.onCoolDown() << std::endl;
          runSequence3(seqInv2a);
          casting = seqInv2b;
        }
      }
    });
    t.detach();

    return nullptr;
  }
  // Prepare Combo 3
  if (keyStates[kVK_ANSI_3].state && keyboardMonitor.isAltKeyPressed()) {
    CGEventSetType(event, kCGEventKeyUp);

    updateSequencesTimes();
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (ChaosMeter.onCoolDown() or Tornado.onCoolDown() or InvokeSpell.onCoolDown()) {
        soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        Set_ChaosMeteor = true;
        Set_Tornado = true;
        Set_DeafeningBlast = true;
        std::cout << "The calculated press r after time " << seqInv3A1_WaitTime << " ms" << std::endl;

        if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 and Exort.m_spellLevel > 0) {
          // InvokeSpell.castSpell(nullptr);
          std::cout << "Invoke Spell on Cooldown: " << InvokeSpell.onCoolDown() << std::endl;
          runSequence3(seqInv3a);
          casting = seqInv3b;
        }
      }
    });
    t.detach();

    return nullptr;
  }

  // TESTING NEW WAY
  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {

    updateSequencesTimes();
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Quas.m_spellLevel > 0 && Exort.m_spellLevel > 0) {
        if (Wex.m_spellLevel > 0)
          runSequence3(seqInv1d);
        else
          runSequence3(seqInv1c);
      }
      casting = seqInv1e;
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_X].state && keyboardMonitor.isAltKeyPressed()) {

    updateSequencesTimes();
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 && Exort.m_spellLevel > 0) {
        runSequence3(seqInv_testB);
      }
    });
    t.detach();

    return nullptr;
  }

  // Execute Spell Combo and Set Second Stage of Combo
  if (keyStates[kVK_ANSI_R].state && keyboardMonitor.isAltKeyPressed()) {

    updateSequencesTimes();
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      bool InvokeCD = InvokeSpell.onCoolDown();
      std::cout << "InvokeSpell.onCoolDown() " << InvokeCD << std::endl;
      if (InvokeCD) {
        std::cout << "Invoke on Cooldown" << std::endl;
        soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        if (!casting.empty()) {
          // InvokeSpell.castSpell(nullptr);
          runSequence3(casting);
        } else {
          std::cout << "Casting not set" << std::endl;
        }
      }

      if (Set_Alacrity) {
        Alacrity.castSpell(nullptr);
        Set_Alacrity = false;
      }
      if (Set_ForgedSpirits) {
        ForgedSpirits.castSpell(nullptr);
        Set_ForgedSpirits = false;
      }
      if (Set_EMP) {
        EMP.castSpell(nullptr);
        Set_EMP = false;
      }
      if (Set_Tornado) {
        Tornado.castSpell(nullptr);
        Set_Tornado = false;
      }
      if (Set_ChaosMeteor) {
        ChaosMeter.castSpell(nullptr);
        Set_ChaosMeteor = false;
      }
      if (Set_DeafeningBlast) {
        DeafeningBlast.castSpell(nullptr);
        Set_DeafeningBlast = false;
      }
    });
    t.detach();

    return nullptr;
  }

  // CAST Invoke
  if (keyStates[kVK_ANSI_R].state) {

    updateSequencesTimes();
    if (!InvokeSpell.onCoolDown())
      if (!checkAndSetMainCombinationSlot())
        return nullptr;

    if (!InvokeSpell.onCoolDown()) {
      InvokeSpell.castSpell(nullptr);
    } else
      soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
    return nullptr;
  }

  // SETTING Orbs

  if (keyStates[kVK_ANSI_Q].state) {
    if (Quas.m_spellLevel > 0) {
      orbsState.enqueue(Qs);
      SetCurrentOrbsCount();
    }
    return nullptr;
  }
  if (keyStates[kVK_ANSI_W].state) {
    if (Wex.m_spellLevel > 0) {
      orbsState.enqueue(Wx);
      SetCurrentOrbsCount();
    }
    return nullptr;
  }
  if (keyStates[kVK_ANSI_E].state) {
    if (Exort.m_spellLevel > 0) {
      orbsState.enqueue(Et);
      SetCurrentOrbsCount();
    }
    return nullptr;
  }

  // USING REFRESHER
  if (keyStates[kVK_ANSI_0].state) {
    soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Refresher on.mp3");
    InvokeSpell.useRefresher();
    IceWall.useRefresher();
    Tornado.useRefresher();
    EMP.useRefresher();
    Alacrity.useRefresher();
    DeafeningBlast.useRefresher();
    ForgedSpirits.useRefresher();
    ChaosMeter.useRefresher();
    SunStrike.useRefresher();
    ColdSnap.useRefresher();
    GhostWalk.useRefresher();
  }
  //-----------------------------------------TESTING---------------------------------------

  //-------------------------------------------------END-TESTING--------------------------------------
  return nullptr;
}

void checkInvokeLevelAndSpellsAvailable() {

  static bool qw = false;
  static bool qe = false;
  static bool ew = false;
  static bool qwe = false;

  // LEARN SPELLS WHERE POSSIBLE
  if (InvokeSpell.m_spellLevel > 20) {

  } else {

    InvokeSpell.learnSpell(nullptr);
  }

  if (!qw) {
    if (Quas.m_spellLevel > 0 && Wex.m_spellLevel > 0) {
      GhostWalk.learnSpell(nullptr);
      Tornado.learnSpell(nullptr);
      qw = true;
    }
  }

  if (!qe) {
    if (Quas.m_spellLevel > 0 and Exort.m_spellLevel > 0) {
      IceWall.learnSpell(nullptr);
      ForgedSpirits.learnSpell(nullptr);
      qe = true;
    }
  }

  if (!ew) {
    if (Wex.m_spellLevel > 0 and Exort.m_spellLevel > 0) {
      Alacrity.learnSpell(nullptr);
      ChaosMeter.learnSpell(nullptr);
      ew = true;
    }
  }

  if (!qwe) {
    if (Quas.m_spellLevel > 0 && Wex.m_spellLevel > 0 && Exort.m_spellLevel > 0) {
      DeafeningBlast.learnSpell(nullptr);
      qwe = true;
    }
  }
  std::cout << "Current Quas Level is " << Quas.m_spellLevel << std::endl;
  std::cout << "Current Wex Level is " << Wex.m_spellLevel << std::endl;
  std::cout << "Current Exort Level is " << Exort.m_spellLevel << std::endl;
  std::cout << "Current Invoke Level is " << InvokeSpell.m_spellLevel << " and Cooldown is " << InvokeSpell.m_cooldown << std::endl;
  std::cout << "Current IceWall Level is " << IceWall.m_spellLevel << " and Cooldown is " << IceWall.m_cooldown << std::endl;
  std::cout << "Current SunStrike Level is " << SunStrike.m_spellLevel << " and Cooldown is " << SunStrike.m_cooldown << std::endl;
  std::cout << "Current ColdSnap Level is " << ColdSnap.m_spellLevel << " and Cooldown is " << ColdSnap.m_cooldown << std::endl;
  std::cout << "Current Chaos Meter Level is " << ChaosMeter.m_spellLevel << " and Cooldown is " << ChaosMeter.m_cooldown << std::endl;
  std::cout << "Current EMP Level is " << EMP.m_spellLevel << " and Cooldown is " << EMP.m_cooldown << std::endl;
  std::cout << "Current Deafening Blast Level is " << DeafeningBlast.m_spellLevel << " and Cooldown is " << IceWall.m_cooldown << std::endl;
  std::cout << "Current Alacrity Level is " << Alacrity.m_spellLevel << " and Cooldown is " << Alacrity.m_cooldown << std::endl;
  std::cout << "Current Forged Spirits Level is " << ForgedSpirits.m_spellLevel << " and Cooldown is " << ForgedSpirits.m_cooldown << std::endl;
  std::cout << "Current Ghost Walk Level is " << GhostWalk.m_spellLevel << " and Cooldown is " << GhostWalk.m_cooldown << std::endl;
  std::cout << "Current Tornado Level is " << Tornado.m_spellLevel << " and Cooldown is " << Tornado.m_cooldown << std::endl;

  // UPDATE ALL THE SEQUENCES WITH CORRECT TIMES

  updateSequencesTimes();
}

void updateSequencesTimes() {

  TornadoLiftTime = TornadoLiftTimes[Quas.m_spellLevel];
  if (TornadoLiftTime <= 1.7)
    TornadoLiftTime = 1.8;

  const char *spell1 = mainCombState.getSpellName(static_cast<int>(mainCombState.m_Slot1));

  const char *spell2 = mainCombState.getSpellName(static_cast<int>(mainCombState.m_Slot2));

  std::cout << "Slot 1 Spell : " << spell1 << std::endl;
  std::cout << "Slot 2 Spell : " << spell2 << std::endl;

  if (mainCombState.m_Slot1 == SpellValues::ChaosMeteor || mainCombState.m_Slot2 == SpellValues::ChaosMeteor) {

    seqInv_TornadoTime = (int)((TornadoLiftTime * 1000) - (ChaosMeteorDelay)); // Add the offset in the sequence not here

    std::cout << "Tornado wait time is " << seqInv_TornadoTime << " Chaos Meteor on the slot" << std::endl;
  } else {

    seqInv_TornadoTime = (int)((TornadoLiftTime * 1000) - (SunStrikeDelay)); // Add the offset in the sequence not here

    std::cout << "Tornado wait time is " << seqInv_TornadoTime << " Sun Strike on the slot" << std::endl;
  }
  seqInv2B_TornadoTime = (int)((TornadoLiftTime * 1000) + 865 - (SunStrikeDelay));
  seqInv3A1_TornadoTime = (int)((TornadoLiftTime * 1000) + 140 - (ChaosMeteorDelay));

  // To prevent seqInv2B and others have early cast time of 'r' at the end of the combo
  if (InvokeSpell.m_cooldown <= 1.3) {
    seqInv_WaitTime = (int)((1.3) * 1000); // no offset here because its directly placed on the
                                           // corresponding key sequnce
    // Note: Since 1.3 is set , the cast time should be adjusted in the key sequences
  } else {
    seqInv_WaitTime = (int)((InvokeSpell.m_cooldown) * 1000);
  }
  // if wait time is lower maintain it

  seqInv1a = {
      {{13, 13, 14, 15}, {}, 100, 20, 50},           // w,w,e,r -> Alacrity
      {{14, 12}, {}, 350, 20, 50},                   // e, q
      {{15}, {}, seqInv_WaitTime + 320, 20, 40},     // r -> Forged Spirits
      {{12, 12}, {}, seqInv_WaitTime + 420, 20, 40}, // q, q , preparing for next
  };

  seqInv1b = {
      {{17}, {58}, 100, 20, 20},                    // alt+t
      {{2}, {}, 240, 20, 20},                       // d
      {{15, 19}, {}, 350, 20, 50},                  // r, 2 (Hex)
      {{2, 14, 14, 13}, {}, 460, 20, 50},           // d,(cold snap), e,e,w
      {{15, 1}, {}, seqInv_WaitTime + 580, 20, 20}, // r (chaos meteor) , s (Silence)
  };

  seqInv1c = {
      {{13, 13, 12, 15}, {}, 100, 20, 50},                   // w w q r
      {{12, 12}, {}, 400, 20, 50},                           // q, q
      {{15, 14, 14, 14}, {}, seqInv_WaitTime + 500, 20, 50}, // r, e,e,e
  };
  seqInv1d = {
      {{13, 13, 12, 15}, {}, 100, 20, 50},                   // w w q r
      {{12, 12}, {}, 400, 20, 50},                           // q, q
      {{15, 14, 14, 14}, {}, seqInv_WaitTime + 500, 20, 50}, // r, e,e,e
  };
  seqInv1e = {
      {{17, 2, 15}, {}, 100, 20, 50},              // t d r
      {{2}, {}, seqInv_TornadoTime + 720, 20, 50}, // d

  };

  seqInv2a = {
      {{12, 13, 13, 15}, {}, 110, 20, 50},               // q,w,w,r (Tornado)
      {{13, 13}, {}, 480, 20, 30},                       // w,w,
      {{15}, {}, seqInv_WaitTime + 320, 20, 50},         // r (EMP)
      {{14, 14, 14}, {}, seqInv_WaitTime + 400, 20, 30}, // e,e,e  prepare for Sun Strike

  };

  seqInv2b = {
      {{17, 2, 15}, {}, 110, 20, 50},                                      // d (Tornado), t (EMP), r
      {{2}, {}, seqInv_TornadoTime + 380 + 300, 20, 50},                   // d (Sun Strike) +300 for time take for tornado to hit
      {{2, 12, 12, 12}, {}, seqInv_TornadoTime + 270 + 300, 20, 50},       // d,q,q,q
      {{15, 2}, {}, (seqInv_WaitTime) + seqInv_TornadoTime + 260, 20, 50}, // r, d, (Cold Snap)

  };

  seqInv3a = {
      {{12, 13, 13, 15}, {}, 110, 20, 50},           // q,w,w,r (Tornado)
      {{13, 13}, {}, 480, 20, 30},                   // w,w,
      {{15}, {}, seqInv_WaitTime + 320, 20, 50},     // r (EMP)
      {{14, 14}, {}, seqInv_WaitTime + 400, 20, 30}, // e,e prepare for Chaos Meteor

  };

  seqInv3b = {
      {{17, 2, 15}, {}, 110, 20, 50},                                                   // d (Tornado), t (EMP), r
      {{2, 13, 12}, {}, seqInv_TornadoTime + 520 + 300, 20, 50},                        // d (Chaos Meteor),w,q, +300 for time take for tornado to hit
      {{15, 2}, {}, seqInv_WaitTime + seqInv_TornadoTime + 200, 20, 105},               // r, d, (Deafening Blast)
                                                                                        //
      {{12, 12, 12, 15}, {}, seqInv_TornadoTime + (seqInv_WaitTime * 2) + 200, 20, 50}, // q,q,q,r, Preparing ColdSnap

  };

  seqInv4a = {
      {{13, 13, 13, 15}, {}, 100, 20, 50},      // w,w,w,,r (EMP)
      {{14, 14}, {}, 400, 20, 30},              // e,e
      {{15}, {}, seqInv_WaitTime + 400, 20, 30} // r (Chaos Meteor)

  };
  seqInv4b = {
      {{3, 201}, {}, 100, 20, 40},                                     // f(Blink),left click
      {{19, 17, 2}, {}, 250, 20, 50},                                  // 2(Hex) , t(EMP), d(Chaos Meteor)
      {{6, 2, 17, 13, 12}, {}, 1320, 20, 50},                          // z(Refresher), d(Chaos Meteor), t(EMP), w, q
      {{15, 14, 2}, {}, 2000, 20, 50},                                 // , r(Deafening Blast), e,d(Deafening Blast)
      {{19, 14, 14}, {}, seqInv_WaitTime + 2150, 20, 50},              // 2(Hex), e,e,
      {{15}, {}, (seqInv_WaitTime * 2) + 2150, 20, 50},                // r (Cataclysm),q,q,q
      {{2}, {58}, (seqInv_WaitTime * 2) + 2200, 20, 50},               // alt+d Cataclysm
      {{12, 12, 12, 15, 2}, {}, (seqInv_WaitTime * 3) + 2450, 20, 50}, // r, d(Cold Snap)
                                                                       //

  };

  seqInv_test = {
      {{13, 13, 12, 15}, {}, 100, 20, 50},                   // w w q r
      {{12, 12}, {}, 400, 20, 50},                           // q, q
      {{15, 14, 14, 14}, {}, seqInv_WaitTime + 500, 20, 50}, // r, e,e,e
  };

  seqInv_testB = {
      {{17, 2, 15}, {}, 100, 20, 50},              // t d r
      {{2}, {}, seqInv_TornadoTime + 720, 20, 50}, // d

  };

  std::cout << "InvokeSpell.m_cooldown : " << InvokeSpell.m_cooldown << std::endl;
  std::cout << "seqInv2B_TornadoTime: " << seqInv2B_TornadoTime << std::endl;
  std::cout << "seqInv3A1_TornadoTime " << (seqInv3A1_TornadoTime) << std::endl;
}

void SetCurrentOrbsCount() {

  if (!orbsState.full()) {
    std::cout << "Orbs are not completely filled " << std::endl;
    return;
  }

  // count current number of q,w and e
  int cur_q = 0;
  int cur_w = 0;
  int cur_e = 0;

  for (int i = 0; i < orbsState.size; i++) {
    Orbs temp = orbsState[i];
    if (temp == Qs)
      cur_q++;
    else if (temp == Wx)
      cur_w++;
    else if (temp == Et)
      cur_e++;
    else {
    }
  }

  currCombState.m_numOfQuas = cur_q;
  currCombState.m_numOfWex = cur_w;
  currCombState.m_numOfExort = cur_e;
}

bool checkAndSetMainCombinationSlot() {

  if (!orbsState.full()) {
    std::cout << "Orbs are not filled yet " << std::endl;
    return false;
  }

  if (mainCombState.checkIfSameCombination(currCombState)) {
    // if the main State and the current Quas,Wex,Exort combination are the same return false
    std::cout << "Same Combination " << std::endl;
    return false;
  } else {

    mainCombState.m_numOfQuas = currCombState.m_numOfQuas;
    mainCombState.m_numOfWex = currCombState.m_numOfWex;
    mainCombState.m_numOfExort = currCombState.m_numOfExort;

    int CurrentSpell = mainCombState.SpellTotal();
    SpellValues currentSpell = static_cast<SpellValues>(CurrentSpell);
    if (mainCombState.m_Slot1 == currentSpell) {

      return false;
    } else if (mainCombState.m_Slot2 == currentSpell) {
      // Swap the Spell
      SpellValues tempSpell = mainCombState.m_Slot1;
      mainCombState.m_Slot1 = currentSpell;
      mainCombState.m_Slot2 = tempSpell;
      return false;
    } else { // Set the spell in Slot 1 and if Slot 1 already Occupied then move it to Slot 2 and
             // Set Current in Slot 1
      if (mainCombState.m_Slot1 == SpellValues::NoSpell) {
        mainCombState.m_Slot1 = currentSpell;
      } else {

        mainCombState.m_Slot2 = mainCombState.m_Slot1;
        mainCombState.m_Slot1 = currentSpell;
      }
      return true;
    }
  }
}

void printCurrentOrbAndSlotState() {
  std::cout << "Current Number of Quas : " << currCombState.m_numOfQuas << std::endl;
  std::cout << "Current Number of Wex : " << currCombState.m_numOfWex << std::endl;
  std::cout << "Current Number of Exort : " << currCombState.m_numOfExort << std::endl;

  int slot1 = static_cast<int>(mainCombState.m_Slot1);
  int slot2 = static_cast<int>(mainCombState.m_Slot2);
  std::cout << "Spell in Slot 1 : " << CombinationState::getSpellName(slot1) << " Value: " << slot1 << std::endl;
  std::cout << "Spell in Slot 2 : " << CombinationState::getSpellName(slot2) << " Value: " << slot2 << std::endl;
  std::cout << std::endl;
}
