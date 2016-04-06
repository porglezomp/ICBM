#include "lib.h"

/* Pass init() a block of memory corresponding to a state object. init()
 * is called when the program first starts, before reload() is called.
 * It will not be called when the program is reloaded.
 */
static void init(state *s) {
  s->running = 1;
}

/* reload() is called immediately after the library is loaded, including
 * the first time.
 */
static void reload(state *s) {
  (void) s;
}

/* unload() is called immediately before the library is unloaded during
 * code hot-swapping, or before the program fully shuts down.
 */
static void unload(state *s) {
  (void) s;
}

/* input() is called at the beginning of each frame to gather input
 * events.
 */
static void input(state *s) {
  (void) s;
}

/* update() is called once per frame in order to step physics forward.
 */
static void update(state *s) {
  (void) s;
}

/* draw() is called at the end of each frame in order to render objects.
 */
static void draw(state *s) {
  s->running = 0;
}

/* finalize() is called when the program is finally shutting down, after
 * unload() is called.
 */
static void finalize(state *s) {
  s->exit_status = 0;
}

const game_api GAME_API = {
  .init = init,
  .reload = reload,
  .unload = unload,
  .input = input,
  .update = update,
  .draw = draw,
  .finalize = finalize,
};
