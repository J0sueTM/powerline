#ifndef __PL_RENDERER_H__
#define __PL_RENDERER_H__

#include "engine.h"

#ifdef __APPLE__
  #define PL_GL_SHDR_VER "#version 150\n"
#else
  #define PL_GL_SHDR_VER "#version 130\n"
#endif

#define PL_DFLT_VTX_SHDR                              \
  PL_GL_SHDR_VER                                      \
  "uniform mat4 proj_mtrx;\n"                         \
  "in vec2 pos;\n"                                    \
  "in vec2 tex_coord;\n"                              \
  "in vec4 color;\n"                                  \
  "out vec2 Frag_UV;\n"                               \
  "out vec4 Frag_Color;\n"                            \
  "void main() {\n"                                   \
  "  Frag_UV = tex_coord;\n"                          \
  "  Frag_Color = color;\n"                           \
  "  gl_Position = proj_mtrx * vec4(pos.xy, 0, 1);\n" \
  "}\n"

#define PL_DFLT_FRAG_SHDR                                  \
  PL_GL_SHDR_VER                                           \
  "precision mediump float;\n"                             \
  "uniform sampler2D tex;\n"                               \
  "in vec2 Frag_UV;\n"                                     \
  "in vec4 Frag_Color;\n"                                  \
  "out vec4 Out_Color;\n"                                  \
  "void main(){\n"                                         \
  "  Out_Color = Frag_Color * texture(tex, Frag_UV.st);\n" \
  "}\n"

typedef struct pl_rndr_device {
    GLuint vbo, vao, ebo;
    GLuint prog;
    GLuint vtx_shdr;
    GLuint frag_shdr;
    GLint attr_pos;
    GLint attr_uv;
    GLint attr_col;
    GLint unif_tex;
    GLint unif_proj;
    GLuint font_tex;
} pl_rndr_device;

void pl_init_rndr();

SDL_GLContext pl_create_gl_ctx(SDL_Window *_sdlwin);

void pl_init_rndr_dev(pl_rndr_device *_dev);

#endif
