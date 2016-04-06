#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include "lib.h"

const char *libfile = "libmissile.so";
static volatile sig_atomic_t should_reload = false;

typedef struct game {
  void *library;
  game_api api;
  state state;
} game;

SDL_GLContext *init_gl(SDL_Window *window);
SDL_Window *init_sdl();
int reload_api(game *game);
void enable_reload(int _);
int try_reload_api(game *game);

int main() {
  game game = {0};
  signal(SIGUSR1, enable_reload);
  game.state.exit_status = 1;
  SDL_Window *window = init_sdl();
  if (window == NULL)
    goto teardown_sdl;
  SDL_GLContext *context = init_gl(window);
  if (context == NULL)
    goto teardown_gl;

  game.state.window = window;
  game.state.context = context;

  if (reload_api(&game))
    goto teardown_api;

  while (game.state.running) {
    if (try_reload_api(&game))
      break;
    game.api.input(&game.state);
    game.api.update(&game.state);
    game.api.draw(&game.state);
  }

teardown_api:
  game.api.unload(&game.state);
  game.api.finalize(&game.state);
teardown_gl:
  SDL_GL_DeleteContext(context);
teardown_sdl:
  SDL_Quit();

  return game.state.exit_status;
}

SDL_GLContext *init_gl(SDL_Window *window) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GLContext *context = SDL_GL_CreateContext(window);
  if (context == NULL) {
    fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
    return NULL;
  }

  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    fprintf(stderr, "Warning: Error initializing GLEW: %s\n",
            glewGetErrorString(glewError));
  }

  if (SDL_GL_SetSwapInterval(1) < 0) {
    fprintf(stderr, "Warning: Unable to set VSync: %s\n", SDL_GetError());
  }

  glClearColor(0, 0, 0, 1);
  return context;
}

SDL_Window *init_sdl() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Failed to init SDL: %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Window *window =
    SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     512, 512, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
    return NULL;
  }

  return window;
}

int reload_api(game *game) {
  assert(game);

  bool first_load;
  if (game->library) {
    /* Unload the game if it's been loaded once before */
    first_load = false;
    game->api.unload(&game->state);
    dlclose(game->library);
  } else {
    first_load = true;
  }

  /* Load the library */
  game->library = dlopen(libfile, RTLD_LAZY);
  if (!game->library) {
    fprintf(stderr, "%s\n", dlerror());
    return 1;
  }

  /* Bind the API struct */
  game_api *api = dlsym(game->library, "GAME_API");
  if (!api) {
    fprintf(stderr, "%s\n", dlerror());
    return 2;
  }
  memcpy(&game->api, api, sizeof(game->api));

  /* Only initialize the game state on the first load */
  if (first_load) {
    game->api.init(&game->state);
  }
  game->api.reload(&game->state);
  return 0;
}

void enable_reload(int _) {
  (void)_;
  signal(SIGUSR1, enable_reload);
  should_reload = true;
}

int try_reload_api(game *game) {
  if (should_reload) {
    should_reload = false;
    if (reload_api(game)) {
      return 1;
    }
  }
  return 0;
}
