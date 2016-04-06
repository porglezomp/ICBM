#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>

#include "lib.h"

const char *libfile = "libmissile.so";

typedef struct game {
  void *library;
  game_api api;
  state state;
} game;

int reload_api(game *game);

int main() {
  game game = {0};

  if (reload_api(&game)) return 1;

  while (game.state.running) {
    game.api.input(&game.state);
    game.api.update(&game.state);
    game.api.draw(&game.state);
  }

  game.api.unload(&game.state);
  game.api.finalize(&game.state);
  return game.state.exit_status;
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
  if (!game->library) return 1;

  /* Bind the API struct */
  game_api *api = dlsym(game->library, "GAME_API");
  if (!api) return 2;
  memcpy(&game->api, api, sizeof(game->api));

  /* Only initialize the game state on the first load */
  if (first_load) {
    game->api.init(&game->state);
  }

  game->api.reload(&game->state);
  return 0;
}
