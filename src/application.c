/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include "application.h"
#include "aip1640_8x8_matrix.h"
#include "life.h"
#include "matrix_pins.h"

enum {
  step_time = 100
};

#define b(_0, _1, _2, _3, _4, _5, _6, _7) \
  ((uint8_t)((_7 << 7) | (_6 << 6) | (_5 << 5) | (_4 << 4) | (_3 << 3) | (_2 << 2) | (_1 << 1) | _0))

static aip1640_8x8_matrix_t matrix;
static tiny_timer_t step_timer;
static life_t life;

static const uint8_t initial[] = {
  b(0, 0, 0, 0, 0, 0, 0, 0),
  b(0, 0, 0, 0, 0, 0, 0, 0),
  b(0, 0, 0, 0, 0, 0, 0, 0),
  b(0, 0, 1, 0, 0, 0, 0, 0),
  b(0, 0, 0, 1, 0, 0, 0, 0),
  b(0, 1, 1, 1, 0, 0, 0, 0),
  b(0, 0, 0, 0, 0, 0, 0, 0),
  b(0, 0, 0, 0, 0, 0, 0, 0)
};

static void render(void) {
  aip1640_8x8_matrix_render(&matrix, life_state(&life), 1);
}

static void arm_step_timer(tiny_timer_group_t* group);

static void step(tiny_timer_group_t* group, void* context) {
  (void)context;

  life_step(&life);
  render();

  arm_step_timer(group);
}

static void arm_step_timer(tiny_timer_group_t* group) {
  tiny_timer_start(group, &step_timer, step_time, step, NULL);
}

static void usec_delay(void) {
}

void application_init(tiny_timer_group_t* timer_group) {
  aip1640_8x8_matrix_init(&matrix, matrix_pins_clock(), matrix_pins_data(), usec_delay);
  life_init(&life);
  life_seed(&life, initial);
  render();

  arm_step_timer(timer_group);
}
