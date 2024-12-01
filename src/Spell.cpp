
#pragma once
#include "Spell.h"
#include "SSM.h"
#include <cmath>
#include <cstdlib>
// #include <filesystem>
#include <iostream>

Spell::Spell(std::initializer_list<double> times)
    : SSM(ST_MAXSTATES), m_cooldown(0), m_spellLevel(0), m_spellCDTimes(times),
      m_spellCDTimesDefault(times),
      m_lastCastTimePoint(std::chrono::system_clock::time_point{}),
      m_lastExpected_CD_FinishTime(std::chrono::system_clock::time_point{}),
      m_octarine(false),
      m_TalentUsed(false),
      m_Scepter(false),
      m_Shard(false) {
  // THE m_spellCDTimes should be set and should not be empty
}

void Spell::st_func_NotLearned(const EventData *data) {
  std::cout << std::endl;
  std::cout << "Not Learned" << std::endl;
}

void Spell::st_func_LearnAndReady(const EventData *data) {
  // std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
  const char *path = "/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Learning.mp3";
  const char *path2 = "../Sounds/General/Learning.mp3";
  m_audioPlayer.playSound(path);
  std::cout << "--------LEARN--------" << std::endl;
  // Setting current cooldown time
  m_cooldown = m_spellCDTimes[m_spellLevel];
  if (m_cooldown <= 0) {
    m_cooldown = 0;
  } else {
    m_cooldown = std::ceil(m_cooldown * 10) / 10;
  }

  std::cout << "Current Cooldown Time setting to " << m_cooldown << std::endl;

  ++m_spellLevel;
  if (m_spellLevel >= m_spellCDTimes.size())
    m_spellLevel = m_spellCDTimes.size() - 1;
}
void Spell::st_func_Casting(const EventData *data) {
  const char *path = "/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Casting.mp3";
  m_audioPlayer.playSound(path);

  std::cout << "--------CASTING--------" << std::endl;
  std::cout << "Casting and Setting Cast time" << std::endl;
  m_lastCastTimePoint = std::chrono::system_clock::now();

  // Calculate the time at which the CD will end with the current CD Time
  auto durationToAdd = std::chrono::duration_cast<std::chrono::system_clock::duration>(
      std::chrono::duration<float>(m_cooldown));

  m_lastExpected_CD_FinishTime = m_lastCastTimePoint + durationToAdd;

  std::cout << "Moving to ON_COOLDOWN state" << std::endl;
  InternalAction(ST_ON_COOLDOWN,
                 nullptr); // After casting it immediately goes to Cooldown
}
void Spell::st_func_On_Cooldown(const EventData *data) {
  std::cout << "On Cooldown" << std::endl;
}

// GUARD CONDITION FUCNTION

bool Spell::gd_func_checkIfLevelFull(const EventData *) {

  std::cout << "--------GUARD-IF-PROCEED-TO-LEVEL-UP--------" << std::endl;
  std::cout << "Current spell level is " << m_spellLevel << std::endl;
  std::cout << "Current Cooldown time is " << m_cooldown << std::endl;
  if (m_spellLevel >= m_spellCDTimes.size()) {
    std::cout << "Guard: Level Already Full" << std::endl;
    return false;
  } else {
    std::cout << "Guard: Proceed Leveling Up" << std::endl;
    return true;
  }
}

bool Spell::gd_func_checkOnCooldown(const EventData *data) {
  std::cout << "--------GUARD-CHECK-ON-COOLDOWN--------" << std::endl;

  auto currentTime = std::chrono::system_clock::now();
  std::cout << "Last expected CD time to finish: "
            << m_lastExpected_CD_FinishTime << std::endl;
  std::cout << "Current time: " << currentTime << std::endl;
  bool proceed = !onCoolDown(); // proceed = true if its not in cooldown. if its
                                // on cool down then proceeding for guard
                                // function is false otherwise guard function
                                // should proceed by equating to true
  if (proceed == true)
    std::cout << "Not on Cooldown " << std::endl;
  else
    std::cout << "Last expected CD Still not finished" << std::endl;

  return proceed;
}

void Spell::learnSpell(const EventData *data) {
  static const BYTE TRANSITIONS[] = {
      ST_LEARN_AND_READY, // NOT_LEARNED,
      ST_LEARN_AND_READY, // LEARN AND READY,
      ST_LEARN_AND_READY, // CASTING,
      ST_LEARN_AND_READY, // ON_COOLDOWN
  };

  ExternalEvent(TRANSITIONS[getCurrentState()], data);
}

void Spell::castSpell(const EventData *data) {

  static const BYTE TRANSITIONS[] = {
      EVENT_IGNORED, // NOT_LEARNED
      ST_CASTING,    // LEARN AND READY
      ST_CASTING,    // CASTING
      ST_CASTING,    // ON_COOLDOWN
  };
  ExternalEvent(TRANSITIONS[getCurrentState()], data);
}

void Spell::setCooldown(double time) {
  m_cooldown = time;
}

bool Spell::onCoolDown() {
  auto currentTime = std::chrono::system_clock::now();
  if (m_lastExpected_CD_FinishTime < currentTime) {
    return false; // if the last expected CD finish time is already passed(less
                  // than current time) then onCooldown is false or it is not on
                  // cool down
  } else {
    //  m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/On Cooldown.mp3");
    return true;
  }
}
void Spell::useRefresher() {

  // m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Refresher on.mp3");
  m_lastCastTimePoint = std::chrono::system_clock::time_point{};
  m_lastExpected_CD_FinishTime = std::chrono::system_clock::time_point{};
}

void Spell::setOctarine(bool value) {
  if (m_octarine == value) { // if the Octarine is already on, don't apply the CD Reduction
    return;
  } else {
    m_octarine = value;
  }
  // m_spellCDTimes = m_spellCDTimesDefault; // Because talent might have been used which decreases CD
  if (m_octarine) {

    //   m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Octarine On.mp3");
    for (int i = 0; i < m_spellCDTimes.size(); i++) {
      double spell_time = m_spellCDTimes[i];
      m_spellCDTimes[i] = (0.75 * spell_time); // or , m_spellCDTimes[i] = (spell_time) - (0.25 * spell_time);
    }
  } else {

    //   m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Octarine Off.mp3");
    //    m_spellCDTimes = m_spellCDTimesDefault;
    for (int i = 0; i < m_spellCDTimes.size(); i++) {
      double spell_time = m_spellCDTimes[i];
      m_spellCDTimes[i] = (spell_time) / (0.75);
    }
  }
  // Updating the m_cooldown to its correct CD time

  m_cooldown = m_spellCDTimes[m_spellLevel];
  if (m_cooldown <= 0) {
    m_cooldown = 0;
  } else {
    m_cooldown = std::ceil(m_cooldown * 10) / 10;
  }
}

void Spell::useTalent(double seconds) {

  if (m_TalentUsed) {
    std::cout << "Talent Already used " << std::endl;
    return;
  }

  m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Talent Set.mp3");
  m_TalentUsed = true;
  // Now we should check if Octarine was used before using the talent
  if (m_octarine) { // if octarine was already in use , we need to re-calculate CD
                    // value (due to octarine) with the new
                    // decreased CD time due to the talent use

    for (int i = 0; i < m_spellCDTimes.size(); i++) {
      m_spellCDTimes[i] = ((m_spellCDTimes[i] / (0.75)) - seconds) * 0.75; // First unapply the Octarine then deduct the Talent CD
                                                                           // Then reapply the Octarine which is same as multiplying with 75%
                                                                           // because deducting 25% of the original number is the same as
                                                                           // taking the 75% of the original number only
    }
  } else {
    // Just deduct the Talent CD
    for (int i = 0; i < m_spellCDTimes.size(); i++) {
      m_spellCDTimes[i] = m_spellCDTimes[i] - seconds;
    }
  }
  // Updating the current cooldown time with the latest Cooldown times

  m_cooldown = m_spellCDTimes[m_spellLevel];
  if (m_cooldown <= 0) {
    m_cooldown = 0;
  } else {
    m_cooldown = std::ceil(m_cooldown * 10) / 10;
  }
}

void Spell::setScepter(bool set, double seconds) {

  if (m_Scepter == set) // if Scepter is already set and set=true, true==true, or set,  and also
                        // if Scepter is false and set=false , false==false, or unset, then do nothing
  {
    return;
  }

  if (set == true) {

    m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Scepter On.mp3");
    m_Scepter = true;
    // Now we should check if Octarine was used before using the talent
    if (m_octarine) { // if octarine was already in use , we need to re-calculate CD
                      // value (due to octarine) with the new
                      // decreased CD time due to the talent use

      for (int i = 0; i < m_spellCDTimes.size(); i++) {
        m_spellCDTimes[i] = ((m_spellCDTimes[i] / (0.75)) - seconds) * 0.75; // First unapply the Octarine then deduct the Talent CD
                                                                             // Then reapply the Octarine which is same as multiplying with 75%
                                                                             // because deducting 25% of the original number is the same as
                                                                             // taking the 75% of the original number only
      }
    } else {
      // Just decrease the Seconds
      for (int i = 0; i < m_spellCDTimes.size(); i++) {
        m_spellCDTimes[i] = m_spellCDTimes[i] - seconds;
      }
    }
  } else {          // if set is false, or Unset Scepter
    if (m_octarine) // taking into account if Octarine is on or Off
    {
      for (int i = 0; i < m_spellCDTimes.size(); i++)
        m_spellCDTimes[i] = ((m_spellCDTimes[i] / (0.75)) + seconds) * 0.75;
    } else {

      for (int i = 0; i < m_spellCDTimes.size(); i++)
        m_spellCDTimes[i] = m_spellCDTimes[i] + seconds;
    }

    m_Scepter = false;
    m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Scepter Off.mp3");
  }

  // Updating the current cooldown time with the latest Cooldown times
  m_cooldown = m_spellCDTimes[m_spellLevel];
  if (m_cooldown <= 0) {
    m_cooldown = 0;
  } else {
    m_cooldown = std::ceil(m_cooldown * 10) / 10;
  }
}

void Spell::setShard(bool set, double seconds) {

  if (m_Shard == set) // if Shard is already set and set=true, true==true, or set,  and also
                      // if Shard is false and set=false , false==false, or unset, then do nothing
  {
    return;
  }

  if (set == true) {

    m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Shard On.mp3");
    m_Shard = true;
    // Now we should check if Octarine was used before using the talent
    if (m_octarine) { // if octarine was already in use , we need to re-calculate CD
                      // value (due to octarine) with the new
                      // decreased CD time due to the talent use

      for (int i = 0; i < m_spellCDTimes.size(); i++) {
        m_spellCDTimes[i] = ((m_spellCDTimes[i] / (0.75)) - seconds) * 0.75; // First unapply the Octarine then deduct the Talent CD
                                                                             // Then reapply the Octarine which is same as multiplying with 75%
                                                                             // because deducting 25% of the original number is the same as
                                                                             // taking the 75% of the original number only
      }
    } else {
      // Just decrease the Seconds
      for (int i = 0; i < m_spellCDTimes.size(); i++) {
        m_spellCDTimes[i] = m_spellCDTimes[i] - seconds;
      }
    }
  } else {          // if set is false, or Unset Shard
    if (m_octarine) // taking into account if Octarine is on or Off
    {
      for (int i = 0; i < m_spellCDTimes.size(); i++)
        m_spellCDTimes[i] = ((m_spellCDTimes[i] / (0.75)) + seconds) * 0.75;
    } else {

      for (int i = 0; i < m_spellCDTimes.size(); i++)
        m_spellCDTimes[i] = m_spellCDTimes[i] + seconds;
    }

    m_Shard = false;
    m_audioPlayer.playSound("/Users/prashantgurung/Programming/keyboardSim2/Sounds/General/Shard Off.mp3");
  }

  // Updating the current cooldown time with the latest Cooldown times

  m_cooldown = m_spellCDTimes[m_spellLevel];
  if (m_cooldown <= 0) {
    m_cooldown = 0;
  } else {
    m_cooldown = std::ceil(m_cooldown * 10) / 10;
  }
}

void Spell::print_SpellTimes() {
  int i = 1;
  for (double time : m_spellCDTimes) {
    std::cout << i << ". Time: " << time << std::endl;
    i++;
  }
  std::cout << std::endl;
}
