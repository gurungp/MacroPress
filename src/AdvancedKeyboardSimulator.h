#pragma once

#include "button_key_States.h"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CGEvent.h>
#include <CoreGraphics/CGEventSource.h>
#include <CoreGraphics/CGEventTypes.h>
#include <CoreGraphics/CGRemoteOperation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <IOKit/graphics/IOGraphicsTypes.h>
#include <IOKit/hidsystem/IOHIDLib.h>
#include <IOKit/hidsystem/IOLLEvent.h>
#include <IOKit/hidsystem/event_status_driver.h>
#include <MacTypes.h>
#include <chrono>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

struct AdvancedButtonPress {
  CGKeyCode key;
  CGKeyCode modifierKey;
  int delayBefore;   // wait time before pressing the key
  int pressDuration; // how long to hold the key down in ms
};

struct AdvancedButtonPress2 {
  std::vector<CGKeyCode> keys;
  std::vector<CGKeyCode> modifierKeys;
  int delayBefore;   // wait time before pressing the key
  int pressDuration; // how long to hold the key down in ms
};

static CGPoint getCurrentMousePosition() {
  CGEventRef event = CGEventCreate(nullptr);
  CGPoint point = CGEventGetLocation(event);
  CFRelease(event);
  return point;
}
enum Modifier {
  alt = kVK_Option,
  shift = kVK_Shift,
  ctrl = kVK_Control,
  cmd = kVK_Command,
  caps = kVK_CapsLock
};

class AdvancedKeyboardSimulator {

  // static inline CGKeyCode key; // For OLD method
  static inline bool modifierKey = false; // flag to check if modifier key value was passed

public:
  static void releaseCGEventref(std::vector<CGEventRef> &events) {
    for (CGEventRef event : events) {
      if (event != nullptr) {
        CFRelease(event);
      }
    }
  }

  static void rightClickHID(CGPoint location) {
    // Connect to IOHIDSystem
    NXEventHandle eventSystem = NXOpenEventStatus();
    if (!eventSystem) {
      std::cerr << "Failed to open event status" << std::endl;
      return;
    }
    // std::cout << "HID CLICK RUNNING" << std::endl;
    //  Create the NXEventData Structure
    NXEventData eventData;
    memset(&eventData, 0, sizeof(NXEventData));
    eventData.mouse.click = true;
    eventData.mouse.pressure = 255; // Max pressure

    // Create the IOGPoint structure
    IOGPoint iolocation;
    iolocation.x = static_cast<SInt16>(location.x);
    iolocation.y = static_cast<SInt16>(location.y);

    // Post the right mouse down event
    IOHIDPostEvent(eventSystem, NX_RMOUSEDOWN, iolocation, &eventData, kNXEventDataVersion, 0, false);

    // Small delay to simulate real click
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Post the right mouse up event
    // MAY REQUIRE TO MAKE SEPARATE FUNCTION FOR MOUSE UP
    IOHIDPostEvent(eventSystem, NX_RMOUSEUP, iolocation, &eventData, kNXEventDataVersion, 0, false);
    NXCloseEventStatus(eventSystem);
  }

  static void leftClickHID(CGPoint location) {
    // Connect to IOHIDSystem
    NXEventHandle eventSystem = NXOpenEventStatus();
    if (!eventSystem) {
      std::cerr << "Failed to open event status" << std::endl;
      return;
    }
    // std::cout << "HID CLICK RUNNING" << std::endl;
    //  Create the NXEventData Structure
    NXEventData eventData;
    memset(&eventData, 0, sizeof(NXEventData));
    eventData.mouse.click = true;
    eventData.mouse.pressure = 255; // Max pressure

    // Create the IOGPoint structure
    IOGPoint iolocation;
    iolocation.x = static_cast<SInt16>(location.x);
    iolocation.y = static_cast<SInt16>(location.y);

    // Post the right mouse down event
    IOHIDPostEvent(eventSystem, NX_LMOUSEDOWN, iolocation, &eventData, kNXEventDataVersion, 0, false);

    // Small delay to simulate real click
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Post the left mouse up event
    // MAY REQUIRE TO MAKE SEPARATE FUNCTION FOR MOUSE UP

    IOHIDPostEvent(eventSystem, NX_LMOUSEUP, iolocation, &eventData, kNXEventDataVersion, 0, false);
    NXCloseEventStatus(eventSystem);
  }

  static void simulateAdvancedMultiButtonPress2(const std::vector<AdvancedButtonPress2> &buttonPresses2) { // flags are for passing modifiers to be applied, 0
                                                                                                           // for no modifiers

    std::vector<std::thread> threads;

    for (const auto &press : buttonPresses2) {
      threads.emplace_back([press]() {
        // Initializing main Event Source
        CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
        std::vector<CGEventRef> eventsDown;
        std::vector<CGEventRef> eventsUp;
        std::vector<CGEventRef> modifiersDown;
        std::vector<CGEventRef> modifiersUp;

        // Wait before pressing
        std::this_thread::sleep_for(std::chrono::milliseconds(press.delayBefore));

        if (source) {
          for (CGKeyCode md : press.modifierKeys) {
            modifiersDown.emplace_back(CGEventCreateKeyboardEvent(source, md, true));
            modifiersUp.emplace_back(CGEventCreateKeyboardEvent(source, md, false));
          }

          for (CGKeyCode key : press.keys) {

            if (key == 201) {
              CGPoint currentPos = getCurrentMousePosition();
              eventsDown.emplace_back(CGEventCreateMouseEvent(source, kCGEventLeftMouseDown, currentPos, kCGMouseButtonLeft));
              eventsUp.emplace_back(CGEventCreateMouseEvent(source, kCGEventLeftMouseUp, currentPos, kCGMouseButtonLeft));
            } else if (key == 200) {

              CGPoint currentPos = getCurrentMousePosition();
              eventsDown.emplace_back(CGEventCreateMouseEvent(source, kCGEventRightMouseDown, currentPos, kCGMouseButtonRight));
              eventsUp.emplace_back(CGEventCreateMouseEvent(source, kCGEventRightMouseUp, currentPos, kCGMouseButtonRight));
            } else {

              eventsDown.emplace_back(CGEventCreateKeyboardEvent(source, key, true));
              eventsUp.emplace_back(CGEventCreateKeyboardEvent(source, key, false));
            }
          }

          // First press all the modifier keys
          for (CGEventRef modifier : modifiersDown) {

            CGEventPost(kCGHIDEventTap, modifier);

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
          }

          // Then press the keys

          for (CGEventRef event : eventsDown) {
            CGEventType eventType = CGEventGetType(event);

            if (eventType == kCGEventRightMouseDown) {
              // HID RightClick
              CGPoint currentPos = getCurrentMousePosition();
              rightClickHID(currentPos);
            } else if (eventType == kCGEventLeftMouseDown) {
              CGPoint currentPos = getCurrentMousePosition();
              leftClickHID(currentPos);
            } else {

              CGEventPost(kCGHIDEventTap, event);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
          }

          // Wait for specified time
          std::this_thread::sleep_for(std::chrono::milliseconds(press.pressDuration));

          // Then Release modifier and event keys
          for (CGEventRef modifier : modifiersUp) {
            CGEventPost(kCGHIDEventTap, modifier);

            //  std::this_thread::sleep_for(std::chrono::milliseconds(200));
          }
          for (CGEventRef event : eventsUp) {
            CGEventPost(kCGHIDEventTap, event);
            //    std::this_thread::sleep_for(std::chrono::milliseconds(200));
          }
        } // End if

        // Clean up - safely release objects only if they were successfully
        releaseCGEventref(modifiersDown);
        releaseCGEventref(modifiersUp);
        releaseCGEventref(eventsDown);
        releaseCGEventref(eventsUp);
      });
    }

    // Wait for all threads to complete
    for (auto &thread : threads) {
      thread.join();
    }
  }
  // OLD VERSION
  static void simulateAdvancedMultiButtonPress(const std::vector<AdvancedButtonPress> &buttonPresses) { // flags are for passing modifiers to be applied, 0
                                                                                                        // for no modifiers
    std::vector<std::thread> threads;

    for (const auto &press : buttonPresses) {
      threads.emplace_back([press]() {
        // std::cout << "Advanced Keyboard Simulator is Running" << std::endl;
        // Wait before pressing
        std::this_thread::sleep_for(std::chrono::milliseconds(press.delayBefore));

        // Initializing main Event Source
        CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
        CGEventRef eventDown = nullptr;
        CGEventRef eventUp = nullptr;
        CGEventRef modifierDown = nullptr;
        CGEventRef modifierUp = nullptr;

        if (source) {
          // since keyStates is an unordered map, it will
          // add any new entries as false other than
          // the keys already present which are modifier keys
          if (press.key == 200) { // if its a right click

            CGPoint currentPos = getCurrentMousePosition();
            eventDown = CGEventCreateMouseEvent(source, kCGEventRightMouseDown, currentPos, kCGMouseButtonRight);
            eventUp = CGEventCreateMouseEvent(source, kCGEventRightMouseUp, currentPos, kCGMouseButtonRight);

            if (press.modifierKey != 79) // modifier key is set
            {
              //   modifierDown =
              //     CGEventCreateKeyboardEvent(source, press.modifierKey,
              //     true);
              CGEventSetFlags(eventDown, modifierStates[press.modifierKey]);
              //  CGEventSetFlags(eventDown, kCGEventFlagMaskAlternate);
              //    CGEventPost(kCGHIDEventTap, modifierDown);
            }
            CGEventPost(kCGHIDEventTap, eventDown);

            // Hold for the specified duration
            std::this_thread::sleep_for(std::chrono::milliseconds(press.pressDuration));

            CGEventPost(kCGHIDEventTap, eventUp);
            if (press.modifierKey != 79) {

              //   modifierUp =
              //       CGEventCreateKeyboardEvent(source, press.modifierKey,
              //       false);
              //   CGEventPost(kCGHIDEventTap, modifierUp);
            }

          } else if (press.key == 201) // 201 for left mouse click
          {

            CGPoint currentPos = getCurrentMousePosition();
            eventDown = CGEventCreateMouseEvent(source, kCGEventLeftMouseDown, currentPos, kCGMouseButtonLeft);
            eventUp = CGEventCreateMouseEvent(source, kCGEventLeftMouseUp, currentPos, kCGMouseButtonLeft);

            if (press.modifierKey != 79) // modifier key is set
            {
              //     modifierDown =
              //       CGEventCreateKeyboardEvent(source, press.modifierKey,
              //       true);
              CGEventSetFlags(eventDown, modifierStates[press.modifierKey]);
              //  CGEventSetFlags(eventDown, kCGEventFlagMaskAlternate);
              //  CGEventPost(kCGHIDEventTap, modifierDown);
            }
            CGEventPost(kCGHIDEventTap, eventDown);

            // Hold for the specified duration
            std::this_thread::sleep_for(std::chrono::milliseconds(press.pressDuration));

            CGEventPost(kCGHIDEventTap, eventUp);

            if (press.modifierKey != 79) {

              //    modifierUp =
              //        CGEventCreateKeyboardEvent(source, press.modifierKey,
              //        false);
              //   CGEventPost(kCGHIDEventTap, modifierUp);
            }

          } // end if 201 left mouse click
          else { // for keyboard presses

            eventUp = CGEventCreateKeyboardEvent(source, press.key, false);
            eventDown = CGEventCreateKeyboardEvent(source, press.key, true);
            if (press.modifierKey != 79) {
              // std::cout << "Modifier key: " << press.modifierKey <<
              // std::endl;
              //    modifierDown =
              //       CGEventCreateKeyboardEvent(source, press.modifierKey,
              //       true);
              CGEventSetFlags(eventDown, modifierStates[press.modifierKey]);
              //    CGEventPost(kCGHIDEventTap, modifierDown);
            }
            CGEventPost(kCGHIDEventTap, eventDown);
            // Hold for the specified duration
            std::this_thread::sleep_for(std::chrono::milliseconds(press.pressDuration));

            CGEventPost(kCGHIDEventTap, eventUp);

            if (press.modifierKey != 79) {

              //  modifierUp =
              //      CGEventCreateKeyboardEvent(source, press.modifierKey,
              //      false);
              //  CGEventPost(kCGHIDEventTap, modifierUp);
            }
          }
          //----------------------------OLD----------------------------------------------------
          //  if (existModifierKey(static_cast<CGKeyCode>(press.key))) {
          //    modifierKey = true;
          //    key = static_cast<CGKeyCode>(press.key);
          //    modifierStates[key].state = true;
          //  } else if (press.key == 200) { // if its a right click

          //    CGPoint currentPos = getCurrentMousePosition();
          //    eventDown =
          //        CGEventCreateMouseEvent(source, kCGEventRightMouseDown,
          //                                currentPos, kCGMouseButtonRight);
          //    eventUp = CGEventCreateMouseEvent(source, kCGEventRightMouseUp,
          //                                      currentPos,
          //                                      kCGMouseButtonRight);

          //    if (modifierStates[key].state) {

          //      modifierDown = CGEventCreateKeyboardEvent(source, key, true);
          //      //  CGEventSetFlags(eventDown, kCGEventFlagMaskAlternate);
          //      CGEventPost(kCGHIDEventTap, modifierDown);
          //    }
          //    CGEventPost(kCGHIDEventTap, eventDown);
          //    // Hold for the specified duration
          //    std::this_thread::sleep_for(
          //        std::chrono::milliseconds(press.pressDuration));
          //    CGEventPost(kCGHIDEventTap, eventUp);

          //    if (modifierStates[key].state) {

          //      modifierUp = CGEventCreateKeyboardEvent(source, key, false);
          //      CGEventPost(kCGHIDEventTap, modifierUp);
          //    }

          //    // Release the button
          //    modifierStates[key].state = false;
          //    modifierKey = false;
          //  } else if (press.key == 201) // 201 for left mouse click
          //  {

          //    CGPoint currentPos = getCurrentMousePosition();
          //    eventDown = CGEventCreateMouseEvent(source,
          //    kCGEventLeftMouseDown,
          //                                        currentPos,
          //                                        kCGMouseButtonLeft);
          //    eventUp = CGEventCreateMouseEvent(source, kCGEventLeftMouseUp,
          //                                      currentPos,
          //                                      kCGMouseButtonLeft);

          //    if (modifierStates[key].state) {

          //      modifierDown = CGEventCreateKeyboardEvent(source, key, true);
          //      //  CGEventSetFlags(eventDown, kCGEventFlagMaskAlternate);
          //      CGEventPost(kCGHIDEventTap, modifierDown);
          //    }
          //    CGEventPost(kCGHIDEventTap, eventDown);

          //    CGEventPost(kCGHIDEventTap,
          //                eventUp); // Hold for the specified duration
          //    std::this_thread::sleep_for(
          //        std::chrono::milliseconds(press.pressDuration));
          //    if (modifierStates[key].state) {

          //      modifierUp = CGEventCreateKeyboardEvent(source, key, false);
          //      CGEventPost(kCGHIDEventTap, modifierUp);
          //    }

          //    // Release the button
          //    modifierStates[key].state = false;
          //    modifierKey = false;
          //  } // end if 201 left mouse click
          //  else { // for keyboard presses
          //    std::cout << "State of shift key : " <<
          //    modifierStates[key].state
          //              << std::endl;
          //    eventUp = CGEventCreateKeyboardEvent(source, press.key, false);
          //    eventDown = CGEventCreateKeyboardEvent(source, press.key, true);
          //    if (modifierStates[key].state) {
          //      std::cout << "Modifier key: " << key << std::endl;
          //      modifierDown = CGEventCreateKeyboardEvent(source, key, true);
          //      CGEventSetFlags(modifierDown, kCGEventFlagMaskShift);
          //      //  CGEventSetFlags(eventDown, kCGEventFlagMaskAlternate);
          //      CGEventPost(kCGHIDEventTap, modifierDown);
          //    }
          //    CGEventPost(kCGHIDEventTap, eventDown);
          //    // Hold for the specified duration
          //    std::this_thread::sleep_for(
          //        std::chrono::milliseconds(press.pressDuration));

          //    CGEventPost(kCGHIDEventTap, eventUp);

          //    if (modifierStates[key].state) {

          //      modifierUp = CGEventCreateKeyboardEvent(source, key, false);
          //      CGEventPost(kCGHIDEventTap, modifierUp);
          //    }

          //    // Release the button
          //    modifierStates[key].state = false;
          //    modifierKey = false;
          //  }
          //  //---------------------------------------OLD--------------------------

        } // End if

        // Clean up - safely release objects only if they were successfully
        if (eventDown) {
          CFRelease(eventDown);
        }
        if (eventUp) {
          CFRelease(eventUp);
        }
        if (source) {
          CFRelease(source);
        }
        if (modifierUp) {
          CFRelease(modifierUp);
        }
        if (modifierDown) {
          CFRelease(modifierDown);
        }
      });
    }

    // Wait for all threads to complete
    for (auto &thread : threads) {
      thread.join();
    }
  }
};
