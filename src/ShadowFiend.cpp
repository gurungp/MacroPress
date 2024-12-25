
#pragma once

#include "ShadowFiend.h"
#include "PlaySound.h"
#include "Sequence.h"
#include "Spell.h"
#include "button_key_States.h"

CGEventRef ShadowFiend(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor,
                       CGEventRef &event) {

  if (keyStates[kVK_ANSI_3].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      continueCombo = true;
      runSequence3(seqSF5);
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_W].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      continueCombo = true;
      runSequence3(seqSF3); // With BKB
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      continueCombo = true;
      runSequence3(seqSF2);
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_R].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      continueCombo = true;
      runSequence3(seqSF4);
    });
    t.detach();

    return nullptr;
  }

  if (inputMonitor.isRightClicked() && continueCombo) {
    continueCombo = false;
    runSequence3(seqSF1);
  }
  if (keyStates[kVK_ANSI_L].state && keyboardMonitor.isAltKeyPressed()) {
    castTime = 1200;
    seqSF2 = {
        {{3, 201, 19}, {}, 100, 20, 50}, // f, left click, 2
        {{15}, {}, castTime, 20, 50},    // r
    };
    seqSF3 = {
        {{3, 201, 19, 6}, {}, 100, 20, 50}, // f, left click, 2,z(BKB)
        {{15}, {}, castTime, 20, 50},       // r
    };

    return nullptr;
  }

  if (keyStates[kVK_ANSI_L].state) {

    castTime = 1700;
    seqSF2 = {
        {{3, 201, 19}, {}, 100, 20, 50}, // f, left click, 2
        {{15}, {}, castTime, 20, 50},    // r
    };
    seqSF3 = {

        {{3, 201, 6, 19}, {}, 100, 20, 50}, // f, left click,z(BKB,Silver edge),2
        {{15}, {}, castTime, 20, 50},       // r

        //     {{3, 201, 19}, {}, 100, 20, 50}, // f, left click, 2
        //    {{15, 6}, {}, castTime, 20, 50}, // r, z(BKB)
    };

    return nullptr;
  }
  return nullptr;
}
