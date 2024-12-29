
#include "Sequence.h"
#include <CoreFoundation/CFBase.h>
#include <CoreGraphics/CGEventTypes.h>
#include <dispatch/dispatch.h>

dispatch_queue_t seqQueue = dispatch_queue_create("com.example.Queue", DISPATCH_QUEUE_SERIAL);
void avoidModifierKey(CGEventRef &event, CGEventFlags flag) {
  CGEventFlags flags = CGEventGetFlags(event);
  CGEventSetType(event, kCGEventKeyUp);
  CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode, kVK_Option);
  CGEventSetFlags(event, flags & ~flag);

  //  CGEventFlags currentflags = CGEventGetFlags(event);
  // CGEventFlags newFlags = currentflags & ~flag;
  // CGEventSetFlags(event, newFlags);

  // CGEventRef altKeyUp = CGEventCreateKeyboardEvent(NULL, kVK_Option, false);
  // CGEventPost(kCGHIDEventTap, altKeyUp);
  // CFRelease(altKeyUp);
}
void asyncSleep(dispatch_queue_t queue, // The queue where task will run
                double seconds          // How long to sleep
) {
  // Step 1: Add task to specified queue
  dispatch_async(queue, ^{
    // Step 2: Create a semaphore with initial value 0
    dispatch_semaphore_t sema = dispatch_semaphore_create(0);

    // Step 3: Schedule a delayed signal
    dispatch_after(
        dispatch_time(DISPATCH_TIME_NOW, seconds * NSEC_PER_MSEC),     // When to wake
        dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), // Queue for timer
        ^{
          dispatch_semaphore_signal(sema); // Wake up the waiting task
        });

    // Step 4: Wait for the signal
    dispatch_semaphore_wait(sema, DISPATCH_TIME_FOREVER);
  });
}
void runSequence2(const std::vector<AdvancedButtonPress2> &sequence) {
  // Advanced Key Presses
  //
  dispatch_async(
      dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        AdvancedKeyboardSimulator::simulateAdvancedMultiButtonPress2(sequence);
      });
}

void runSequence3(const std::vector<AdvancedButtonPress3> &sequence) {
  // Advanced Key Presses
  //
  dispatch_async(
      dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        AdvancedKeyboardSimulator::simulateAdvancedMultiButtonPress3(sequence);
      });
}
void runSequence4(const std::vector<AdvancedButtonPress3> &sequences, double delay) {
  // Advanced Key Presses

  // Delay Before Executing the sequence itself
  dispatch_time_t delaytime = dispatch_time(DISPATCH_TIME_NOW, delay * NSEC_PER_MSEC);

  std::cout << " Waiting for " << delay << "\n";
  asyncSleep(seqQueue, delay);

  dispatch_async(seqQueue, ^{
    // This block is left empty intentionally as we just need the delay

    AdvancedKeyboardSimulator::simulateAdvancedMultiButtonPress3(sequences);
  });
}
// 200 for right click
// 201 for left click
// 58 for alt
// 56 for shift, For best result working with shift, also add times to shift
// and auto attacks should be disabled
// 79 is arbitarily chosen number to say that no modifier is pressed. 79 = 0x4f
// = kVK_F18 Arc Warden

// Generic
std::vector<AdvancedButtonPress2> seqG1 = {
    {{200}, {58}, 140, 50}, // Alt + Right click

};

std::vector<AdvancedButtonPress2> seqG2 = {
    {{201}, {58}, 140, 50}, // Alt + Left click

};

// Arc Warden
// Key sequence 1
//  Presses q then e, and tab and then q and e again

std::vector<AdvancedButtonPress2> seqArc1 = {
    // Advanced Buttun Press 2 Version
    {{12}, {}, 140, 70},  // the delay 140ms is necessary because the game won't
                          // register fast key press at the beginning
    {{14}, {}, 650, 60},  // e
    {{23}, {}, 780, 70},  // 5
    {{12}, {}, 900, 60},  // q
    {{14}, {}, 1460, 70}, // e
    {{25}, {}, 1600, 60}  // 9 // ctrl grp 9
};

// Key sequence 2
//  Selects main hero and then presses q and e

std::vector<AdvancedButtonPress2> seqArc2 = {
    {{20}, {}, 140, 60}, // 3
    {{12}, {}, 290, 55}, // q
    {{14}, {}, 750, 53}, // e
    {{25}, {}, 1000, 57} // 9
};

// Key sequence 3
//  Selects clone and then presses q and e

std::vector<AdvancedButtonPress2> seqArc3 = {
    {{23}, {}, 140, 60}, // 5
    {{12}, {}, 290, 55}, // q
    {{14}, {}, 750, 53}, // e
    {{25}, {}, 1000, 57} // 9
};

// Key sequence 4
//  selects main hero and right clicks and select both

std::vector<AdvancedButtonPress2> seqArc4 = {
    {{20}, {}, 140, 60},  // 3
    {{200}, {}, 300, 55}, // right click
};
// selects clone and right clicks and select both

std::vector<AdvancedButtonPress2> seqArc5 = {
    {{23}, {}, 140, 60},  // 5
    {{200}, {}, 300, 55}, // right click
};

// select both hero and clone only with ctrl group 9

std::vector<AdvancedButtonPress2> seqArc6 = {
    {{25}, {}, 150, 50} // 9
};

//  Presses select clone, press f, press s, press w,
// select main here, press w , press 2 , select ctrl group 9

std::vector<AdvancedButtonPress2> seqArc7 = {
    {{23}, {}, 140, 70},  // 5
    {{3}, {}, 250, 55},   // f
    {{201}, {}, 420, 60}, // Left Click
    {{1}, {}, 660, 70},   // s
    {{58}, {}, 0, 0},     // alt
    {{13}, {}, 765, 60},  // w
    {{19}, {}, 920, 60},  // 2
    {{23}, {}, 1080, 70}, // 5
    {{20}, {}, 1250, 55}, // 3
    {{58}, {}, 0, 0},     // alt
    {{13}, {}, 1400, 60}, // w
    {{19}, {}, 1580, 60}, // 2
    {{25}, {}, 1890, 60}  // 9
};

// --------------Legion-Commander-----
std::vector<AdvancedButtonPress2> seqLC1 = {
    {{13}, {58}, 140, 50},   // alt+w
    {{3}, {}, 340, 55},      // f
    {{201}, {}, 520, 55},    // left click
    {{12}, {}, 670, 55},     // q
    {{0}, {56}, 850, 60},    // shift + a
    {{4, 15}, {}, 1000, 60}, // h + r
                             // h ->hold to stop auto attack before r

};

std::vector<AdvancedButtonPress2> seqLC3 = {
    {{13}, {58}, 140, 50},      // alt+w
    {{3}, {}, 340, 55},         // f
    {{201}, {}, 520, 55},       // left click
    {{12}, {}, 670, 55},        // q
    {{0}, {56}, 850, 60},       // shift + a , a=blademill
    {{4, 6, 15}, {}, 1000, 60}, // h + z + r  , z =bkb
                                // h ->hold to stop auto attack before r

};

// -------------Tusk---------------------

std::vector<AdvancedButtonPress2> seqTusk1 = {
    // {56, 0, 0},     // shift
    {{3}, {}, 140, 55},   // f
    {{201}, {}, 240, 60}, // Left Click
                          //  {56, 0, 0},     // Shift
    {{15}, {}, 380, 55},  // r
                          // {56, 0, 0},     // Shift
    {{13}, {}, 500, 60},  // w
                          // {56, 0, 0},     // shift
    {{2}, {}, 600, 1050}, // d
                          //    {6, 1120, 55},  // z
                          //   {1, 1300, 60},  // s=1
                          //    {15, 1490, 54}  // r

};

std::vector<AdvancedButtonPress2> seqTest1 = {
    {{56}, {79}, 140, 320}, // shift (shift is 56)
    {{1}, {79}, 320, 60},
    // {{56}, {79, 50, 56}, 440, 350},
    // {{19}, {79}, 640, 60},
    //{{20}, {79}, 800, 56},
};

std::vector<AdvancedButtonPress2> seqTest2 = {
    {{23}, {}, 140, 55},       // 5  , empty brackest mean no modifier key set
    {{0, 201}, {56}, 280, 60}, // shift + a + left-click
    {{1}, {56}, 390, 59},      // shift + s
    {{19}, {56}, 550, 55},     // shift + 2
    {{20}, {}, 640, 56},
    // {{56}, {79, 50, 56}, 440, 350},
    // {{19}, {79}, 640, 60},
    //{{20}, {79}, 800, 56},
};

std::vector<AdvancedButtonPress2> seqTest3 = {
    {{23}, {}, 140, 55},              // 5  , empty brackest mean no modifier key set
    {{0, 201, 1, 19}, {56}, 300, 60}, // shift + a + left-click + s + 2
    {{20}, {}, 750, 56},              // 3
                                      // {{56}, {79, 50, 56}, 440, 350},
                                      // {{19}, {79}, 640, 60},
                                      //{{20}, {79}, 800, 56},
};

//-------------Sniper---------------
std::vector<AdvancedButtonPress2> seqSnipe1 = {
    {{14, 1, 200}, {}, 140, 55}, // e then s then right click
};

//-------------Tinker------------
std::vector<AdvancedButtonPress3> seqTinker1 = {
    {{6, 201, 0, 201}, {}, 100, 20, 40}, // z,left click,a, left click
    {{19, 12, 15, 1}, {}, 350, 20, 70},  // 2,q,s,r
};
std::vector<AdvancedButtonPress3> seqTinker2 = {
    {{6, 201, 0, 201}, {}, 100, 20, 40}, // z,left click,a, left click
    {{14}, {58}, 300, 20, 60},           // alt + e
    {{19, 12, 15, 1}, {}, 590, 20, 120}, // 2,q,s,r
};

std::vector<AdvancedButtonPress3> seqTinker3 = {
    {{3, 201, 6, 201, 0, 201}, {}, 100, 20, 40}, // f(Blink),left click,z,left click,a, left click
    {{19, 12, 15, 1}, {}, 400, 20, 70},          // 2,q,s,r
};
std::vector<AdvancedButtonPress3> seqTinker4 = {
    {{3, 201, 6, 201, 0, 201}, {}, 100, 20, 40}, // f(Blink),left click,z,left click,a, left click
    {{14}, {58}, 350, 20, 40},                   // alt + e
    {{19, 12, 15, 1}, {}, 630, 20, 120},         // 2,q,s,r
};
