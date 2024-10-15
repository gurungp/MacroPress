
#pragma once

#include "InputMonitor.h"
#include <CoreGraphics/CGEventTypes.h>

// Legion Commander
CGEventRef LoneDruid(const InputMonitor &inputMonitor,
                     const KeyboardMonitor &keyboardMonitor, CGEventRef &event);
