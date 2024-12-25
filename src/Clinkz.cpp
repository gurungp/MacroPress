

#pragma once

#include "Clinkz.h"
#include "Sequence.h"
#include "button_key_States.h"

CGEventRef Clinkz(const InputMonitor &inputMonitor,
                  const KeyboardMonitor &keyboardMonitor,
                  CGEventRef &event) {
  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(seqClinkz1);
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

      runSequence3(seqClinkz2); //
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
      runSequence3(seqClinkz3);
    });
    t.detach();

    return nullptr;
  }

  return nullptr;
}
