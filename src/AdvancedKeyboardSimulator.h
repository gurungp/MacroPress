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
#include <vector>

struct AdvancedButtonPress2 {
  std::vector<CGKeyCode> keys;
  std::vector<CGKeyCode> modifierKeys;
  int delayBefore;   // wait time before pressing the key
  int pressDuration; // how long to hold the key down in ms
};

struct AdvancedButtonPress3 {
  std::vector<CGKeyCode> keys;
  std::vector<CGKeyCode> modifierKeys;
  int delayBefore; // wait time before pressing the key
  int WaitAfterPressDuration;
  int pressInterval; // if there are sequence of presses in a single
                     // entry, this is the wait interval for each presses
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

  static void simulateAdvancedMultiButtonPress3(const std::vector<AdvancedButtonPress3> &buttonPresses) {

    std::vector<std::thread> threads;

    for (const auto &press : buttonPresses) {
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

          for (int i = 0; i < eventsDown.size(); i++) {
            CGEventType eventType = CGEventGetType(eventsDown[i]);
            if (eventType == kCGEventRightMouseDown) {
              // HID RightClick
              CGPoint currentPos = getCurrentMousePosition();
              rightClickHID(currentPos);
            } else if (eventType == kCGEventLeftMouseDown) {
              CGPoint currentPos = getCurrentMousePosition();
              leftClickHID(currentPos);
            } else {

              CGEventPost(kCGHIDEventTap, eventsDown[i]);

              std::this_thread::sleep_for(std::chrono::milliseconds(press.pressInterval));

              CGEventPost(kCGHIDEventTap, eventsUp[i]);
            }
          }

          //   for (CGEventRef event : eventsDown) {
          //  }

          // Wait for specified time
          std::this_thread::sleep_for(std::chrono::milliseconds(press.WaitAfterPressDuration));

          // Then Release modifier and event keys
          for (CGEventRef modifier : modifiersUp) {
            CGEventPost(kCGHIDEventTap, modifier);
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
  // flags are for passing modifiers to be applied, 0 for no modifiers
  static void simulateAdvancedMultiButtonPress2(const std::vector<AdvancedButtonPress2> &buttonPresses) {

    std::vector<std::thread> threads;

    for (const auto &press : buttonPresses) {
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
};
