#pragma once

#include <Carbon/Carbon.h>
#include <IOKit/hid/IOHIDManager.h>
#include <IOKit/hid/IOHIDUsageTables.h>

class InputMonitor {
public:
  IOHIDManagerRef manager;
  bool mouse1; // left click
  bool mouse2; // right click
  bool mouse3; // middle click
  bool mouse4; // back
  bool mouse5; // forward

  static void InputCallback(void *context, IOReturn result, void *sender,
                            IOHIDValueRef value) {
    InputMonitor *monitor = static_cast<InputMonitor *>(context);
    IOHIDElementRef element = IOHIDValueGetElement(value);
    uint32_t usagePage = IOHIDElementGetUsagePage(element);
    uint32_t usage = IOHIDElementGetUsage(element);
    int pressed = IOHIDValueGetIntegerValue(value);

    if (usagePage == kHIDPage_Button) {

      // printf("Mouse Button %u %s \n", usage, pressed ? "Pressed" :
      // "Released");

      if (usage == 5) {
        monitor->mouse5 = pressed;
      }
      if (usage == 2) {
        monitor->mouse2 = pressed;
      }
      if (usage == 3) {
        monitor->mouse3 = pressed;
      }
      if (usage == 4) {
        monitor->mouse4 = pressed;
      }
      if (usage == 1) {
        monitor->mouse1 = pressed;
      }
    }
  }

public:
  InputMonitor()
      : manager(nullptr), mouse1(false), mouse2(false), mouse3(false),
        mouse4(false), mouse5(false) {
    manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    IOHIDManagerOpen(manager, kIOHIDOptionsTypeNone);

    IOHIDManagerRegisterInputValueCallback(manager, InputCallback, this);

    CFDictionaryRef matchingDict = IOServiceMatching(kIOHIDDeviceKey);
    IOHIDManagerSetDeviceMatching(manager, matchingDict);

    IOHIDManagerScheduleWithRunLoop(manager, CFRunLoopGetCurrent(),
                                    kCFRunLoopDefaultMode);
  }

  ~InputMonitor() {
    if (manager) {
      IOHIDManagerUnscheduleFromRunLoop(manager, CFRunLoopGetCurrent(),
                                        kCFRunLoopDefaultMode);
      IOHIDManagerClose(manager, kIOHIDOptionsTypeNone);
      CFRelease(manager);
    }
  }

  bool isLeftClicked() const { return mouse1; }
  bool isRightClicked() const { return mouse2; }
  bool isMidClicked() const { return mouse3; }
  bool isBackClicked() const { return mouse4; }
  bool isForwardClicked() const { return mouse5; }
};

class KeyboardMonitor {
private:
  IOHIDManagerRef manager;
  bool altKeyPressed;
  bool shiftKeyPressed;
  bool capKeyPressed;
  bool tabKeyPressed;

  static void KeyboardCallback(void *context, IOReturn result, void *sender,
                               IOHIDValueRef value) {
    KeyboardMonitor *monitor = static_cast<KeyboardMonitor *>(context);
    IOHIDElementRef element = IOHIDValueGetElement(value);
    uint32_t usagePage = IOHIDElementGetUsagePage(element);
    uint32_t usage = IOHIDElementGetUsage(element);
    int pressed = IOHIDValueGetIntegerValue(value);

    if (usagePage == kHIDPage_KeyboardOrKeypad) {
      if (usage == kHIDUsage_KeyboardLeftAlt) {
        monitor->altKeyPressed = pressed;
      } else if (usage == kHIDUsage_KeyboardLeftShift) {
        monitor->shiftKeyPressed = pressed;
      } else if (usage == kHIDUsage_KeyboardCapsLock) {
        monitor->capKeyPressed = pressed;
      } else if (usage == kHIDUsage_KeyboardTab) {
        monitor->tabKeyPressed = pressed;
      }
    }
  }

public:
  KeyboardMonitor() : manager(nullptr), altKeyPressed(false) {
    manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    IOHIDManagerOpen(manager, kIOHIDOptionsTypeNone);

    IOHIDManagerRegisterInputValueCallback(manager, KeyboardCallback, this);

    CFDictionaryRef matchingDict = IOServiceMatching(kIOHIDDeviceKey);
    IOHIDManagerSetDeviceMatching(manager, matchingDict);

    IOHIDManagerScheduleWithRunLoop(manager, CFRunLoopGetCurrent(),
                                    kCFRunLoopDefaultMode);
  }

  ~KeyboardMonitor() {
    if (manager) {
      IOHIDManagerUnscheduleFromRunLoop(manager, CFRunLoopGetCurrent(),
                                        kCFRunLoopDefaultMode);
      IOHIDManagerClose(manager, kIOHIDOptionsTypeNone);
      CFRelease(manager);
    }
  }

  bool isAltKeyPressed() const { return altKeyPressed; }
  bool isShiftKeyPressed() const { return shiftKeyPressed; }
  bool isCapsKeyPressed() const { return capKeyPressed; }
  bool isTabKeyPressed() const { return tabKeyPressed; }
};
