#include "window.h"

bool pl_init_window(pl_window *_win) {
  if (!_win) {
    return false;
  }

  // hints
  SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return false;
  }

  pl_init_rndr();

  // create sdl window
  _win->sdlwin_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                       SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
  _win->sdlwin = SDL_CreateWindow("Powerline", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, 1280, 720,
                                  _win->sdlwin_flags);
  if (!_win->sdlwin) {
    pl_kill_sdl("failed to create sdl window");

    return false;
  }
  _win->is_running = true;

  _win->gl_ctx = pl_create_gl_ctx(_win->sdlwin);

  bool status = pl_init_ui(&_win->ui_hdlr, _win->sdlwin);

  return status;
}

void pl_poll_win_evts(pl_window *_win) {
  // nk_input_begin(_win->nk_ctx);
  SDL_Event evt;
  while (SDL_PollEvent(&evt)) {
    if (evt.type == SDL_QUIT) {
      _win->is_running = false;
    }

    if (evt.type == SDL_WINDOWEVENT &&
        evt.window.event == SDL_WINDOWEVENT_CLOSE &&
        evt.window.windowID == SDL_GetWindowID(_win->sdlwin)) {
      _win->is_running = false;
    }

    // nk_sdl_handle_event(&evt);
  }
  // nk_input_end(_win->nk_ctx);
}

void pl_draw_window(pl_window *_win) {
  int winw, winh;
  SDL_GetWindowSize(_win->sdlwin, &winw, &winh);
  glViewport(0, 0, winw, winh);
  glClearColor(0.133f, 0.137f, 0.137f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(_win->sdlwin);
}
