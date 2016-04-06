#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "lib.h"

const char *libfile = "libmissile.so";
static volatile sig_atomic_t should_reload = false;

typedef struct game {
  void *library;
  game_api api;
  state state;
} game;

int reload_api(game *game);
void enable_reload(int _);
int try_reload_api(game *game);

int main() {
  game game = {0};
  signal(SIGUSR1, enable_reload);

  if (reload_api(&game)) return 1;

  while (game.state.running) {
    if (try_reload_api(&game)) {
      continue;
    }
    game.api.input(&game.state);
    game.api.update(&game.state);
    game.api.draw(&game.state);
    sleep(1);
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
  (void) _;
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
