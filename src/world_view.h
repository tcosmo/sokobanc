#pragma once

#include <SDL2/SDL.h>
#include "world.h"

static const char* SPRITESHEET_PATH = "assets/images/spritesheet/sprites.png";

static const SDL_Rect RECT_WALL = {0, 320, 64, 64};
static const SDL_Rect RECT_CRATE = {192, 256, 64, 64};
static const SDL_Rect RECT_GOAL = {0, 384, 32, 32};
static const SDL_Rect RECT_PLAYER = {362, 248, 37, 59};

#define SYMB_EMPTY ' '
#define SYMB_WALL '#'
#define SYMB_CRATE '$'
#define SYMB_GOAL '.'
#define SYMB_CRATE_ON_GOAL '*'
#define SYMB_PLAYER '@'
#define SYMB_PLAYER_ON_GOAL '+'

typedef struct {
  const World* world;
  SDL_Texture* spritesheet;
  uint8_t screen_tile_dim;
} WorldView;

bool init_view(SDL_Renderer* renderer, WorldView* view, World* world,
               uint8_t screen_tile_dim);
void render_view(SDL_Renderer* renderer, WorldView* view);
void clean_view(WorldView* view);