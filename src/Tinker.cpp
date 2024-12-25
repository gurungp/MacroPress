#pragma once

#include "Tinker.h"
#include "PlaySound.h"
#include "Sequence.h"
#include "Spell.h"
#include "button_key_States.h"
#include <dispatch/dispatch.h>

static Spell Blink{15.45};
static Spell Laser{19.0, 18.0, 17.0, 16.0};
static Spell March{35.0, 33.0, 31.0, 29.0};
static Spell Defense{20.0};
static Spell Rearm{7.0, 6.0, 5.0};
static Spell Warp{15.0};
static double timetoRearm[] = {2.80, 2.10, 1.30};
static double rearmTime = 0.0;
bool rearming = false;

static PlaySound soundPlayer;
// Create a dispatch queue for asynchronous use of callback
static dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

// Tinker

void waitForTime(double sec) {
  // run the waitRearmTime function after the rearm time is over which will set the rearming to false.
  dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), queue, ^{
    setRearm();
  });
}

void setRearm() {
  std::cout << "Setting rearming back to false" << std::endl;
  rearming = false;
  Rearm.useRefresher();
}

CGEventRef Tinker(const InputMonitor &inputMonitor,
                  const KeyboardMonitor &keyboardMonitor,
                  CGEventRef &event) {
  // If Tinker is currently rearming then do nothing so that right click won't break the rearming
  if (rearming && inputMonitor.isRightClicked()) {
    std::cout << "Right click not possible, rearming in process" << std::endl;
    return nullptr;
  }

  if (keyStates[kVK_ANSI_L].state) {
    if (Rearm.m_spellLevel <= Rearm.m_spellCDTimes.size()) {

      rearmTime = timetoRearm[Rearm.m_spellLevel];
      Rearm.learnSpell(nullptr);
      std::cout << "Rearm Spell Level : " << Rearm.m_spellLevel << " Rearm Spell CD Times size : " << Rearm.m_spellCDTimes.size()
                << std::endl;
      soundPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/Tinker/Rearm.mp3");
      std::cout << "Current Rearm time is " << rearmTime << std::endl;
    }
    return nullptr;
  }

  if (keyStates[kVK_ANSI_Q].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Rearm.m_spellLevel <= 0) {
        std::cout << "Rearm Not Learned " << std::endl;
        // return nullptr;
      } else if (rearming) {
        std::cout << "Rearming in process " << std::endl;
        //  return nullptr;
      } else if (Rearm.onCoolDown()) {
        std::cout << "Rearm on Cool down" << std::endl;
        //  return nullptr;
      } else {

        rearming = true;
        runSequence3(seqTinker1);
        waitForTime(rearmTime + 2.1); // +2.1 to account for the delay in casting laser
      }
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_W].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Rearm.m_spellLevel <= 0) {
        std::cout << "Rearm Not Learned " << std::endl;
        // return nullptr;
      } else if (rearming) {
        std::cout << "Rearming in process " << std::endl;
        //  return nullptr;
      } else if (Rearm.onCoolDown()) {
        std::cout << "Rearm on Cool down" << std::endl;
        //  return nullptr;
      } else {

        rearming = true;
        runSequence3(seqTinker2);
        waitForTime(rearmTime + 2.27); // 1.96 sec to account for the delay in casting laser
      }
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_3].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Rearm.m_spellLevel <= 0) {
        std::cout << "Rearm Not Learned " << std::endl;
        // return nullptr;
      } else if (rearming) {
        std::cout << "Rearming in process " << std::endl;
        //  return nullptr;
      } else if (Rearm.onCoolDown()) {
        std::cout << "Rearm on Cool down" << std::endl;
        //  return nullptr;
      } else {

        rearming = true;
        runSequence3(seqTinker3);
        waitForTime(rearmTime + 2.10); // 2.10 sec to account for the delay in casting laser
      }
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_R].state && keyboardMonitor.isAltKeyPressed()) {
    // Unpress the E or any other key, to not have effect of the keypresses
    CGEventSetType(event, kCGEventKeyUp);
    std::thread t([] {
      while (altState) { // until alt is released, don't run the sequence
      }
      if (Rearm.m_spellLevel <= 0) {
        std::cout << "Rearm Not Learned " << std::endl;
        // return nullptr;
      } else if (rearming) {
        std::cout << "Rearming in process " << std::endl;
        //  return nullptr;
      } else if (Rearm.onCoolDown()) {
        std::cout << "Rearm on Cool down" << std::endl;
        //  return nullptr;
      } else {

        rearming = true;
        runSequence3(seqTinker4);
        waitForTime(rearmTime + 2.56); // 2.56 sec to account for the delay in casting laser
      }
    });
    t.detach();

    return nullptr;
  }

  if (keyStates[kVK_ANSI_R].state) {
    if (!rearming && Rearm.m_spellLevel > 0) {
      std::cout << "Casting Rearm and Setting rearming to True" << std::endl;
      Rearm.castSpell(nullptr);
    }
  }
  return nullptr;
}
