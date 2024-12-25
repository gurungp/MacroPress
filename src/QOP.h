
#pragma once

#include "AdvancedKeyboardSimulator.h"
#include "InputMonitor.h"
// Queen of Pain
CGEventRef QueenOfPain(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

//-------------QOP---------------

static std::vector<AdvancedButtonPress3> seqQOP1 = {
    {{13}, {}, 10, 20, 45},               // w
    {{19, 12, 14, 1}, {56}, 130, 20, 55}, // (2, q , e , s ) all with shift
                                          // {{13,19,12, 14, 1}, {56}, 140, 55}, // w, 2, q , e , s
};

static std::vector<AdvancedButtonPress3> seqQOP2 = {

    {{13}, {}, 10, 20, 45},                      // w
    {{19, 3, 201, 12, 14, 1}, {56}, 90, 20, 55}, // ( 2,f,left click, q , e , s ) all with shift
};
