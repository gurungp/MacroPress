
#pragma once

#include "AdvancedKeyboardSimulator.h"
#include <vector>

// Function to avoid modifier key
void avoidModifierKey(CGEventRef &event, CGEventFlags flag);

// Function to run a sequence of key presses
void runSequence2(const std::vector<AdvancedButtonPress2> &sequence);
void runSequence3(const std::vector<AdvancedButtonPress3> &sequence);

// Generic
extern std::vector<AdvancedButtonPress2> seqG1;
extern std::vector<AdvancedButtonPress2> seqG2;

// Key sequence 1: Presses q, e, tab, q, e again
extern std::vector<AdvancedButtonPress2> seqArc1;

// Key sequence 2: Selects main hero and presses q, e
extern std::vector<AdvancedButtonPress2> seqArc2;

// Key sequence 3: Selects clone and presses q, e
extern std::vector<AdvancedButtonPress2> seqArc3;

// Key sequence 4: Selects main hero and right-clicks
extern std::vector<AdvancedButtonPress2> seqArc4;

// Key sequence 5: Selects clone and right-clicks
extern std::vector<AdvancedButtonPress2> seqArc5;

// Key sequence 6: Selects both hero and clone with ctrl group 9
extern std::vector<AdvancedButtonPress2> seqArc6;

// Key sequence 7: Complex sequence with clone, main hero, and ctrl group 9
extern std::vector<AdvancedButtonPress2> seqArc7;

// Key sequence for Legion Commander

// minimum items and ult
extern std::vector<AdvancedButtonPress2> seqLC1;

// Enable all items and ult
extern std::vector<AdvancedButtonPress2> seqLC3;

// Key sequence for Tusk
extern std::vector<AdvancedButtonPress2> seqTusk1;

// Key sequence for Sniper

extern std::vector<AdvancedButtonPress2> seqSnipe1;


// Key sequence for Tinker
extern std::vector<AdvancedButtonPress3> seqTinker1;
extern std::vector<AdvancedButtonPress3> seqTinker2;
extern std::vector<AdvancedButtonPress3> seqTinker3;
extern std::vector<AdvancedButtonPress3> seqTinker4;

// test New Way of pressing
extern std::vector<AdvancedButtonPress2> seqTest1;
extern std::vector<AdvancedButtonPress2> seqTest2;
extern std::vector<AdvancedButtonPress2> seqTest3;
