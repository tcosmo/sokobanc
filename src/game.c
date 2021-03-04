#include <SDL2/SDL.h>
#include "game.h"
#include "world_parser.h"

bool load_current_level(WorldParser* parser, World* world) {
  printf("Loading level %zu...\n", parser->current_level);

  while (parser->current_level < parser->number_of_levels &&
         !load_level(parser, world)) {
    printf("Level %zu is not valid, skipping.\n", parser->current_level);
    parser->current_level += 1;
    printf("Loading level %zu...\n", parser->current_level);
  }

  return parser->current_level < parser->number_of_levels;
}

int run_game(World* world) {
  WorldParser parser;

  if (!init_parser(&parser, LEVEL_FILE)) {
    printf("Invalid level file `%s`. Abort.\n", LEVEL_FILE);
    return 1;
  } else {
    printf("Level file `%s` contains %zu level(s).\n", LEVEL_FILE,
           parser.number_of_levels);
  }

  if (!load_current_level(&parser, world)) {
    printf("No level could be loaded. Abort.\n");
    return 1;
  } else {
    printf("Level %zu loaded! Level name: `%s`.\n", parser.current_level,
           parser.current_level_name);
    print_world(world);
  }

  SDL_Window* window;

  SDL_Init(SDL_INIT_VIDEO);

  window =
      SDL_CreateWindow("Sokoban!!", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Delay(3000);

  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}