
#pragma once

#include "InputMonitor.h"
#include <CoreGraphics/CGEventTypes.h>

// Queen of Pain
CGEventRef QueenOfPain(const InputMonitor &inputMonitor,
                       const KeyboardMonitor &keyboardMonitor, CGEventRef &event);
