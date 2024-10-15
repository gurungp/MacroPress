#pragma once

#include "button_key_States.h"
#include <CoreGraphics/CGEventTypes.h>
#include <CoreGraphics/CGRemoteOperation.h>
#include <vector>

// key states of modifier keys
std::unordered_map<CGKeyCode, buttonState> keyStates = {
    {kVK_ANSI_W, buttonState()},
    {kVK_ANSI_E, buttonState()},
    {kVK_ANSI_R, buttonState()},
    {kVK_Control, buttonState()},
    {kVK_Option, buttonState()},

};

std::unordered_map<CGEventType, buttonState> mouseStates = {
    {kCGEventLeftMouseDown, buttonState()},
    {kCGEventRightMouseDown, buttonState()},
    {kCGEventLeftMouseUp, buttonState()},
    {kCGEventRightMouseUp, buttonState()},
    {kCGEventOtherMouseDown, buttonState()},
    {kCGEventOtherMouseUp, buttonState()}

};

std::unordered_map<CGEventFlags, buttonState> flagsStates = {
    {kCGEventFlagMaskAlternate, buttonState()},
    {kCGEventFlagMaskControl, buttonState()},
    {kCGEventFlagMaskShift, buttonState()},
};

std::unordered_map<CGKeyCode, CGEventFlags> modifierStates = {
    {kVK_Shift, kCGEventFlagMaskShift},
    {kVK_Control, kCGEventFlagMaskControl},
    {kVK_Option, kCGEventFlagMaskAlternate}};
