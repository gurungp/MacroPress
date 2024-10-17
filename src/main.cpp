
#include "ArcWarden.h"
#include "EarthSpirit.cpp"
#include "InputMonitor.h"
#include "LegionCommander.h"
#include "LoneDruid.cpp"
#include "Sniper.cpp"
#include "Tusk.h"
#include "button_key_States.h"
#include <Carbon/Carbon.h>
#include <CoreGraphics/CGEvent.h>
#include <CoreGraphics/CGEventTypes.h>
#include <CoreGraphics/CGRemoteOperation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <chrono>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <ostream>
#include <thread>

// Using Threads to detect click Counts
std::atomic<int> leftclickCount(0);
std::atomic<int> rightclickCount(0);
std::atomic<bool> inLeftClickDetection(
    false); // Flag to ensure only one detection thread runs
std::atomic<bool> inRightClickDetection(
    false); // Flag to ensure only one detection thread runs
std::atomic<bool> left_alt_state = false;
std::atomic<bool> right_alt_state = false;
std::atomic<bool> double_leftClick = false;
std::atomic<bool> double_rightClick = false;
// Keyboard and Mouse Monitor to monitor key/button presses through IOKIT/Carbon
KeyboardMonitor keyboardMonitor;
InputMonitor inputMonitor;

void postSingleRightClick() {
  // Manual single right click event post
  CGPoint mousePosition = CGEventGetLocation(CGEventCreate(NULL));
  CGEventRef rightClickDown = CGEventCreateMouseEvent(
      NULL, kCGEventRightMouseDown, mousePosition, kCGMouseButtonRight);
  CGEventRef rightClickUp = CGEventCreateMouseEvent(
      NULL, kCGEventRightMouseUp, mousePosition, kCGMouseButtonRight);

  // Post the right click event
  CGEventPost(kCGSessionEventTap, rightClickDown);
  CGEventPost(kCGSessionEventTap, rightClickUp);

  // Clean up
  CFRelease(rightClickDown);
  CFRelease(rightClickUp);
}
void postSingleLeftClick() {
  // Manual single right click event post
  CGPoint mousePosition = CGEventGetLocation(CGEventCreate(NULL));
  CGEventRef leftClickDown = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseDown, mousePosition, kCGMouseButtonLeft);
  CGEventRef leftClickUp = CGEventCreateMouseEvent(
      NULL, kCGEventLeftMouseUp, mousePosition, kCGMouseButtonLeft);

  // Post the right click event
  CGEventPost(kCGSessionEventTap, leftClickDown);
  CGEventPost(kCGSessionEventTap, leftClickUp);

  // Clean up
  CFRelease(leftClickDown);
  CFRelease(leftClickUp);
}

void detectLeftDoubleClickandAlt(int timeoutMs) {

  inLeftClickDetection = true;
  std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));

  if (leftclickCount == 2) {
    double_leftClick = true;
    std::cout << "Double Left Click Detected" << std::endl;
    mouseStates[kCGEventLeftMouseDown].doubleClick = true;
  } else if (leftclickCount == 1) {
    if (flagsStates[kCGEventFlagMaskAlternate].state) {
      std::cout << " alt and left click detected " << std::endl;
      left_alt_state = true;
    } else {

      std::cout << "Single Left Click Detected" << std::endl;
      std::thread postLeftClick(postSingleLeftClick);
      postLeftClick.detach();
    }
  }
  leftclickCount = 0;
  inLeftClickDetection = false;
}
void detectRightDoubleClickandAlt(int timeoutMs) {

  inRightClickDetection = true;
  std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));

  if (rightclickCount == 2) {

    double_rightClick = true;
    std::cout << "Double Right Click Detected" << std::endl;
    mouseStates[kCGEventRightMouseDown].doubleClick = true;
  } else if (rightclickCount == 1) {
    if (flagsStates[kCGEventFlagMaskAlternate].state) {
      right_alt_state = true;
    } else {
      std::cout << "Single Right Click Detected" << std::endl;
      std::thread postRightClick(postSingleRightClick);
      postRightClick.detach();
    }
  }
  rightclickCount = 0;
  inRightClickDetection = false;
}
// ----------------End Double click detect --
//
// load the Function pointer that is selected to be run on the event loop for a
// particular hero this time ArcWarden or LegionCommander only
// variable name is hero
CGEventRef (*hero)(const InputMonitor &, const KeyboardMonitor &,
                   CGEventRef &) = &Sniper;

// Event CallBack Function
CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type,
                         CGEventRef event, void *refcon) {

  CGMouseButton button = static_cast<CGMouseButton>(
      CGEventGetIntegerValueField(event, kCGMouseEventButtonNumber));

  // Setting modifier keys states
  if (type == kCGEventFlagsChanged) {
    CGEventFlags flags = CGEventGetFlags(event);
    if ((flags & kCGEventFlagMaskAlternate) == 0) {
      flagsStates[kCGEventFlagMaskAlternate].state = false;
      //  std::cout << "Alt Released" << std::endl;
    } else {
      flagsStates[kCGEventFlagMaskAlternate].state = true;
      //   std::cout << "Alt Pressed" << std::endl;
    }
    if ((flags & kCGEventFlagMaskShift) == 0) {
      flagsStates[kCGEventFlagMaskShift].state = false;
      //    std::cout << "Shift Released" << std::endl;
    } else {
      flagsStates[kCGEventFlagMaskShift].state = true;
      //   std::cout << "Shift Pressed" << std::endl;
    }

    if ((flags & kCGEventFlagMaskControl) == 0) {
      flagsStates[kCGEventFlagMaskControl].state = false;
      //   std::cout << "Control Released" << std::endl;
    } else {
      flagsStates[kCGEventFlagMaskControl].state = true;
      //   std::cout << "Control Pressed" << std::endl;
    }
  }

  // Setting the mouse states
  if (type == kCGEventLeftMouseDown) {
    mouseStates[kCGEventLeftMouseUp].state = false;
    mouseStates[kCGEventLeftMouseDown].state = true;
  }
  if (type == kCGEventRightMouseDown) {

    mouseStates[kCGEventRightMouseUp].state = false;
    mouseStates[kCGEventRightMouseDown].state = true;
  }

  if (type == kCGEventLeftMouseUp) {
    mouseStates[kCGEventLeftMouseUp].state = true;
    mouseStates[kCGEventLeftMouseDown].state = false;
  }
  if (type == kCGEventRightMouseUp) {

    mouseStates[kCGEventRightMouseUp].state = true;
    mouseStates[kCGEventRightMouseDown].state = false;
  }

  if (type == kCGEventOtherMouseDown) {

    std::cout << "OTHER Mouse Button Clicked " << std::endl;
    mouseStates[kCGEventOtherMouseDown].state = true;
    mouseStates[kCGEventOtherMouseUp].state = false;
    if (button == 2) {
      std::cout << "Middle Mouse Button Clicked " << std::endl;

    } else if (button == 3) {

      std::cout << "Back Mouse Button Clicked " << std::endl;
    } else if (button == 4) {

      std::cout << "Forward Mouse Button Clicked " << std::endl;
    } else {
      std::cout << "Other Mouse Button Clicked " << std::endl;
    }
  }
  if (type == kCGEventOtherMouseUp) {

    mouseStates[kCGEventOtherMouseUp].state = true;
    mouseStates[kCGEventOtherMouseDown].state = false;
  }

  // End Setting Mouse states

  // if (type == kCGEventRightMouseDown) {

  //   rightclickCount++;          // Increament click count
  //   if (!inRightClickDetection) // Start a new detection thread only if not
  //                               // already running
  //   {
  //     std::thread detectThread(detectRightDoubleClickandAlt, 170);
  //     detectThread.detach();
  //   }
  //   return nullptr;
  // }

  // if (type == kCGEventLeftMouseDown) {
  //   leftclickCount++;          // Increament click count
  //   if (!inLeftClickDetection) // Start a new detection thread only if not
  //                              // already running
  //   {
  //     std::thread detectThread(detectLeftDoubleClickandAlt, 170);
  //     detectThread.detach();
  //   }
  //   return nullptr;
  // }
  //
  // --------Detect Double or Triple Clicks using Queue ---------
  //
  //  if (type == kCGEventLeftMouseDown) {
  //    mouseStates[kCGEventLeftMouseDown].state = true;
  //    mouseStates[kCGEventLeftMouseUp].state = false;
  //
  //    mouseStates[kCGEventLeftMouseDown].insertTime();
  //    mouseStates[kCGEventLeftMouseDown].calculateClickTimes();
  //
  //    if (mouseStates[kCGEventLeftMouseDown].tripleClick) {
  //      mouseStates[kCGEventLeftMouseDown].doubleClick = false;
  //      std::cout << "Left Triple Click" << std::endl;
  //    } else if (mouseStates[kCGEventLeftMouseDown].doubleClick) {
  //      std::cout << "Left Double Click " << std::endl;
  //    }
  //  }
  //
  //  if (type == kCGEventRightMouseDown) {
  //
  //    mouseStates[kCGEventRightMouseDown].state = true;
  //    mouseStates[kCGEventRightMouseUp].state = false;
  //    mouseStates[kCGEventRightMouseDown].insertTime();
  //    mouseStates[kCGEventRightMouseDown].calculateClickTimes();
  //
  //    if (mouseStates[kCGEventRightMouseDown].tripleClick) {
  //      mouseStates[kCGEventRightMouseDown].doubleClick = false;
  //      std::cout << "Right Triple Click" << std::endl;
  //    } else if (mouseStates[kCGEventRightMouseDown].doubleClick) {
  //      std::cout << "Right Double Click " << std::endl;
  //    }
  //  }

  // KEY DOWN EVENTS
  if (type == kCGEventKeyDown) {

    CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    if (keyCode == kVK_ANSI_W) {
      keyStates[kVK_ANSI_W].state = true;
    }
    if (keyCode == kVK_ANSI_E) {
      keyStates[kVK_ANSI_E].state = true;
    }
    if (keyCode == kVK_ANSI_R) {
      keyStates[kVK_ANSI_R].state = true;
    }
    if (keyCode == kVK_Option) {
      keyStates[kVK_Option].state = true;
    }
    if (keyCode == kVK_Control) {
      keyStates[kVK_Control].state = true;
    }
  }

  // KEY UP EVENTS
  if (type == kCGEventKeyUp) {

    CGKeyCode keyCode =
        (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    if (keyCode == kVK_ANSI_W) {
      keyStates[kVK_ANSI_W].state = false;
    }

    if (keyCode == kVK_ANSI_E) {
      keyStates[kVK_ANSI_E].state = false;
    }
    if (keyCode == kVK_ANSI_R) {
      keyStates[kVK_ANSI_R].state = false;
    }

    if (keyCode == kVK_Option) {
      keyStates[kVK_Option].state = false;
    }
    if (keyCode == kVK_Control) {
      keyStates[kVK_Control].state = false;
    }
  }

  // ---------------------------- All the macros defined below
  //
  hero(inputMonitor, keyboardMonitor, event);

  // turn off doubleClick flag for next iteration
  mouseStates[kCGEventRightMouseDown].doubleClick = false;
  mouseStates[kCGEventLeftMouseDown].doubleClick = false;

  // mouseStates[kCGEventLeftMouseDown].state = false;
  return event; // Pass the event to the next tap. Returning
  // the event will put the event (clicks, button press etc) back to the event
  // queue that will interact with the system or OS. Returning null will not let
  // the event happen
}

int main() {

  // Set up event tap
  CGEventMask eventMask =
      CGEventMaskBit(kCGEventLeftMouseDown) |
      CGEventMaskBit(kCGEventRightMouseDown) |
      CGEventMaskBit(kCGEventLeftMouseUp) |
      CGEventMaskBit(kCGEventRightMouseUp) | CGEventMaskBit(kCGEventKeyDown) |
      CGEventMaskBit(kCGEventKeyUp) | CGEventMaskBit(kCGEventFlagsChanged) |
      CGEventMaskBit(kCGEventOtherMouseDown) |
      CGEventMaskBit(kCGEventOtherMouseUp);

  CFMachPortRef eventTap = CGEventTapCreate(
      kCGHIDEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
      eventMask, eventCallback, NULL);

  if (!eventTap) {
    std::cerr << "Failed to create event tap." << std::endl;
    return 1;
  }

  CFRunLoopSourceRef runLoopSource =
      CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
                     kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);

  // Enter the run loop
  CFRunLoopRun();

  // Clean up
  CFRelease(runLoopSource);
  CFRelease(eventTap);

  return 0;
}
