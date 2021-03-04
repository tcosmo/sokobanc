#include "game.h"
#include "world.h"
#include "world_parser.h"

static const char* LEVEL_FILE = "assets/levels/level_set_1.txt";

int main() {
  if (!init_parser(LEVEL_FILE)) {
    printf("Invalid level file `%s`. Abort.\n", LEVEL_FILE);
    return 1;
  }

  World world;

  // Loading first level
  load_level(&world, 0);

  run_game(&world);

  return 0;
}