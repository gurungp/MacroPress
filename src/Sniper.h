

#pragma once

#include "InputMonitor.h"
#include <CoreGraphics/CGEventTypes.h>

// Legion Commander
CGEventRef Sniper(const InputMonitor &inputMonitor,
                  const KeyboardMonitor &keyboardMonitor, CGEventRef &event);
