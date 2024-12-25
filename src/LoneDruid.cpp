
#pragma once

#include "LoneDruid.h"
#include "Sequence.h"
#include "button_key_States.h"
#include <CoreGraphics/CGEventTypes.h>
#include <iostream>
#include <thread>

PlaySound soundPlayerLoneDruid;
CGEventRef LoneDruid(const InputMonitor &inputMonitor, const KeyboardMonitor &keyboardMonitor, CGEventRef &event) { // this event is the same from the
                                                                                                                    // eventCallBack of main.cpp
                                                                                                                    // alt + right click
                                                                                                                    // alt + right click

  // alt + right click
  // if (altState && mouseRightState) {

  //   std::thread t([] {
  //     while (altState) { // until alt is released, don't run the sequence

  //       std::cout << "Alt and Right Click Pressed" << std::endl;
  //     }
  //     runSequence2(seqLD1A); // fetch the enemy
  //   });
  //   t.detach();
  //   return nullptr;
  // }

  // both mouse button click
  if (inputMonitor.isRightClicked() && inputMonitor.isLeftClicked()) {
    std::thread t([] {
      while (mouseRightState && mouseLeftState) { // until both button is released, don't run the sequence
      }

      runSequence3(seqDruidGen2); //
    });
    t.detach();
    return nullptr;
  }

  // alt + q
  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      runSequence3(seqLD2a);
    });
    t.detach();
    return nullptr;
  }

  // alt + 4
  if (keyStates[kVK_ANSI_R].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      runSequence3(seqLD3);
    });
    t.detach();
    return nullptr;
  }
  // alt + 3
  if (keyStates[kVK_ANSI_3].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      runSequence3(seqLD4);
    });
    t.detach();
    return nullptr;
  }

  // alt + e
  if (keyStates[kVK_ANSI_E].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);

    // Similarly, to avoid alt modifier to linger when the sequence of presses
    // are being executed

    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }

      runSequence3(seqLD1A); // fetch the enemy
    });
    t.detach();
    return nullptr;
  }
  // alt + w
  if (keyStates[kVK_ANSI_W].state && keyboardMonitor.isAltKeyPressed()) {

    // Unpress the E or any other key, to not have effect of the
    // keypresses
    CGEventSetType(event, kCGEventKeyUp);

    // Similarly, to avoid alt modifier to linger when the sequence of presses
    // are being executed

    std::thread t([] {
      while (keyStates[kVK_ANSI_W].state) { // until alt is released, don't run the sequence
      }

      runSequence3(seqLD2b); // fetch the enemy
    });
    t.detach();
    return nullptr;
  }

  if (keyStates[kVK_ANSI_W].state) {

    std::thread t([] {
      while (keyStates[kVK_ANSI_W].state) { // until w is released, don't run the sequence
      }
      if (currentUnit == BEAR || currentUnit == DRUID) {
        currentUnit = BOTH;

        runSequence3(seqDruidGen2);
        soundPlayerLoneDruid.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/LoneDruid/Both Selected.mp3");
      } else {

        currentUnit = BEAR;

        runSequence3(seqDruidGen3);
        soundPlayerLoneDruid.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/LoneDruid/Bear.mp3");
      }
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_3].state) {
    currentUnit = DRUID;
    return nullptr;
  }
  if (keyStates[kVK_ANSI_4].state || keyStates[kVK_ANSI_5].state) {
    currentUnit = BEAR;
    return nullptr;
  }
  if (keyStates[kVK_ANSI_9].state || keyStates[kVK_ANSI_6].state) {
    currentUnit = BOTH;
    return nullptr;
  }
  // to calculate double left click
  //  if (inputMonitor.isLeftClicked()) {
  //
  //    mouseStates[kCGEventLeftMouseDown].insertTime();
  //
  //    // When calling member functiohns in a thread, we need to provide both the
  //    // object (buttonState instance) and the function pointer to the member
  //    // function.
  //    //  std::thread calcThread(&buttonState::calculateClickTimes, //
  //    //                       &mouseStates[kCGEventLeftMouseDown]);
  //    //
  //    // calcThread.detach()
  //    //
  //    mouseStates[kCGEventLeftMouseDown].calculateClickTimes();
  //
  //    if (mouseStates[kCGEventLeftMouseDown].tripleClick) {
  //      mouseStates[kCGEventLeftMouseDown].doubleClick = false;
  //      std::cout << "Left Triple Click" << std::endl;
  //    } else if (mouseStates[kCGEventLeftMouseDown].doubleClick) {
  //      std::cout << "Left Double Click " << std::endl;
  //    }
  // }

  // to calculate double right click
  //  if (inputMonitor.isRightClicked()) {
  //
  //    mouseStates[kCGEventRightMouseDown].insertTime();
  //    mouseStates[kCGEventRightMouseDown].calculateClickTimes();
  //
  //    if (mouseStates[kCGEventRightMouseDown].tripleClick) {
  //      mouseStates[kCGEventRightMouseDown].doubleClick = false;
  //      std::cout << "Right Triple Click" << std::endl;
  //    } else if (mouseStates[kCGEventRightMouseDown].doubleClick) {
  //      std::cout << "Rightg Double Click " << std::endl;
  //    }
  //  }

  // Check if there was double click

  //  if (mouseStates[kCGEventLeftMouseDown].doubleClick) {
  //    runSequence(seqLD5);
  //  }
  // alt + right click
  // if (keyboardMonitor.isAltKeyPressed() && inputMonitor.isRightClicked()) {
  // std::cout << "alt and right click" << std::endl;
  // to avoid alt modifier to linger when the sequence of presses
  // are being executed
  //    avoidModifierKey(
  //       event, kCGEventFlagMaskAlternate); // avoid or unpress Alt modifier key

  //   runSequence(seqLD1);
  //   return event; // return nullptr or null event to avoid the click being
  // processed as
  // the click will be done in the runSequence
  // }
  // otherwise alt + right click
  //  if (flagsStates[kCGEventFlagMaskAlternate].state &&
  //      mouseStates[kCGEventRightMouseDown].state) {
  //
  //    flagsStates[kCGEventFlagMaskAlternate].state = false;
  //    mouseStates[kCGEventRightMouseDown].state = false;
  //    std::cout << "alt and right click " << std::endl;
  //    runSequence(seq4);
  //  }

  return event;
}
