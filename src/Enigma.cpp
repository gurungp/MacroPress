

#pragma once

#include "Enigma.h"
#include "PlaySound.h"
#include "Sequence.h"
#include "button_key_States.h"

PlaySound soundPlayerEnigma;

CGEventRef Enigma(const InputMonitor &inputMonitor,
                  const KeyboardMonitor &keyboardMonitor,
                  CGEventRef &event) {

  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    std::thread t([] {
      while (mouseRightState && mouseLeftState) { // until both button is released, don't run the sequence
      }

      runSequence3(selectEnigma3); //
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
      runSequence3(seqEnigma1);
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
      runSequence3(seqEnigma2);
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

      runSequence3(seqEnigma3);
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

      runSequence3(seqEnigma4);
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_D].state) {

    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (keyStates[kVK_ANSI_D].state) { // until d is released, don't run the sequence
      }
      if (unitSelected == EnigmaUnits::EIDOLON || unitSelected == EnigmaUnits::ENIGMA) {

        unitSelected = EnigmaUnits::ALL;

        runSequence3(selectEnigma2);
        soundPlayerEnigma.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Enigma/Both Selected.mp3");
      } else {

        unitSelected = EnigmaUnits::EIDOLON;

        runSequence3(selectEnigma1);
        soundPlayerEnigma.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Enigma/Enigma.mp3");
      }
    });
    t.detach();

    return nullptr;
  }
  if (keyStates[kVK_ANSI_W].state) {

    std::thread t([] {
      while (keyStates[kVK_ANSI_W].state) { // until w is released, don't run the sequence
      }

      runSequence3(selectEnigma4);
    });
    t.detach();

    return nullptr;
  }
  // FOR SELECTION PURPOSES
  if (keyStates[kVK_ANSI_3].state) {
    unitSelected = EnigmaUnits::ENIGMA;
    return nullptr;
  }
  if (keyStates[kVK_ANSI_4].state) {
    unitSelected = EnigmaUnits::EIDOLON;
    return nullptr;
  }
  if (keyStates[kVK_ANSI_V].state) {
    unitSelected = EnigmaUnits::ALL;
    return nullptr;
  }
  return nullptr;
}
