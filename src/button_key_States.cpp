#pragma once

#include "button_key_States.h"
#include <CoreGraphics/CGEventTypes.h>
#include <CoreGraphics/CGRemoteOperation.h>

// key states of modifier keys
std::unordered_map<CGKeyCode, buttonState> keyStates = {

    {kVK_ANSI_W, buttonState()},
    {kVK_ANSI_Q, buttonState()},
    {kVK_ANSI_E, buttonState()},
    {kVK_ANSI_R, buttonState()},
    {kVK_ANSI_P, buttonState()},
    {kVK_ANSI_O, buttonState()},
    {kVK_ANSI_L, buttonState()},
    {kVK_ANSI_K, buttonState()},
    {kVK_ANSI_I, buttonState()},
    {kVK_ANSI_D, buttonState()},
    {kVK_ANSI_T, buttonState()},
    {kVK_ANSI_F, buttonState()},
    {kVK_ANSI_V, buttonState()},
    {kVK_ANSI_2, buttonState()},
    {kVK_ANSI_3, buttonState()},
    {kVK_ANSI_4, buttonState()},
    {kVK_ANSI_5, buttonState()},
    {kVK_ANSI_6, buttonState()},
    {kVK_ANSI_7, buttonState()},
    {kVK_ANSI_8, buttonState()},
    {kVK_ANSI_9, buttonState()},
    {kVK_ANSI_0, buttonState()},
    {kVK_ANSI_X, buttonState()},
    {kVK_ANSI_C, buttonState()},
    {kVK_ANSI_Semicolon, buttonState()},

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
