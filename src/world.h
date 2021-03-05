#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define WORLD_MAX_DIM 100

static const uint8_t EMPTY = 0;
static const uint8_t FLAG_WALL = 1 << 0;
static const uint8_t FLAG_GOAL = 1 << 1;
static const uint8_t FLAG_CRATE = 1 << 2;
static const uint8_t FLAG_PLAYER = 1 << 3;

static const size_t NORTH = 0;
static const size_t EAST = 1;
static const size_t SOUTH = 2;
static const size_t WEST = 3;

typedef struct {
  uint8_t map[WORLD_MAX_DIM][WORLD_MAX_DIM];
  size_t height;
  size_t width;
} World;

bool has_player_won(const World* world);
bool move_player(World* world, size_t dir);