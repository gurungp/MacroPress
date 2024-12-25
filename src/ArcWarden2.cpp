#pragma once

#include "ArcWarden2.h"
#include "Sequence.h"
#include "Spell.h"
#include "button_key_States.h"
#include <chrono>

// 3 selects main hero
// 5 (ctrl-group) selects clone only
// 9 (ctrl-group) selects both main hero and clone
// 8 (ctrl-group) selects the illusions only
// 7 (ctrl-group) selects the clone and the illusions

PlaySound soundPlayerArc;

CGEventRef ArcWarden2(const InputMonitor &inputMonitor,
                      const KeyboardMonitor &keyboardMonitor,
                      CGEventRef &event) {

  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    // Select both Clone and Arc Warden
    //
    std::thread t([] {
      while (mouseRightState && mouseLeftState) { // until both button is released, don't run the sequence
      }

      runSequence3(seqArcGen);
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (switchHero == ARCWARDEN) {
        switchHero = CLONE;

        runSequence3(Arc1a);
      } else {

        switchHero = ARCWARDEN;

        runSequence3(Arc1b);
      }
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
      if (switchHero == ARCWARDEN) {
        switchHero = CLONE;

        runSequence3(Arc2a);
      } else {

        switchHero = ARCWARDEN;

        runSequence3(Arc2b);
      }
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
      if (switchHero == ARCWARDEN) {
        switchHero = CLONE;

        runSequence3(Arc3a);
      } else {

        switchHero = ARCWARDEN;

        runSequence3(Arc3b);
      }
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

      altR_Combo = true;
      runSequence3(seqArc4a);
    });
    t.detach();

    return nullptr;
  }

  if (inputMonitor.isRightClicked() && altR_Combo) {
    altR_Combo = false;
    runSequence3(seqArc4b);

    return nullptr;
  }
  if (keyStates[kVK_ANSI_3].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(Arc5);
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_4].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(Arc6);
    });
    t.detach();

    return nullptr;
  }

  // FOR SELECTION PURPOSES
  if (keyStates[kVK_ANSI_D].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (switchHero == ARCWARDEN) {
        switchHero = CLONE;
        runSequence3(seqArcSwitch1a);

      } else {
        switchHero = ARCWARDEN;
        runSequence3(seqArcSwitch1b);
      }
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_R].state) {
    std::thread t([] {
      while (keyStates[kVK_ANSI_R].state) { // until 3 is released, don't run the sequence
      }
      runSequence3(seqArcGen);
      // soundPlayerArc.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Arc Warden/Main Hero Selected.mp3");
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_3].state) {
    std::thread t([] {
      while (keyStates[kVK_ANSI_3].state) { // until 3 is released, don't run the sequence
      }
      selectedUnit = ARCWARDEN;
      switchHero = CLONE;
      // soundPlayerArc.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Arc Warden/Main Hero Selected.mp3");
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_5].state) {
    if (TempestAlive) {
      selectedUnit = CLONE;
      switchHero = CLONE;
      //   soundPlayerArc.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Arc Warden/Clone Selected.mp3");
    }
    return nullptr;
  }
  if (keyStates[kVK_ANSI_9].state) {
    if (TempestAlive) {
      selectedUnit = BOTH;
      switchHero = BOTH;
      // soundPlayerArc.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Arc Warden/Both Selected.mp3");
    }
    return nullptr;
  }
  if (keyStates[kVK_ANSI_8].state) {
    selectedUnit = ILLUSIONS;
    switchHero = ILLUSIONS;
    // soundPlayerArc.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Arc Warden/Illusions Selected.mp3");
    return nullptr;
  }
  if (keyStates[kVK_ANSI_7].state) {
    selectedUnit = CLONE_AND_ILLUSIONS;
    switchHero = CLONE_AND_ILLUSIONS;
    // soundPlayerArc.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Arc Warden/Clone Illusions Selected.mp3");
    return nullptr;
  }

  return nullptr;
}
