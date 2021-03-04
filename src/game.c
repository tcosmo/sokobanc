#include <SDL2/SDL.h>
#include "game.h"

void run_game(World* world) {
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