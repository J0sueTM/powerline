#include "engine.h"

void pl_kill_sdl(const char *msg) {
  log_error("%s: %s\n", msg, SDL_GetError());

  SDL_Quit();
}
