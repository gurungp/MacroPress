

#pragma once

#include "QOP.h"
#include "Sequence.h"
#include "button_key_States.h"

CGEventRef QueenOfPain(const InputMonitor &inputMonitor, const KeyboardMonitor &keyboardMonitor, CGEventRef &event) { // this event is the same from the
                                                                                                                      // eventCallBack of main.cpp
                                                                                                                      // alt + right click
  // alt + e
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    CGEventSetType(event, kCGEventKeyUp);

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      runSequence3(seqQOP1);
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
      runSequence3(seqQOP2);
    });
    t.detach();
  }
  return event;
}
