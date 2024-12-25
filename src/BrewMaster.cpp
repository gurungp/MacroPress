

#pragma once

#include "BrewMaster.h"
#include "Sequence.h"
#include "button_key_States.h"

CGEventRef BrewMaster(const InputMonitor &inputMonitor,
                      const KeyboardMonitor &keyboardMonitor,
                      CGEventRef &event) {
  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    // Select both Clone and Arc Warden
    runSequence3(seqBrewGen); // Select all
    return nullptr;
  }

  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(seqBrew1);
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

      runSequence3(seqBrew2a);
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

      runSequence3(seqBrew2b);
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
      runSequence3(seqBrew3);
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
      runSequence3(seqBrew2c);
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
      runSequence3(seqBrew4);
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
      runSequence3(seqBrew5);
    });
    t.detach();

    return nullptr;
  }

  return nullptr;
}
