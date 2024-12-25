

#pragma once

#include "InputMonitor.h"
#include "Sequence.h"

CGEventRef Chen(const InputMonitor &inputMonitor,
                const KeyboardMonitor &keyboardMonitor, CGEventRef &event);

static std::vector<AdvancedButtonPress3> seqChenGen = {
    {{9}, {}, 100, 20, 100}, // v (Select all)

};

static std::vector<AdvancedButtonPress3> seqChen1 = {
    {{22, 12}, {}, 100, 20, 100}, // 6, q
    {{200}, {56}, 360, 20, 100},  // Shift + right Click
    {{37}, {}, 560, 20, 100},     // l(Ctrl group l) , select the rest of units including chen
};

static std::vector<AdvancedButtonPress3> seqChen2 = {

    {{26, 12, 13}, {}, 100, 20, 100}, // 7,q,w
    {{200}, {56}, 530, 20, 100},      // Shift + right Click

    {{41}, {}, 760, 20, 100}, // ;(Ctrl group ;) , select the rest of units including chen
};
static std::vector<AdvancedButtonPress3> seqChen3 = {
    {{28, 12, 13, 14}, {}, 100, 20, 100}, // 8, q,w,e
    {{200}, {56}, 630, 20, 100},          // Shift + right Click

    {{39}, {}, 860, 20, 100}, // '(Ctrl group ') , select the rest of units including chen
};

static std::vector<AdvancedButtonPress3> seqChen4 = {
    // for self and allied heroes
    {{25, 12}, {}, 100, 20, 100}, // 9, q
    {{200}, {56}, 362, 20, 100},  // Shift + right Click

    {{42}, {}, 560, 20, 100}, // \(Ctrl group \) , select the rest of units including chen
};

static std::vector<AdvancedButtonPress3> seqChen5 = {
    {{23, 12}, {}, 100, 20, 100}, // 5(ctrl group 5), q
    {{200}, {56}, 362, 20, 100},  // Shift + right Click

    {{9}, {}, 560, 20, 100}, // Select all
};

static std::vector<AdvancedButtonPress3> seqChen6 = {
    // for wildwing ripper only
    {{29}, {}, 100, 20, 100},  // 0(ctrl group 0)
    {{12}, {}, 350, 500, 400}, // q
    {{20}, {}, 1450, 20, 100}, // 3
};
