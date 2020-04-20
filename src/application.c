/*!
 * @file
 * @brief
 */

#include "application.h"
#include "aip1640_8x8_matrix.h"
#include "matrix_pins.h"

#define b(_0, _1, _2, _3, _4, _5, _6, _7) \
  ((uint8_t)((_7 << 7) | (_6 << 6) | (_5 << 5) | (_4 << 4) | (_3 << 3) | (_2 << 2) | (_1 << 1) | _0))

static aip1640_8x8_matrix_t matrix;
static uint8_t matrix_buffer[] = {
  b(0, 0, 0, 0, 0, 0, 0, 0),
  b(0, 1, 1, 1, 0, 0, 0, 0),
  b(0, 1, 0, 0, 0, 0, 0, 0),
  b(0, 1, 1, 1, 0, 0, 0, 0),
  b(0, 1, 0, 0, 0, 0, 0, 0),
  b(0, 1, 1, 1, 0, 0, 0, 0),
  b(0, 0, 0, 0, 0, 0, 0, 0),
  b(0, 0, 0, 0, 0, 0, 0, 0)
};

static void usec_delay(void) {
}

void application_init(void) {
  aip1640_8x8_matrix_init(&matrix, matrix_pins_clock(), matrix_pins_data(), usec_delay);
  aip1640_8x8_matrix_render(&matrix, matrix_buffer, 1);
}
