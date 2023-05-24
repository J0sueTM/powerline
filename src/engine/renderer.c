#include "renderer.h"

void pl_init_rndr() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

SDL_GLContext pl_create_gl_ctx(SDL_Window *_sdlwin) {
  SDL_GLContext gl_ctx = SDL_GL_CreateContext(_sdlwin);
  if (!gl_ctx) {
    pl_kill_sdl("failed to create opengl context");

    return NULL;
  }

  SDL_GL_MakeCurrent(_sdlwin, gl_ctx);
  SDL_GL_SetSwapInterval(1); // enable vsync

  gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  return gl_ctx;
}

void pl_init_rndr_dev(pl_rndr_device *_dev) {
  _dev->prog = glCreateProgram();
  _dev->vtx_shdr = glCreateShader(GL_VERTEX_SHADER);
  _dev->frag_shdr = glCreateShader(GL_FRAGMENT_SHADER);
  int status;

  glShaderSource(_dev->vtx_shdr, 1, (const char *const *)PL_DFLT_VTX_SHDR, 0);
  glShaderSource(_dev->frag_shdr, 1, (const char *const *)PL_DFLT_FRAG_SHDR, 0);

  glCompileShader(_dev->vtx_shdr);
  glCompileShader(_dev->frag_shdr);
  glGetShaderiv(_dev->vtx_shdr, GL_COMPILE_STATUS, &status);
  assert(status);

  glGetShaderiv(_dev->frag_shdr, GL_COMPILE_STATUS, &status);
  assert(status);

  glAttachShader(_dev->prog, _dev->vtx_shdr);
  glAttachShader(_dev->prog, _dev->frag_shdr);
  glGetProgramiv(_dev->prog, GL_LINK_STATUS, &status);
  assert(status);

  _dev->unif_tex = glGetUniformLocation(_dev->prog, "tex");
  _dev->unif_proj = glGetUniformLocation(_dev->prog, "proj_mtrx");
  _dev->attr_pos = glGetAttribLocation(_dev->prog, "pos");
  _dev->attr_uv = glGetAttribLocation(_dev->prog, "tex_coord");
  _dev->attr_col = glGetAttribLocation(_dev->prog, "color");
  
  // TODO(J0sueTM): finish buffer setup
}
