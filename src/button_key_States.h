
#pragma once

#include "Queue.h"
#include <Carbon/Carbon.h>
#include <chrono>
#include <thread>
#include <unordered_map>

#define altState flagsStates[kCGEventFlagMaskAlternate].state
#define mouseRightState mouseStates[kCGEventRightMouseDown].state
#define mouseLeftState mouseStates[kCGEventLeftMouseDown].state
#define w_keyState keyStates[kVK_ANSI_W].state
#define e_keyState keyStates[kVK_ANSI_E].state
#define r_keyState keyStates[kVK_ANSI_R].state

// Struct to hold button state and handle time-point calculations for
// double/triple clicks

struct buttonState {

  Queue<std::chrono::time_point<std::chrono::high_resolution_clock>> time_point{
      3}; //  in-class member initialization:
  std::chrono::milliseconds d1 = std::chrono::milliseconds(0);
  std::chrono::milliseconds d2 = std::chrono::milliseconds(0);
  bool state = false;
  bool doubleClick = false;
  bool tripleClick = false;

  void insertTime() {
    time_point.enqueue(std::chrono::high_resolution_clock::now());
  }

  // Store click times and then calculate if there was double click or triple
  // click
  void calculateClickTimes() {
    int startIndex = time_point.rear;
    int index = (time_point.rear - 1 + time_point.size) % time_point.size;

    //  std::cout << "Index 1: " << index << std::endl;
    //  std::cout << "Rear Value: " << time_point.rear << std::endl;
    auto timePointNew = time_point[index];

    index = (index - 1 + time_point.size) % time_point.size;
    //  std::cout << "Index 2: " << index << std::endl;
    auto timePointMid = time_point[index];

    index = (index - 1 + time_point.size) % time_point.size;

    // std::cout << "Index 3: " << index << std::endl;
    auto timePointOld = time_point[index];

    //    std::cout << "Old : " << timePointOld.time_since_epoch().count()
    //              << std::endl;
    //    std::cout << "Mid : " << timePointMid.time_since_epoch().count()
    //              << std::endl;
    //    std::cout << "New : " << timePointNew.time_since_epoch().count()
    //              << std::endl;
    //
    d1 = std::chrono::duration_cast<std::chrono::milliseconds>(timePointNew -
                                                               timePointMid);
    d2 = std::chrono::duration_cast<std::chrono::milliseconds>(timePointMid -
                                                               timePointOld);
    //    std::cout << "1st - 2nd diff:  " << d1.count() << "ms" << std::endl;
    //    std::cout << "2nd - 3rd diff:  " << d2.count() << "ms" << std::endl;
    if (d1 >= std::chrono::milliseconds(120) &&
        d1 <= std::chrono::milliseconds(220)) {
      doubleClick = true;
    } else {
      doubleClick = false;
    }

    if (d2 >= std::chrono::milliseconds(120) &&
        d2 <= std::chrono::milliseconds(220) &&
        d1 >= std::chrono::milliseconds(120) &&
        d1 <= std::chrono::milliseconds(220)) {
      tripleClick = true;
    } else {
      tripleClick = false;
    }
  }
};

// Declare global unordered maps for key, mouse, flag states, modifier keys list
extern std::unordered_map<CGKeyCode, buttonState> keyStates;
extern std::unordered_map<CGEventType, buttonState> mouseStates;
extern std::unordered_map<CGEventFlags, buttonState> flagsStates;
extern std::unordered_map<CGKeyCode, CGEventFlags> modifierStates;
