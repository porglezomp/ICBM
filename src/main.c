#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>

#include "lib.h"

const char *libfile = "libmissile.so";

typedef struct game {
  void *library;
  game_api api;
  state state;
} game;

int main() {
  game game;

  game.library = dlopen(libfile, RTLD_LAZY);
  if (!game.library) return 1;
  game_api *api = dlsym(game.library, "GAME_API");
  memcpy(&game.api, api, sizeof(game.api));

  game.api.init(&game.state);
  game.api.reload(&game.state);
  while (game.state.running) {
    game.api.input(&game.state);
    game.api.update(&game.state);
    game.api.draw(&game.state);
  }
  game.api.unload(&game.state);
  game.api.finalize(&game.state);

  return game.state.exit_status;
}
