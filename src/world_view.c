#include <SDL_image.h>
#include "world_view.h"

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* texture_path) {
  /* Inspired from
   * https://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php
   */
  SDL_Texture* new_texture = NULL;

  // Load image at specified path
  SDL_Surface* image_surface = IMG_Load(texture_path);
  if (image_surface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", texture_path,
           IMG_GetError());
  } else {
    // Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    if (new_texture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", texture_path,
             SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(image_surface);
  }

  return new_texture;
}

bool init_view(SDL_Renderer* renderer, WorldView* view, World* world,
               uint8_t screen_tile_dim) {
  view->world = world;
  view->spritesheet = load_texture(renderer, SPRITESHEET_PATH);
  view->screen_tile_dim = screen_tile_dim;

  if (view->spritesheet == NULL) return false;

  return true;
}

void render_view(SDL_Renderer* renderer, WorldView* view) {
  for (size_t line = 0; line < view->world->height; line += 1)
    for (size_t col = 0; col < view->world->width; col += 1) {
      SDL_Rect current_screen_pos = {
          col * view->screen_tile_dim, line * view->screen_tile_dim,
          view->screen_tile_dim, view->screen_tile_dim};

      if (view->world->map[line][col] & FLAG_WALL) {
        SDL_RenderCopy(renderer, view->spritesheet, &RECT_WALL,
                       &current_screen_pos);
      }

      if (view->world->map[line][col] & FLAG_GOAL) {
        SDL_RenderCopy(renderer, view->spritesheet, &RECT_GOAL,
                       &current_screen_pos);
      }

      if (view->world->map[line][col] & FLAG_CRATE) {
        if (view->world->map[line][col] & FLAG_GOAL)
          SDL_RenderCopy(renderer, view->spritesheet, &RECT_CRATE_ON_GOAL,
                         &current_screen_pos);
        else
          SDL_RenderCopy(renderer, view->spritesheet, &RECT_CRATE,
                         &current_screen_pos);
      }

      if (view->world->map[line][col] & FLAG_PLAYER) {
        SDL_RenderCopy(renderer, view->spritesheet, &RECT_PLAYER,
                       &current_screen_pos);
      }
    }
}

void clean_view(WorldView* view) {
  SDL_DestroyTexture(view->spritesheet);
  view->spritesheet = NULL;
}