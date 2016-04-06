#include <stdlib.h>

#include "lib.h"

int main() {
  state s;

  GAME_API.init(&s);
  GAME_API.reload(&s);
  while (s.running) {
    GAME_API.input(&s);
    GAME_API.update(&s);
    GAME_API.draw(&s);
  }
  GAME_API.unload(&s);
  GAME_API.finalize(&s);

  return s.exit_status;
}
