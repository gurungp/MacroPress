#pragma once

#include "InputMonitor.h"
#include "Sequence.h"
#include "Spell.h"

// Tinker
CGEventRef Tinker(const InputMonitor &inputMonitor,
                  const KeyboardMonitor &keyboardMonitor,
                  CGEventRef &event);

void waitForTime(double sec);
void setRearm();
