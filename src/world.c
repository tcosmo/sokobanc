#include <stdio.h>
#include "world.h"

static const size_t cardinal_vectors[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool has_player_won(const World* world) {
  for (size_t line = 0; line < world->height; line += 1) {
    for (size_t col = 0; col < world->width; col += 1) {
      if (world->map[line][col] & FLAG_CRATE) {
        if (!(world->map[line][col] & FLAG_GOAL)) {
          return false;
        }
      }
    }
  }
  return true;
}

bool is_position_valid(const World* world, size_t line, size_t col) {
  return line >= 0 && line < world->height && col >= 0 && col < world->width;
}

bool is_position_valid_and_empty(const World* world, size_t line, size_t col) {
  return is_position_valid(world, line, col) &&
         (world->map[line][col] == EMPTY || world->map[line][col] == FLAG_GOAL);
}

void move_object(World* world, uint8_t flag_object, size_t old_line,
                 size_t old_col, size_t new_line, size_t new_col) {
  assert(is_position_valid(world, old_line, old_col));
  assert(is_position_valid(world, new_line, new_col));

  world->map[old_line][old_col] &= ~flag_object;
  world->map[new_line][new_col] |= flag_object;
}

void move_player(World* world, size_t dir) {
  for (size_t line = 0; line < world->height; line += 1) {
    for (size_t col = 0; col < world->width; col += 1) {
      if (world->map[line][col] & FLAG_PLAYER) {
        // We've found the player
        size_t new_line = line + cardinal_vectors[dir][0];
        size_t new_col = col + cardinal_vectors[dir][1];

        // There is nothing on the position we aim
        if (is_position_valid_and_empty(world, new_line, new_col)) {
          move_object(world, FLAG_PLAYER, line, col, new_line, new_col);
          return;
        }

        // There is a crate on the position we aim
        if ((world->map[new_line][new_col] & FLAG_CRATE)) {
          size_t new_line_crate = new_line + cardinal_vectors[dir][0];
          size_t new_col_crate = new_col + cardinal_vectors[dir][1];

          // There is nothing where we want to push the crate
          if (is_position_valid_and_empty(world, new_line_crate,
                                          new_col_crate)) {
            // We move the crate
            move_object(world, FLAG_CRATE, new_line, new_col, new_line_crate,
                        new_col_crate);
            // We move the player
            move_object(world, FLAG_PLAYER, line, col, new_line, new_col);
            return;
          }
        }
      }
    }
  }
}