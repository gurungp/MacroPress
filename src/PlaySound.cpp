
#define MINIAUDIO_IMPLEMENTATION
#include "PlaySound.h"
#include "miniaudio.h"
#include <stdexcept>

PlaySound::PlaySound() : result(ma_engine_init(NULL, &engine)) {
  if (result != MA_SUCCESS) {
    throw std::runtime_error("Failed to initialize audio engine");
  }
}

PlaySound::~PlaySound() {
  ma_engine_uninit(&engine);
}

void PlaySound::playSound(const char *path) {

  if (path == nullptr) {

    std::cerr << "path is nullptr" << std::endl;
  }

  if (result != MA_SUCCESS) {
    std::cerr << "Engine is not initialized properly" << std::endl;
  }
  ma_engine_play_sound(&engine, path, NULL);
}
