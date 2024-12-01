
#pragma once

#include "EarthSpirit.h"
#include "Sequence.h"
#include "button_key_States.h"
// Tusk

CGEventRef EarthSpirit(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor,
                       CGEventRef &event) { // this event is the same from the
                                            // eventCallBack of main.cpp
  // alt + right click
  if (keyboardMonitor.isAltKeyPressed() && inputMonitor.isRightClicked()) {
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
                         // to avoid alt modifier to linger when the sequence of presses
        //  std::cout << "Alt and Right Click Pressed" << std::endl;
      }
      runSequence2(seqESpirit1);
    });
    t.detach();

    return nullptr; // return nullptr or null event to avoid the click being
                    // processed as
    // the click will be done in the runSequence
  }

  // alt + e
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    // Similarly, to avoid alt modifier to linger when the sequence of presses
    // are being executed

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence2(seqESpirit2); // fetch the enemy
    });
    t.detach();

    return nullptr;
  }

  // alt + r
  if (keyStates[kVK_ANSI_R].state && altState) {

    CGEventSetType(event, kCGEventKeyUp); // unpress r first
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
                         // to avoid alt modifier to linger when the sequence of presses
        //  std::cout << "Alt and Right Click Pressed" << std::endl;
      }
      runSequence2(seqESpirit3);
    });
    t.detach();
  }

  return nullptr;
}
