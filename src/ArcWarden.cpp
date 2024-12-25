#pragma once

#include "ArcWarden.h"
#include "Sequence.h"
#include "button_key_States.h"

CGEventRef ArcWarden(const InputMonitor &inputMonitor,
                     const KeyboardMonitor &keyboardMonitor,
                     CGEventRef &event) { // this event is the same from the
                                          // eventCallBack of main.cpp
                                          //

  // middle mouse button
  // if (inputMonitor.isMidClicked()) {
  // runSequence(seq6);
  //}

  // alt + left click
  //  if (keyboardMonitor.isAltKeyPressed() && inputMonitor.isLeftClicked()) {
  //    std::cout << "alt and left click" << std::endl;
  //  avoidModifierKey(event, kCGEventFlagMaskAlternate);
  //  runSequence(seq3);
  // return nullptr;
  // }

  // if forward clicked
  if (inputMonitor.isForwardClicked()) {
    // Select main hero and righ click
    runSequence2(seqArc4);
    return nullptr;
  }

  // if back Clicked
  if (inputMonitor.isBackClicked()) {
    // Select clone and Right click
    runSequence2(seqArc5);
    return nullptr;
  }

  // alt + w
  //  if (keyStates[kVK_ANSI_W].state && keyboardMonitor.isAltKeyPressed()) {
  //
  //    CGEventSetType(event, kCGEventKeyUp); // Unpress w or any pressed keys
  //    std::thread t([] {
  //      while (altState) { // until alt is released, don't run the sequence
  //      }
  //
  //      runSequence2(seqArc7);
  //    });
  //    t.detach();
  //    return nullptr;
  //  }

  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    // Select both Clone and Arc Warden
    runSequence2(seqArc6);
    return nullptr;
  }

  // alt + right click
  if (keyboardMonitor.isAltKeyPressed() && inputMonitor.isRightClicked()) {
    //  Selects main hero and then presses q and e, and selects both hero again
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(seqArcB3);
    });
    t.detach();
    return nullptr;
  }

  // alt + e
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    CGEventSetType(event, kCGEventKeyUp); // Unpress e or any pressed keys
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence2(seqArc7);
    });
    t.detach();
    return nullptr;
  }

  // alt + r
  if (keyStates[kVK_ANSI_R].state && keyboardMonitor.isAltKeyPressed()) {

    CGEventSetType(event, kCGEventKeyUp); // Unpress e or any pressed keys
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      continueCombo = true;
      runSequence3(seqArcB1a);
    });
    t.detach();
    return nullptr;
  }

  if (inputMonitor.isRightClicked() && continueCombo) {
    continueCombo = false;
    runSequence3(seqArcB1b);
  }

  return event;
}
