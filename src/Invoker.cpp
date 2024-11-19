

#pragma once

#include "Invoker.h"
#include "PlaySound.h"
#include "Spell.h"
#include "button_key_States.h"
#include <cstddef>

static Spell Blink{15.45};
static Spell Quas{0, 1, 2, 3, 4, 5, 6, 7, 8};
static Spell Wex{0, 1, 2, 3, 4, 5, 6, 7, 8};
static Spell Exort{0, 1, 2, 3, 4, 5, 6, 7, 8};

static Spell InvokeSpell{6.9, 6.6, 6.3, 6.0, 5.7, 5.4, 5.1, 4.8,
                         4.5, 4.2, 3.9, 3.6, 3.3, 3.0, 2.7,
                         2.4, 2.1, 1.8, 1.5, 1.2, 1.0};
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
int seqInv2B_TornadoTime;  // = (int)((TornadoLiftTime * 1000) + 865);            // 865 is the offset from where it begins
int seqInv3A1_WaitTime;    // = (int)((InvokeSpell.m_cooldown * 1000) + 370 + 330); // 370 + (600-270), and this is the offset
int seqInv3A1_TornadoTime; // = (int)((TornadoLiftTime * 1000) + 140);

PlaySound onCooldown;
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

    if (Quas.m_spellLevel > 0 && Wex.m_spellLevel > 0 and Exort.m_spellLevel > 0) {
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
  // Prepare Combo 1
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Alacrity.onCoolDown() or ForgedSpirits.onCoolDown() or InvokeSpell.onCoolDown()) {
        onCooldown.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        Set_Alacrity = true;
        Set_ForgedSpirits = true;

        if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 && Exort.m_spellLevel > 0) {

          //          InvokeSpell.castSpell(nullptr);
          runSequence2(seqInv1A);
          casting = seqInv1B;
        }
      }
    });
    t.detach();

    return nullptr;
  }
  // Prepare Combo 4B
  if (keyStates[kVK_ANSI_4].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 && Exort.m_spellLevel > 0) {

        runSequence2(seqInv4A);
        ChaosMeter.castSpell(nullptr);
        EMP.castSpell(nullptr);

        casting = seqInv4B;
      }
    });
    t.detach();

    return nullptr;
  }
  // Prepare Combo 2
  if (keyStates[kVK_ANSI_W].state && keyboardMonitor.isAltKeyPressed()) {
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (EMP.onCoolDown() or Tornado.onCoolDown() or InvokeSpell.onCoolDown()) {
        onCooldown.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        Set_EMP = true;
        Set_Tornado = true;

        if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0) {
          // InvokeSpell.castSpell(nullptr);
          std::cout << "Invoke Spell on Cooldown: " << InvokeSpell.onCoolDown() << std::endl;
          runSequence2(seqInv2A);
          casting = seqInv2B;
        }
      }
    });
    t.detach();

    return nullptr;
  }
  // Prepare Combo 3
  if (keyStates[kVK_ANSI_3].state && keyboardMonitor.isAltKeyPressed()) {
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (ChaosMeter.onCoolDown() or Tornado.onCoolDown() or InvokeSpell.onCoolDown()) {
        onCooldown.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        Set_ChaosMeteor = true;
        Set_Tornado = true;
        Set_DeafeningBlast = true;
        std::cout << "The calculated press r after time " << seqInv3A1_WaitTime << " ms" << std::endl;

        if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 and Exort.m_spellLevel > 0) {
          // InvokeSpell.castSpell(nullptr);
          std::cout << "Invoke Spell on Cooldown: " << InvokeSpell.onCoolDown() << std::endl;
          runSequence2(seqInv3A);
          casting = seqInv3B;
        }
      }
    });
    t.detach();

    return nullptr;
  }

  // Execute Spell Combo and Set Second Stage of Combo
  if (keyStates[kVK_ANSI_R].state && keyboardMonitor.isAltKeyPressed()) {

    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      bool InvokeCD = InvokeSpell.onCoolDown();
      std::cout << "InvokeSpell.onCoolDown() " << InvokeCD << std::endl;
      if (InvokeCD) {
        std::cout << "Invoke on Cooldown" << std::endl;
        onCooldown.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {
        if (!casting.empty()) {
          // InvokeSpell.castSpell(nullptr);
          runSequence2(casting);
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
    if (!InvokeSpell.onCoolDown())
      InvokeSpell.castSpell(nullptr);
    else
      onCooldown.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
    return nullptr;
  }

  // USING REFRESHER
  if (keyStates[kVK_ANSI_0].state) {
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
  std::cout << "Tornado wait time is " << seqInv2B_TornadoTime << std::endl;

  seqInv1A = {
      {{13}, {}, 140, 20},                   // w
      {{13}, {}, 270, 20},                   // w
      {{14, 15}, {}, 370, 20},               // e, r
      {{14}, {}, 490, 20},                   // e
      {{12}, {}, 623, 20},                   // q
      {{15}, {}, seqInv_WaitTime + 380, 20}, // r

  };

  seqInv1B = {
      {{17}, {58}, 140, 20},                 // alt + t
      {{2}, {}, 270, 20},                    // d
      {{12}, {}, 370, 20},                   // q
      {{12}, {}, 470, 20},                   // q
      {{15}, {}, 580, 20},                   // r
      {{2}, {}, 690, 20},                    // d
      {{14}, {}, 800, 20},                   // e
      {{14}, {}, 915, 20},                   // e
      {{13}, {}, 1030, 20},                  // w
      {{15}, {}, seqInv_WaitTime + 590, 20}, // r

  };
  seqInv2A = {
      {{13}, {}, 140, 20},                   // w
      {{13}, {}, 270, 20},                   // w
      {{13, 15}, {}, 370, 20},               // w, r
      {{12}, {}, 490, 20},                   // q
      {{15}, {}, seqInv_WaitTime + 390, 20}, // r

  };

  seqInv2B = {
      {{17}, {}, 140, 20},                          // t
      {{2}, {}, 270, 20},                           // d
      {{14}, {}, 370, 20},                          // e
      {{14}, {}, 490, 20},                          // e
      {{14}, {}, 623, 20},                          // e
      {{14}, {}, 730, 20},                          // e
      {{15}, {}, 850, 20},                          // r
      {{2}, {}, seqInv2B_TornadoTime, 20},          // d , casing sunstrike after the TornadoLiftTime
      {{12}, {}, (seqInv2B_TornadoTime + 100), 20}, // q
      {{12}, {}, (seqInv2B_TornadoTime + 200), 20}, // q
      {{15}, {}, (seqInv_WaitTime + 900), 20},      // r

  };

  seqInv3A = {
      {{12}, {}, 140, 20},                   // q
      {{13}, {}, 270, 20},                   // w
      {{13, 15}, {}, 370, 20},               // w, r -> Tornado
      {{14}, {}, 490, 20},                   // e
      {{14}, {}, 600, 20},                   // e
      {{15}, {}, seqInv_WaitTime + 370, 20}, // r -> Chaos Meter and +50 to make sure r is pressed after
      {{12}, {}, seqInv_WaitTime + 490, 20}, // q
      {{13}, {}, seqInv_WaitTime + 600, 20}, // w , preparing for  Deafening Blast
  };

  seqInv3B = {
      {{17}, {}, 140, 20},                                                                    // t, tornado
      {{2}, {}, seqInv3A1_TornadoTime + 400, 20},                                             // d, Chaos Meteor, The +400 is accounting for the
                                                                                              // time taken for Tornado to take affect
      {{15}, {}, seqInv3A1_TornadoTime + 400 + 200, 20},                                      // r
      {{2}, {}, seqInv3A1_TornadoTime + 400 + 1020, 20},                                      // d , Deafening Blast
      {{13}, {}, seqInv3A1_TornadoTime + 400 + 1140, 20},                                     // w
      {{14}, {}, seqInv3A1_TornadoTime + 400 + 1260, 20},                                     // e
      {{15}, {}, seqInv3A1_TornadoTime + seqInv_WaitTime + 400 + 900, 20},                    // r
      {{2}, {58}, seqInv3A1_TornadoTime + seqInv_WaitTime + 400 + 1020, 20},                  // alt + d
      {{12}, {}, seqInv3A1_TornadoTime + seqInv_WaitTime + 400 + 1140, 20},                   // q
      {{12}, {}, seqInv3A1_TornadoTime + seqInv_WaitTime + 400 + 1260, 20},                   // q
      {{12}, {}, seqInv3A1_TornadoTime + seqInv_WaitTime + 400 + 1390, 20},                   // q
      {{15}, {}, seqInv3A1_TornadoTime + seqInv_WaitTime + seqInv_WaitTime + 400 + 1190, 20}, // r

  };

  seqInv4A = {
      {{13}, {}, 140, 20},                   // w
      {{13}, {}, 270, 20},                   // w
      {{13, 15}, {}, 370, 20},               // w, r
      {{14}, {}, 490, 20},                   // e
      {{14}, {}, 600, 20},                   // e
      {{15}, {}, seqInv_WaitTime + 380, 20}, // r

  };

  seqInv4B = {

      {{3, 201}, {}, 140, 30},                       // F(Blink) + Left Click
      {{19}, {}, 260, 20},                           // 2 (Hex)
      {{17}, {}, 370, 30},                           // t (EMP)
      {{2}, {}, 470, 30},                            // d (Chaos Meteor)
      {{6}, {}, 780, 20},                            // z (Refresher)
      {{2}, {}, 1120, 20},                           // d (Chaos Meteor)
      {{17}, {}, 1480, 30},                          // t (EMP)
      {{13}, {}, 1810, 20},                          // w
      {{12}, {}, 1920, 20},                          // q
      {{19}, {}, 2060, 20},                          // 2 (Hex)
      {{15}, {}, 2170, 20},                          // r
      {{14}, {}, 2290, 20},                          // e,
      {{2}, {}, 2400, 20},                           // d (Deafening Blast)
      {{14}, {}, 2510, 20},                          // e
      {{14}, {}, 2620, 20},                          // e
      {{15}, {}, seqInv_WaitTime + 2100, 20},        // r
      {{2}, {58}, seqInv_WaitTime + 2100 + 110, 20}, // alt + d, Cataclysm

      {{12}, {}, seqInv_WaitTime + 2100 + 210, 20},       // q
      {{12}, {}, seqInv_WaitTime + 2100 + 310, 20},       // q
      {{12}, {}, seqInv_WaitTime + 2100 + 410, 20},       // q
      {{15}, {}, (seqInv_WaitTime * 2) + 2100 + 550, 20}, // r
      {{2}, {}, (seqInv_WaitTime * 2) + 2100 + 680, 20},  //  d (Cold Snap)
  };

  std::cout << "InvokeSpell.m_cooldown : " << InvokeSpell.m_cooldown << std::endl;
  std::cout << "seqInv2B_TornadoTime: " << seqInv2B_TornadoTime << std::endl;
  std::cout << "seqInv3A1_TornadoTime " << (seqInv3A1_TornadoTime) << std::endl;
}
