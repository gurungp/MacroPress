
#pragma once

#include "BroodMother.h"
#include "PlaySound.h"
#include "Sequence.h"
#include "button_key_States.h"

PlaySound soundPlayerBrood;

CGEventRef BroodMother(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor,
                       CGEventRef &event) {
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(seqBrood1);
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_3].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(seqBrood2); //
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
      runSequence3(seqBrood3);
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_W].state) {
    // Select All
    std::thread t([] {
      while (keyStates[kVK_ANSI_W].state) { // until w is released, don't run the sequence
      }

      runSequence3(seqBroodSelect3);
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_E].state) {
    // Select All
    std::thread t([] {
      while (keyStates[kVK_ANSI_E].state) { // until e is released, don't run the sequence
      }
      if (selectUnits == 0) {

        runSequence3(seqBroodSelect4);
      } else {

        runSequence3(seqBroodSelect5);
      }
    });
    t.detach();

    return nullptr;
  }
  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    // Select All
    std::thread t([] {
      while (mouseRightState && mouseLeftState) { // until both button is released, don't run the sequence
      }

      runSequence3(seqBroodSelect3);
    });
    t.detach();
    return nullptr;
  }
  if (keyboardMonitor.isTabKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    if (selectUnits == 0) {

      soundPlayerBrood.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Other Units.mp3");
      runSequence3(seqBroodSelect2);
    } else {
      soundPlayerBrood.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/BroodMother/BroodMother.mp3");
      runSequence3(seqBroodSelect1);
    }
    return nullptr;
  }
  if (keyStates[kVK_ANSI_3].state) {
    // Unpress the E or any other key, to not have effect of the keypresses
    selectUnits = 0;
    return nullptr;
  }
  if (keyStates[kVK_ANSI_4].state) {
    // Unpress the E or any other key, to not have effect of the keypresses
    selectUnits = 1;
    return nullptr;
  }
  return nullptr;
}
