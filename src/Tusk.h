
#pragma once

#include "InputMonitor.h"
#include "Spell.h"

// Tusk
CGEventRef Tusk(const InputMonitor &inputMonitor,
                const KeyboardMonitor &keyboardMonitor, CGEventRef &event);
