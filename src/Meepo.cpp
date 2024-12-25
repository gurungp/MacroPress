

#pragma once

#include "Meepo.h"
#include "PlaySound.h"
#include "Sequence.h"
#include "button_key_States.h"

PlaySound soundPlayerMeepo;

CGEventRef Meepo(const InputMonitor &inputMonitor,
                 const KeyboardMonitor &keyboardMonitor,
                 CGEventRef &event) {
  // Add meepo amount
  if (keyStates[kVK_ANSI_0].state) {

    soundPlayerMeepo.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Meepo/Adding Meepo.mp3");
    currentMeepoNum++;
    if (currentMeepoNum >= 5)
      currentMeepoNum = 5;

    return nullptr;
  }

  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    runSequence3(seqMeepoGen); // Select all
    return nullptr;
  }

  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      runSequence3(seqMeepo1);
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
      std::cout << "Running Meepo Sequence " << currentMeepoNum - 1 << "\n";
      runSequence3(*meepoSequences1[currentMeepoNum - 1]); // for ability w according to the number of Meepo
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

      runSequence3(*meepoSequences2[currentMeepoNum - 1]);
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
      runSequence3(*meepoSequences3[currentMeepoNum - 1]);
    });
    t.detach();

    return nullptr;
  }
  return nullptr;
}
