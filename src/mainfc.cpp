
#include "AdvancedKeyboardSimulator.h"
#include "KeyboardMonitor.h"
#include "Sequence.cpp"
#include <Carbon/Carbon.h>
#include <CoreGraphics/CGEvent.h>
#include <CoreGraphics/CGEventTypes.h>
#include <CoreGraphics/CGRemoteOperation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <chrono>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

template <typename T> class Queue {
public:
  Queue(int s) : size(s), arr(new T[s]) {
    // std::cout << "Queue constructor called " << std::endl;
  }
  Queue(const Queue &other) : size(other.size), arr(new T[other.size]) {
    // std::cout << "Copy constructor called " << std::endl;
    for (int i = 0; i < size; i++)
      arr[i] = other.arr[i];
  }

  Queue &operator=(const Queue &other) {
    // std::cout << "Queue copy assignment called" << std::endl;
    if (this == &other) {
      return *this; // handle self assignment
    }

    delete[] arr;

    // Allocate new memory and copy elements
    arr = new T[size];
    size = other.size;
    front = other.front;
    rear = other.rear;
    count = other.count;
    for (int i = 0; i < size; ++i) {
      arr[i] = other.arr[i];
    }
    return *this;
  }
  Queue(Queue &&other)
      : size(other.size), arr(other.arr), front(other.front), rear(other.rear),
        count(other.count) {
    // std::cout << "Move constructor called " << std::endl;
    other.arr = nullptr;
    other.size = other.front = other.rear = other.count = 0;
  }

  T &operator[](int i) { return arr[i]; }

  ~Queue() {
    // std::cout << "Queue destructor called " << std::endl;
    delete[] arr;
  }

  void enqueue(T element) {
    if (arr == nullptr) {
      std::cout << "Queue uninitialized" << std::endl;
      return;
    }

    if (rear == front && count != 0) // front always should be in front if there
                                     // are elements added already
    {
      front = ((front + 1) % size);
    }

    arr[rear % size] = element;
    rear = (rear + 1) % size;

    count++;
    if (count >= size + 1)
      count = size;
  }

  T dequeue() {
    if (isEmpty()) {
      throw std::underflow_error("Queue is empty");
    }

    T element = arr[front];
    front = (front + 1) % size;
    count--;
    if (front == rear && !isEmpty())
      rear = (rear + 1) % size;
    return element;
  }

  bool isEmpty() {
    if (count == 0)
      return true;
    else
      return false;
  }

public:
  T *arr;
  int size;
  int rear = 0;
  int front = 0;
  int count = 0;
};

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

  void calculateClickTimes() {
    int startIndex = time_point.rear;
    int index = (time_point.rear - 1 + time_point.size) % time_point.size;

    std::cout << "Index 1: " << index << std::endl;
    std::cout << "Rear Value: " << time_point.rear << std::endl;
    auto timePointNew = time_point[index];

    index = (index - 1 + time_point.size) % time_point.size;
    std::cout << "Index 2: " << index << std::endl;
    auto timePointMid = time_point[index];

    index = (index - 1 + time_point.size) % time_point.size;

    std::cout << "Index 3: " << index << std::endl;
    auto timePointOld = time_point[index];


    d1 = std::chrono::duration_cast<std::chrono::milliseconds>(timePointNew -
                                                               timePointMid);
    d2 = std::chrono::duration_cast<std::chrono::milliseconds>(timePointMid -
                                                               timePointOld);

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

std::unordered_map<CGKeyCode, buttonState> keyStates = {
    {kVK_ANSI_W, buttonState()}, {kVK_ANSI_E, buttonState()}};

std::unordered_map<CGEventType, buttonState> mouseStates = {
    {kCGEventLeftMouseDown, buttonState()},
    {kCGEventRightMouseDown, buttonState()},
    {kCGEventLeftMouseUp, buttonState()},
    {kCGEventRightMouseUp, buttonState()}};

std::unordered_map<CGEventFlags, buttonState> flagsStates = {
    {kCGEventFlagMaskAlternate, buttonState()}};

// Using Threads to detect click Counts
std::atomic<int> leftclickCount(0);
std::atomic<int> rightclickCount(0);
std::atomic<bool> inLeftClickDetection(
    false); // Flag to ensure only one detection thread runs
std::atomic<bool> inRightClickDetection(
    false); // Flag to ensure only one detection thread runs
//

// Keyboard Monitor to monitor key presses through IOKIT/Carbon
KeyboardMonitor keyboardMonitor;

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

void detectLeftDoubleClick(int timeoutMs) {

  inLeftClickDetection = true;

  std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));
  if (leftclickCount == 2) {
    std::cout << "Double Left Click Detected" << std::endl;
    mouseStates[kCGEventLeftMouseDown].doubleClick = true;
  } else if (leftclickCount == 1) {

    std::cout << "Single Left Click Detected" << std::endl;
    std::thread postLeftClick(postSingleLeftClick);
    postLeftClick.detach();
  }
  leftclickCount = 0;
  inLeftClickDetection = false;
}
void detectRightDoubleClick(int timeoutMs) {
  inRightClickDetection = true;
  std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));
  if (rightclickCount == 2) {
    std::cout << "Double Right Click Detected" << std::endl;
    mouseStates[kCGEventRightMouseDown].doubleClick = true;
  } else if (rightclickCount == 1) {

    std::cout << "Single Right Click Detected" << std::endl;
    std::thread postRightClick(postSingleRightClick);
    postRightClick.detach();
  }
  rightclickCount = 0;
  inRightClickDetection = false;
}
// ----------------End Double click detect --
//
//
// To the sequence of Key Presses
void runSequence(const std::vector<AdvancedButtonPress> &sequence) {
  // Advanced Key Presses

  dispatch_async(
      dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        AdvancedKeyboardSimulator::simulateAdvancedMultiButtonPress(sequence);
      });
}

void avoidModifierKey(CGEventRef &event, CGEventFlags flag) {
  CGEventFlags currentflags = CGEventGetFlags(event);
  CGEventFlags newFlags = currentflags & ~flag;
  CGEventSetFlags(event, newFlags);
}

// Event CallBack Function
CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type,
                         CGEventRef event, void *refcon) {

 
  if (keyboardMonitor.isAltKeyPressed()) {
    std::cout << " Alt is pressed " << std::endl;
  }
  if (type == kCGEventRightMouseDown) {

    rightclickCount++;          // Increament click count
    if (!inRightClickDetection) // Start a new detection thread only if not
                                // already running
    {
      std::thread detectThread(detectRightDoubleClick, 180);
      detectThread.detach();
    }
    return nullptr;
  }

  if (type == kCGEventLeftMouseDown) {
    leftclickCount++;          // Increament click count
    if (!inLeftClickDetection) // Start a new detection thread only if not
                               // already running
    {
      std::thread detectThread(detectLeftDoubleClick, 180);
      detectThread.detach();
    }
    return nullptr;
  }

  // KEY DOWN EVENTS
  if (type == kCGEventKeyDown) {

    CGKeyCode keyCode =
        (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    if (keyCode == kVK_ANSI_W) {
      keyStates[kVK_ANSI_W].state = true;
    }
    if (keyCode == kVK_ANSI_E) {
      keyStates[kVK_ANSI_E].state = true;
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
  }

  // ---------------------------- All the macros defined below

  // alt + double right click
  if (keyboardMonitor.isAltKeyPressed() &&
      mouseStates[kCGEventRightMouseDown].doubleClick) {
    mouseStates[kCGEventRightMouseDown].state = false;
    mouseStates[kCGEventRightMouseDown].doubleClick = false;
    std::cout << "alt and double right click" << std::endl;
  }
  // otherwise alt + right click
  if (keyboardMonitor.isAltKeyPressed() &&
      mouseStates[kCGEventRightMouseDown].state) {

    mouseStates[kCGEventRightMouseDown].state = false;
    std::cout << "alt and right click " << std::endl;
    runSequence(seq4);
  }

  // alt + double left click
  if (flagsStates[kCGEventFlagMaskAlternate].state &&
      mouseStates[kCGEventLeftMouseDown].doubleClick) {
    mouseStates[kCGEventLeftMouseDown].state = false;
    mouseStates[kCGEventLeftMouseDown].doubleClick = false;
    std::cout << "alt and double left click" << std::endl;
  }
  // alt + left click
  if (flagsStates[kCGEventFlagMaskAlternate].state &&
      mouseStates[kCGEventLeftMouseDown].state) {
    std::cout << " alt and left click " << std::endl;
    // runSequence(seq5);
  }

  // both mouse button click
  if (flagsStates[kCGEventRightMouseDown].state &&
      flagsStates[kCGEventLeftMouseDown].state) {
  }

  // right double click
  if (flagsStates[kCGEventRightMouseDown].doubleClick) {
    std::cout << " sequence about to run right double click" << std::endl;
    //  runSequence(seq4);
  }
  // left double click
  if (flagsStates[kCGEventLeftMouseDown].doubleClick) {
    std::cout << " sequence about to run left double click" << std::endl;
  }
  //
  // alt + w
  if (keyStates[kVK_ANSI_W].state &&
      flagsStates[kCGEventFlagMaskAlternate].state) {

  } else if (keyStates[kVK_ANSI_W].state &&
             !flagsStates[kCGEventFlagMaskAlternate].state) {

    //  std::cout << "E ONLY PRESSED" << std::endl;
  }

  // alt + e
  if (keyStates[kVK_ANSI_E].state &&
      flagsStates[kCGEventFlagMaskAlternate].state) {
    // to avoid alt modifier to linger when the sequence of presses
    // are being executed
    avoidModifierKey(
        event, kCGEventFlagMaskAlternate); // avoid or unpress Alt modifier key

    // Similarly to unpress the E to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);

    // Press the keys of the sequence, passed
    runSequence(seq1);
  }

  // turn off doubleClick flag for next iteration
  mouseStates[kCGEventLeftMouseDown].doubleClick = false;
  mouseStates[kCGEventRightMouseDown].doubleClick = false;

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
      CGEventMaskBit(kCGEventKeyUp) | CGEventMaskBit(kCGEventFlagsChanged);

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
