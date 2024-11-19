#pragma once

#include "miniaudio.h"
#include <iostream>
#include <stdexcept>

class PlaySound {

public:
  PlaySound();

  void playSound(const char *path);
  ~PlaySound();

private:
  ma_engine engine;
  ma_result result;
};
