#ifndef __PL_UI_H__
#define __PL_UI_H__

#include "../engine/engine.h"
#include "../engine/renderer.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"

typedef struct pl_ui {
  struct nk_context nk_ctx;
  struct nk_buffer nk_cmds;
  struct nk_draw_null_texture nk_tex_null;

  pl_rndr_device rndr_dev;
} pl_ui;

bool pl_init_ui(pl_ui *_hdlr, SDL_Window *_sdlwin);

#endif