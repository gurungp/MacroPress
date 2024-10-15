#pragma once

#include "ArcWarden.h"
#include "Sequence.h"
#include "button_key_States.h"

CGEventRef ArcWarden(const InputMonitor &inputMonitor,
                     const KeyboardMonitor &keyboardMonitor,
                     CGEventRef &event) { // this event is the same from the
                                          // eventCallBack of main.cpp
  // middle mouse button
  if (inputMonitor.isMidClicked()) {
    // runSequence(seq6);
  }

  // alt + right click
  if (keyboardMonitor.isAltKeyPressed() && inputMonitor.isRightClicked()) {
    // std::cout << "alt and right click" << std::endl;
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed
    avoidModifierKey(
        event, kCGEventFlagMaskAlternate); // avoid or unpress Alt modifier key

    runSequence(seq2);
    return nullptr; // return nullptr or null event to avoid the click being
                    // processed as
    // the click will be done in the runSequence
  }
  // otherwise alt + right click
  //  if (flagsStates[kCGEventFlagMaskAlternate].state &&
  //      mouseStates[kCGEventRightMouseDown].state) {
  //
  //    flagsStates[kCGEventFlagMaskAlternate].state = false;
  //    mouseStates[kCGEventRightMouseDown].state = false;
  //    std::cout << "alt and right click " << std::endl;
  //    runSequence(seq4);
  //  }

  // alt + left click
  if (keyboardMonitor.isAltKeyPressed() && inputMonitor.isLeftClicked()) {
    //    std::cout << "alt and left click" << std::endl;
    //  avoidModifierKey(event, kCGEventFlagMaskAlternate);
    //  runSequence(seq3);
    // return nullptr;
  }
  // alt + left click
  //  if (flagsStates[kCGEventFlagMaskAlternate].state &&
  //      mouseStates[kCGEventLeftMouseDown].state) {
  //
  //    flagsStates[kCGEventFlagMaskAlternate].state = false;
  //    std::cout << " alt and left click " << std::endl;
  //    // runSequence(seq5);
  //  }

  // if forward clicked
  if (inputMonitor.isForwardClicked()) {
    runSequence(seq4);
    //   return nullptr;
  }

  // if alt + back Clicked
  if (inputMonitor.isBackClicked()) {
    runSequence(seq5);
    // return nullptr;
  }
  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    // CGEventSetType(event, kCGEventKeyUp);
    runSequence(seq6);
    return nullptr;
  }

  // alt + w
  if (keyStates[kVK_ANSI_W].state && keyboardMonitor.isAltKeyPressed()) {
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed
    avoidModifierKey(
        event, kCGEventFlagMaskAlternate); // avoid or unpress Alt modifier key

    // Similarly to unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);

    // Press the keys of the sequence, passed
    runSequence(seq7);
  }
  // alt + e
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed
    avoidModifierKey(
        event, kCGEventFlagMaskAlternate); // avoid or unpress Alt modifier key

    // Similarly to unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);

    // Press the keys of the sequence, passed
    runSequence(seq1);
  }
  return event;
}
