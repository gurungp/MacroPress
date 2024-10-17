

#pragma once

#include "Sniper.h"
#include "Sequence.h"
#include "button_key_States.h"
#include <CoreGraphics/CGEventTypes.h>
#include <thread>

CGEventRef Sniper(const InputMonitor &inputMonitor, const KeyboardMonitor &keyboardMonitor, CGEventRef &event) { // this event is the same from the
                                                                                                                 // eventCallBack of main.cpp
                                                                                                                 // alt + right click
  // alt + e
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      runSequence2(seqSnipe1); // fetch the enemy
    });
    t.detach();
    return nullptr;
  }

  return event;
}
