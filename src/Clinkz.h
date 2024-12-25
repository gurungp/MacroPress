

#pragma once

#include "InputMonitor.h"
#include "Sequence.h"

CGEventRef Clinkz(const InputMonitor &inputMonitor,
                  const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

static std::vector<AdvancedButtonPress3> seqClinkz1 = {
    {{19, 12, 13, 200}, {}, 100, 20, 100}, // 2,q,w,right click
};

static std::vector<AdvancedButtonPress3> seqClinkz2 = {

    {{1, 19, 12, 13, 200}, {}, 100, 20, 100}, // s(Hex),2,q,w,right click
};
static std::vector<AdvancedButtonPress3> seqClinkz3 = {

    {{1, 19, 12, 17, 13, 200}, {}, 100, 20, 100}, // s(Hex),2,q,t(Aghanim),w, right click

};
