

#pragma once

#include "Chen.h"
#include "Sequence.h"
#include "button_key_States.h"

CGEventRef Chen(const InputMonitor &inputMonitor,
                const KeyboardMonitor &keyboardMonitor,
                CGEventRef &event) {

  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    // Select both Clone and Arc Warden
    runSequence3(seqChenGen); // Select all
    return nullptr;
  }

  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      runSequence3(seqChen1);
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
      runSequence3(seqChen2);
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_D].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(seqChen3);
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

      runSequence3(seqChen4);
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

      runSequence3(seqChen5);
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

      runSequence3(seqChen6);
    });
    t.detach();

    return nullptr;
  }

  return nullptr;
}
