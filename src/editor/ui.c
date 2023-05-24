#define NK_IMPLEMENTATION
#include "ui.h"

bool pl_init_ui(pl_ui *_hdlr, SDL_Window *_sdlwin) {
  nk_init_default(&_hdlr->nk_ctx, 0);
  return true;
}