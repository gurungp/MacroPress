
#pragma once

#include "AdvancedKeyboardSimulator.h"
#include <vector>

// Function to avoid modifier key
void avoidModifierKey(CGEventRef &event, CGEventFlags flag);

// Function to run a sequence of key presses
void runSequence(const std::vector<AdvancedButtonPress> &sequence);
void runSequence2(const std::vector<AdvancedButtonPress2> &sequence);

// Generic
extern std::vector<AdvancedButtonPress2> seqG1;
extern std::vector<AdvancedButtonPress2> seqG2;

// Key sequence 1: Presses q, e, tab, q, e again
extern std::vector<AdvancedButtonPress> seq1;

// Key sequence 2: Selects main hero and presses q, e
extern std::vector<AdvancedButtonPress> seq2;

// Key sequence 3: Selects clone and presses q, e
extern std::vector<AdvancedButtonPress> seq3;

// Key sequence 4: Selects main hero and right-clicks
extern std::vector<AdvancedButtonPress> seq4;

// Key sequence 5: Selects clone and right-clicks
extern std::vector<AdvancedButtonPress> seq5;

// Key sequence 6: Selects both hero and clone with ctrl group 9
extern std::vector<AdvancedButtonPress> seq6;

// Key sequence 7: Complex sequence with clone, main hero, and ctrl group 9
extern std::vector<AdvancedButtonPress> seq7;

// Key sequence for Legion Commander

// minimum items and ult
extern std::vector<AdvancedButtonPress2> seqLC1;

// more items and ult
extern std::vector<AdvancedButtonPress> seqLC2;

// Enable all items and ult
extern std::vector<AdvancedButtonPress2> seqLC3;

// Key sequence for Tusk
extern std::vector<AdvancedButtonPress> seqTusk1;

// Key sequence for Earth Spirit
extern std::vector<AdvancedButtonPress2> seqESpirit1;
extern std::vector<AdvancedButtonPress> seqESpirit2;
extern std::vector<AdvancedButtonPress2> seqESpirit3;

// Key sequence for Lone Druid
extern std::vector<AdvancedButtonPress2> seqLD1A;
extern std::vector<AdvancedButtonPress2> seqLD2B;

extern std::vector<AdvancedButtonPress2> seqLD2;
extern std::vector<AdvancedButtonPress2> seqLD3;
extern std::vector<AdvancedButtonPress2> seqLD4;
extern std::vector<AdvancedButtonPress> seqLD5;

// test New Way of pressing
extern std::vector<AdvancedButtonPress2> seqTest1;
extern std::vector<AdvancedButtonPress2> seqTest2;
extern std::vector<AdvancedButtonPress2> seqTest3;
