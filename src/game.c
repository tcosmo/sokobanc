#include <SDL2/SDL.h>
#include "game.h"
#include "world_parser.h"
#include "world_view.h"

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
                       SDL_WINDOWPOS_UNDEFINED, 960, 740, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    printf("Could not create renderer: %s\n", SDL_GetError());
    return 1;
  }

  WorldView view;

  if (!init_view(renderer, &view, world, 37)) {
    printf("Could not create view. Abort.\n");
    return 1;
  }

  bool is_game_running = true;
  while (is_game_running) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) is_game_running = false;
    }

    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);

    render_view(renderer, &view);

    SDL_RenderPresent(renderer);
  }

  clean_view(&view);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}