/*!
 * @file
 * @brief
 */

#include <string.h>
#include <stdbool.h>
#include "life.h"

enum {
  GridSize = 8
};

void life_init(life_t* self) {
  self->current_buffer = self->buffers[1];
}

void life_seed(life_t* self, const uint8_t* buffer) {
  memcpy(self->current_buffer, buffer, GridSize);
}

static bool alive(const uint8_t* previous, int8_t x, int8_t y) {
  if(y < 0) {
    y += GridSize;
  }

  if(x < 0) {
    x += GridSize;
  }

  y %= GridSize;
  x %= GridSize;

  return !!(previous[y] & (1 << x));
}

static void set(uint8_t* current, int8_t x, int8_t y, bool alive) {
  if(alive) {
    current[y] |= (1 << x);
  }
  else {
    current[y] &= ~(1 << x);
  }
}

static uint8_t neighbors(const uint8_t* previous, int8_t x, int8_t y) {
  uint8_t count = 0;

  for(int8_t dx = -1; dx <= 1; dx++) {
    for(int8_t dy = -1; dy <= 1; dy++) {
      if(dx == 0 && dy == 0) {
        continue;
      }

      if(alive(previous, x + dx, y + dy)) {
        count++;
      }
    }
  }

  return count;
}

static void step(const uint8_t* previous, uint8_t* current) {
  for(int8_t x = 0; x < GridSize; x++) {
    for(int8_t y = 0; y < GridSize; y++) {
      if(alive(previous, x, y)) {
        uint8_t _neighbors = neighbors(previous, x, y);
        set(current, x, y, _neighbors == 2 || _neighbors == 3);
      }
      else {
        set(current, x, y, neighbors(previous, x, y) == 3);
      }
    }
  }
}

void life_step(life_t* self) {
  uint8_t* previous = self->current_buffer;
  uint8_t* current;

  if(previous == self->buffers[0]) {
    current = self->buffers[1];
  }
  else {
    current = self->buffers[0];
  }

  step(previous, current);

  self->current_buffer = current;
}

const uint8_t* life_state(life_t* self) {
  return self->current_buffer;
}
