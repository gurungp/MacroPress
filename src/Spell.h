//
//  Spell.h
//  SimpleStateMachine
//
//  Created by Prashant Gurung on 13/11/2024.
//

#ifndef Spell_h
#define Spell_h

#include "PlaySound.h"
#include "SSM.h"
#include <chrono>
#include <initializer_list>
#include <math.h>
#include <vector>
class Spell : public SSM {

public:
  Spell(std::initializer_list<double> times);

public:
  enum StateBase {
    ST_NOTLEARNED,
    ST_LEARN_AND_READY,
    ST_CASTING,
    ST_ON_COOLDOWN,
    ST_MAXSTATES,
  };

  double m_cooldown;
  int m_spellLevel;
  std::vector<double> m_spellCDTimes;
  std::vector<double> m_spellCDTimesDefault;
  std::chrono::system_clock::time_point m_lastCastTimePoint;
  std::chrono::system_clock::time_point m_lastExpected_CD_FinishTime;
  bool m_octarine;
  PlaySound m_audioPlayer;
  bool m_TalentUsed; // Can only use talent once which decreases cooldown
  bool m_Scepter;
  bool m_Shard;

  // State and Guard Functions
  void st_func_NotLearned(const EventData *); // variable name is not necessary
  void st_func_LearnAndReady(const EventData *);
  void st_func_Casting(const EventData *);
  void st_func_On_Cooldown(const EventData *);
  bool gd_func_checkOnCooldown(const EventData *);  // guard function
  bool gd_func_checkIfLevelFull(const EventData *); // guard function

  // General Functions
  bool onCoolDown();
  void useRefresher();
  void setOctarine(bool val);
  void print_SpellTimes();
  void useTalent(double seconds);
  void setScepter(bool set, double seconds);
  void setShard(bool, double);
  void setCooldown(double);

  const StateAction<Spell, &Spell::st_func_NotLearned> func_NotLearned;
  const StateAction<Spell, &Spell::st_func_LearnAndReady> func_LearnAndReady;
  const StateAction<Spell, &Spell::st_func_Casting> func_Casting;
  const StateAction<Spell, &Spell::st_func_On_Cooldown> func_On_Cooldown;
  const GuardCondition<Spell, &Spell::gd_func_checkOnCooldown> func_checkOnCooldown;
  const GuardCondition<Spell, &Spell::gd_func_checkIfLevelFull> func_checkIfFullLevel;
  StateFunctionMap *GetStateFunctionMap() {
    static StateFunctionMap stFuncMap[] = {
        {&func_NotLearned, nullptr},
        {&func_LearnAndReady, &func_checkIfFullLevel},
        {&func_Casting, &func_checkOnCooldown},
        {&func_On_Cooldown, &func_checkOnCooldown},

    };
    return stFuncMap;
  };

  void learnSpell(const EventData *data);
  void castSpell(const EventData *data);
};

#endif /* Spell_h */
