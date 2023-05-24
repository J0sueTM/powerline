#include "engine/window.h"
#include "editor/ui.h"

int main(void) {
  pl_window window;
  if (!pl_init_window(&window)) {
    return 1;
  }

  while (window.is_running) {
    pl_poll_win_evts(&window);
    pl_draw_window(&window);
  }

  // SDL_GL_DeleteContext(window.gl_ctx);
  SDL_DestroyWindow(window.sdlwin);
  SDL_Quit();

  return 0;
}
