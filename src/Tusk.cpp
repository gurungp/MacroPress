#pragma once

#include "Tusk.h"
#include "Sequence.h"
#include "Spell.h"
#include "button_key_States.h"

static Spell IceShard{23.0, 20.0, 17.0, 14.0};
static Spell SnowBall{21.45, 19.45, 17.45, 15.45};
static Spell TagTeam{24.45, 21.45, 18.45, 15.45};
static Spell WalrusKick{12.45};
static Spell WalrusPunch{20.45, 15.45, 10.45};
static Spell Blink{15.45};

// Tusk
CGEventRef Tusk(const InputMonitor &inputMonitor,
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

  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Blink.onCoolDown() or SnowBall.onCoolDown() || WalrusPunch.onCoolDown() or WalrusKick.onCoolDown()) {
        std::cout << "THE WHOLE SEQUENCE CANNOT RUN BECAUSE ON COOLDOWN" << std::endl;
        //   IceShard.m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
      } else {

        // Press the keys of the sequence, passed
        runSequence2(seqTusk1);
      }
    });
    t.detach();

    return nullptr;
  }
  //-----------------------------------------TESTING---------------------------------------
  // Learn and print times
  if (keyStates[kVK_ANSI_P].state) {

    IceShard.learnSpell(nullptr);
    SnowBall.learnSpell(nullptr);
    WalrusPunch.learnSpell(nullptr);
    TagTeam.learnSpell(nullptr);
    Blink.learnSpell(nullptr);
    // IceShard.print_SpellTimes();
    return nullptr;
    // runSequence(seq6);
  }
  // SET SCEPTER
  if (keyStates[kVK_ANSI_O].state) {

    WalrusKick.learnSpell(nullptr);
    // IceShard.setScepter(true, 6.0);
    return nullptr;
  }

  // UNSET SCEPTER
  if (keyStates[kVK_ANSI_O].state and keyboardMonitor.isAltKeyPressed()) {
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed

    avoidModifierKey(event, kCGEventFlagMaskAlternate); // avoid or unpress
                                                        // Alt modifier key

    // Similarly to unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);
    IceShard.setScepter(false, 6.0);

    return nullptr;
  }
  // CAST SPELL Q
  if (keyStates[kVK_ANSI_Q].state) {

    IceShard.castSpell(nullptr);
    return nullptr;
  }
  // CAST SPELL W
  if (keyStates[kVK_ANSI_W].state) {

    SnowBall.castSpell(nullptr);
    return nullptr;
  }
  // CAST SPELL E
  // if (keyStates[kVK_ANSI_E].state) {
  //
  //   TagTeam.castSpell(nullptr);
  //   return nullptr;
  // }
  // CAST SPELL R
  if (keyStates[kVK_ANSI_R].state) {

    WalrusPunch.castSpell(nullptr);
    return nullptr;
  }

  // CAST D (WalrusKick)
  if (keyStates[kVK_ANSI_D].state) {

    WalrusKick.castSpell(nullptr);
    return nullptr;
  }
  // CAST F Blink
  if (keyStates[kVK_ANSI_F].state) {

    Blink.castSpell(nullptr);
    return nullptr;
  }

  // Use Talent
  if (keyStates[kVK_ANSI_I].state) {
    SnowBall.useTalent(8.0);
    return nullptr;
  }
  // UNSET OCTARINE
  if (keyStates[kVK_ANSI_L].state && keyboardMonitor.isAltKeyPressed()) {

    avoidModifierKey(event, kCGEventFlagMaskAlternate);
    CGEventSetType(event, kCGEventKeyUp);

    IceShard.setOctarine(false);
    WalrusPunch.setOctarine(false);

    WalrusKick.setOctarine(false);
    TagTeam.setOctarine(false);
    SnowBall.setOctarine(false);
    Blink.setOctarine(false);
    return nullptr;
  }

  // SET OCTARINE
  if (keyStates[kVK_ANSI_L].state) {
    IceShard.setOctarine(true);
    WalrusPunch.setOctarine(true);

    WalrusKick.setOctarine(true);
    TagTeam.setOctarine(true);
    SnowBall.setOctarine(true);
    Blink.setOctarine(true);
  }

  // UNSET SHARD
  if (keyStates[kVK_ANSI_K].state && keyboardMonitor.isAltKeyPressed()) {
    // testing only
    //  avoidModifierKey(event, kCGEventFlagMaskAlternate);
    // CGEventSetType(event, kCGEventKeyUp);

    // IceShard.setShard(false, 3.0);
    return nullptr;
  }

  // SET SHARD
  if (keyStates[kVK_ANSI_K].state) {
    // testing only
    // IceShard.setShard(true, 3.0);
    return nullptr;
  }

  //-------------------------------------------------END-TESTING--------------------------------------
  return nullptr;
}
