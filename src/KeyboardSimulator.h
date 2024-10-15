#pragma once

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CGRemoteOperation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <unistd.h>

struct AdvancedKeyPress {
  CGKeyCode key;
  int pressDuration; // how long to hold the key down in milliseconds
  int delayAfter;    // delay after key release in milliseconds
};

class KeyboardSimulator {
public:
  static void simulateKeyPressDown(CGKeyCode keyCode) {

    CGEventSourceRef source =
        CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

    // Key press
    CGEventRef keyDown = CGEventCreateKeyboardEvent(source, keyCode, true);
    CGEventPost(kCGHIDEventTap, keyDown);

    // Clean up
    CFRelease(keyDown);
    CFRelease(source);
  }

  static void simulateKeyPressUp(CGKeyCode keyCode) {
    CGEventSourceRef source =
        CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

    // Key release
    CGEventRef keyUp = CGEventCreateKeyboardEvent(source, keyCode, false);
    CGEventPost(kCGHIDEventTap, keyUp);

    // Clean up
    CFRelease(keyUp);
    CFRelease(source);
  }

  static void simulateKeyPressWithModifiers(CGKeyCode keyCode,
                                            CGEventFlags modifiers) {
    CGEventSourceRef source =
        CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

    // Key press with modifiers
    CGEventRef keyDown = CGEventCreateKeyboardEvent(source, keyCode, true);
    CGEventSetFlags(keyDown, modifiers);
    CGEventPost(kCGHIDEventTap, keyDown);

    // Key release with modifiers
    CGEventRef keyUp = CGEventCreateKeyboardEvent(source, keyCode, false);
    CGEventSetFlags(keyUp, modifiers);
    CGEventPost(kCGHIDEventTap, keyUp);

    // Clean up
    CFRelease(keyDown);
    CFRelease(keyUp);
    CFRelease(source);
  }

  static void injectAdvancedInput(const AdvancedKeyPress &press) {
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStatePrivate);
    if (source) {
      CGEventRef keyDown = CGEventCreateKeyboardEvent(source, press.key, true);
      CGEventRef keyUp = CGEventCreateKeyboardEvent(source, press.key, false);

      if (keyDown && keyUp) {
        CGEventPost(kCGSessionEventTap, keyDown);
        usleep(press.pressDuration *
               1000); // Convert ms to microseconds for press duration
        CGEventPost(kCGSessionEventTap, keyUp);
        usleep(press.delayAfter *
               1000); // Convert ms to microseconds for delay after
      }

      if (keyDown)
        CFRelease(keyDown);
      if (keyUp)
        CFRelease(keyUp);
      CFRelease(source);
    }
  }
};
