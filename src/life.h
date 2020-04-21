/*!
 * @file
 * @brief
 */

#ifndef life_h
#define life_h

#include <stdint.h>

typedef struct {
  uint8_t buffers[2][8];
  uint8_t* current_buffer;
} life_t;

void life_init(life_t* self);
void life_seed(life_t* self, const uint8_t buffer[8]);
void life_step(life_t* self);
const uint8_t* life_state(life_t* self);

#endif
