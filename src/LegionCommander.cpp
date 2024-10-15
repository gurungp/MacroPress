#pragma once

#include "LegionCommander.h"
#include "Sequence.h"
#include "button_key_States.h"
#include <CoreGraphics/CGEventTypes.h>

// Legion Commander
CGEventRef LC(const InputMonitor &inputMonitor,
              const KeyboardMonitor &keyboardMonitor,
              CGEventRef &event) { // this event is the same from the
                                   // eventCallBack of main.cpp
  // middle mouse button
  if (inputMonitor.isBackClicked()) {
    runSequence2(seqG1);
    return nullptr;
  }

  // alt + right click
  if (altState && mouseRightState) {

    // CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
                         // to avoid alt modifier to linger when the sequence of presses
        //  std::cout << "Alt and Right Click Pressed" << std::endl;
      }
      runSequence2(seqLC1);
    });
    t.detach();

    return nullptr; // return nullptr or null event to avoid the click being
                    // processed as
    // the click will be done in the runSequence
  }

  // alt + e
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
                         // to avoid alt modifier to linger when the sequence of presses
        //  std::cout << "Alt and Right Click Pressed" << std::endl;
      }
      runSequence2(seqLC3);
    });
    t.detach();

    return nullptr;
  }
  return nullptr;
}
