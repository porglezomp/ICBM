#ifndef _ICBM_LIB_H
#define _ICBM_LIB_H

#include <stdbool.h>

#include <SDL2/SDL.h>

/* The state struct contains the program state that persists between
 * reloads and between frames.
 */
typedef struct {
  bool running;
  int exit_status;
  SDL_Window *window;
  SDL_GLContext *context;
} state;

/* The game_api struct is the interface that the main program has access to
 * in order to call the reloadable functions.
 */
typedef struct {
  void (*init)(state *s);
  void (*reload)(state *s);
  void (*unload)(state *s);
  void (*input)(state *s);
  void (*update)(state *s);
  void (*draw)(state *s);
  void (*finalize)(state *s);
} game_api;

extern const game_api GAME_API;

#endif
