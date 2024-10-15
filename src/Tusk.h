
#pragma once

#include "InputMonitor.h"

// Tusk
CGEventRef Tusk(const InputMonitor &inputMonitor,
                const KeyboardMonitor &keyboardMonitor, CGEventRef &event);
