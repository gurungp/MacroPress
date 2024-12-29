

#pragma once

#include "Invoker2.h"
#include "PlaySound.h"
#include "Sequence.h"
#include "Spell.h"
#include "button_key_States.h"
#include <cstddef>
#include <dispatch/dispatch.h>

static Spell Blink{15.45};
static Spell Quas{0, 1, 2, 3, 4, 5, 6, 7, 8};
static Spell Wex{0, 1, 2, 3, 4, 5, 6, 7, 8};
static Spell Exort{0, 1, 2, 3, 4, 5, 6, 7, 8};

static Spell InvokeSpell{6.7, 6.4, 6.1, 5.8, 5.5, 5.2, 4.9,
                         4.6, 4.3, 4.0, 3.7, 3.4, 3.1, 2.8,
                         2.5, 2.2, 1.9, 1.6, 1.3, 1.0, 0.7};

int seqInv_WaitTime;    // default global Wait time for invoke spell
int seqInv_TornadoTime; // default global tornado wait time

PlaySound soundPlayer;

// Invoker
CGEventRef
Invoker(const InputMonitor &inputMonitor,
        const KeyboardMonitor &keyboardMonitor,
        CGEventRef &event) { // this event is the same from the
                             // eventCallBack of main.cpp

  // LEARNING
  if (keyStates[kVK_ANSI_P].state) {
    Quas.learnSpell(nullptr);

    InvokeSpell.learnSpell(nullptr);
    updateSequencesTimes();
    return nullptr;
  }

  if (keyStates[kVK_ANSI_L].state) {
    Wex.learnSpell(nullptr);

    InvokeSpell.learnSpell(nullptr);
    updateSequencesTimes();
    return nullptr;
  }

  if (keyStates[kVK_ANSI_K].state) {
    Exort.learnSpell(nullptr);

    InvokeSpell.learnSpell(nullptr);
    updateSequencesTimes();
    return nullptr;
  }

  // Prepare Combo 1
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 && Exort.m_spellLevel > 0) {
        altEprep();
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

      if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0) {
        altWprep();
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

      if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0 and Exort.m_spellLevel > 0) {
        alt3prep();
      }
    });
    t.detach();

    return nullptr;
  }

  // TESTING NEW WAY
  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Quas.m_spellLevel > 0 && Exort.m_spellLevel > 0) {
        if (Wex.m_spellLevel > 0) {
          altQprep();
        }
      }
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_2].state && keyboardMonitor.isAltKeyPressed()) {
    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      if (Quas.m_spellLevel > 0 and Wex.m_spellLevel > 0) {
        alt2prep();
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

      if (castingFunc != NULL) {
        // InvokeSpell.castSpell(nullptr);
        castingFunc();
      } else {
        std::cout << "Casting not set" << std::endl;
      }
    });
    t.detach();

    return nullptr;
  }

  // CAST Invoke
  if (keyStates[kVK_ANSI_R].state) {

    if (!InvokeSpell.onCoolDown()) {
      InvokeSpell.castSpell(nullptr);
    } else
      soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
    return nullptr;
  }

  return nullptr;
}

void updateSequencesTimes() {

  std::cout << "Current Quas Level is " << Quas.m_spellLevel << std::endl;
  std::cout << "Current Wex Level is " << Wex.m_spellLevel << std::endl;
  std::cout << "Current Exort Level is " << Exort.m_spellLevel << std::endl;

  TornadoLiftTime = TornadoLiftTimes[Quas.m_spellLevel];
  if (TornadoLiftTime <= 1.7)
    TornadoLiftTime = 1.8;

  if (setTornadoDelaySpell == SpellValues::ChaosMeteor) {

    seqInv_TornadoTime = (int)((TornadoLiftTime * 1000) - (ChaosMeteorDelay)); // Add the offset in the sequence not here

    std::cout << "Tornado wait time is " << seqInv_TornadoTime << " Chaos Meteor on the slot" << std::endl;
  } else if (setTornadoDelaySpell == SpellValues::SunStrike) {

    seqInv_TornadoTime = (int)((TornadoLiftTime * 1000) - (SunStrikeDelay)); // Add the offset in the sequence not here

    std::cout << "Tornado wait time is " << seqInv_TornadoTime << " Sun Strike on the slot" << std::endl;
  }

  // To prevent early cast time of 'r' at the end of the combo
  // TODO Analyze if this code under if can be discarded
  if (InvokeSpell.m_cooldown <= 1.3) {
    seqInv_WaitTime = (int)((1.3) * 1000); // no offset here because its directly placed on the
                                           // corresponding key sequnce
    // Note: Since 1.3 is set , the cast time should be adjusted in the key sequences
  } else {
    seqInv_WaitTime = (int)((InvokeSpell.m_cooldown) * 1000);
  }

  std::cout << "InvokeSpell.m_cooldown : " << InvokeSpell.m_cooldown << std::endl;
}

void altQprep() {

  runSequence4(seqInvTornado);
  runSequence4(seqInvEMP, seqInv_WaitTime);
  runSequence4(SunStrikePrep);

  castingFunc = altQcasting;
  setTornadoDelaySpell = SpellValues::SunStrike;
  updateSequencesTimes();

  std::cout << "seqInv_WaitTime : " << seqInv_WaitTime << "\n";
}
void altQcasting() {
  std::cout << "Tornado wait time is " << seqInv_TornadoTime << "\n";

  runSequence4(seqInvPressTD);
  runSequence4(seqInvPressR);
  runSequence4(seqInvPressD, seqInv_TornadoTime + TornadoHitTime);
  std::cout << "seqInv_WaitTime : " << seqInv_WaitTime << "\n";
}
void altWprep() {

  runSequence4(seqInvTornado);
  runSequence4(seqInvEMP, seqInv_WaitTime);
  runSequence4(SunStrikePrep);

  castingFunc = altWcasting;
  setTornadoDelaySpell = SpellValues::SunStrike;
  updateSequencesTimes();
}
void altWcasting() {
  runSequence4(seqInvPressDT);
  runSequence4(seqInvPressR);
  runSequence4(seqInvPressD, seqInv_TornadoTime + TornadoHitTime);
  runSequence4(ColdSnapPrep);
  runSequence4(seqInvPressR, seqInv_WaitTime);
}

void alt2prep() {

  runSequence4(seqInvTornado);
  runSequence4(seqInvColdSnap, seqInv_WaitTime);
  runSequence4(EMPPrep);

  castingFunc = alt2casting;
}
void alt2casting() {

  runSequence4(seqInvPressTD);
  runSequence4(seqInvPressR);
  runSequence4(seqInvPressD, 70);
}

void alt3prep() {

  runSequence4(seqInvTornado);
  runSequence4(seqInvEMP, seqInv_WaitTime);

  runSequence4(ChaosMeteorPrep);

  setTornadoDelaySpell = SpellValues::ChaosMeteor;
  updateSequencesTimes();
  castingFunc = alt3casting;
}
void alt3casting() {

  runSequence4(seqInvPressDT);                                     // Tornado + EMP
  runSequence4(seqInvPressR);                                      // Chaos Meteor Prepare
  runSequence4(seqInvPressD, seqInv_TornadoTime + TornadoHitTime); // Chaos Meteor

  if (seqInv_WaitTime > ((TornadoLiftTime * 1000) + TornadoHitTime - 50)) {
    std::cout << "seqInv_WaitTime is bigger : " << seqInv_WaitTime << " vs " << ((TornadoLiftTime * 1000) + TornadoHitTime - 50) << " \n";
    runSequence4(seqInvDeafeningBlast, seqInv_WaitTime - seqInv_TornadoTime - TornadoHitTime - 150);
  } else {

    std::cout << "seqInv_WaitTime is smaller : " << seqInv_WaitTime << " vs " << ((TornadoLiftTime * 1000) + TornadoHitTime - 50) << " \n";
    runSequence4(seqInvDeafeningBlast, seqInv_TornadoTime - 220);
  }

  runSequence4(seqInvPressD);
  runSequence4(seqInvColdSnap, seqInv_WaitTime - 100);
}

void altEprep() {

  runSequence4(seqInvAlacrity);
  runSequence4(seqInvForgedSpirits, seqInv_WaitTime);

  runSequence4(ColdSnapPrep);

  updateSequencesTimes();
  castingFunc = altEcasting;
}
void altEcasting() {

  runSequence4(seqInvPressAltT); // Alacrity
  runSequence4(seqInvPressD);    // Forged Spirits

  runSequence4(seqInvPressR); // ColdSnap Prepare

  runSequence4(seqInvPress2, 80); // Hex
  runSequence4(seqInvPressS);     // Soulburn

  runSequence4(seqInvPressD); // ColdSnap Cast

  runSequence4(seqInvChaosMeteor, seqInv_WaitTime); // Prepare Chaos Meteor
}
