#pragma once

#include "Tusk.h"
#include "Sequence.h"
#include "button_key_States.h"

// Tusk
CGEventRef Tusk(const InputMonitor &inputMonitor,
                const KeyboardMonitor &keyboardMonitor,
                CGEventRef &event) { // this event is the same from the
                                     // eventCallBack of main.cpp
  // middle mouse button
  if (inputMonitor.isMidClicked()) {
    // runSequence(seq6);
  }

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
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed

    avoidModifierKey(event, kCGEventFlagMaskAlternate); // avoid or unpress
                                                        // Alt modifier key

    // Similarly to unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);
    // Press the keys of the sequence, passed
    runSequence(seqTusk1);
  }
  return nullptr;
}
