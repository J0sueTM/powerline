#ifndef __PL_WINDOW_H__
#define __PL_WINDOW_H__

#include "engine.h"
#include "renderer.h"
#include "../editor/ui.h"

typedef struct pl_window {
  SDL_Window *sdlwin;
  SDL_WindowFlags sdlwin_flags;
  SDL_GLContext gl_ctx;

  pl_ui ui_hdlr;

  bool is_running;
} pl_window;

bool pl_init_window(pl_window *_win);

void pl_poll_win_evts(pl_window *_win);

void pl_draw_window(pl_window *_win);

#endif
