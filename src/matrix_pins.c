/*!
 * @file
 * @brief
 */

#include "matrix_pins.h"
#include "stm8s_gpio.h"

enum {
  pin_3 = (1 << 3),
  pin_4 = (1 << 4),
  data_pin = pin_3,
  clock_pin = pin_4
};

static void write_clock(i_tiny_digital_output_t* self, bool value) {
  (void)self;

  if(value) {
    GPIOC->ODR |= clock_pin;
  }
  else {
    GPIOC->ODR &= ~clock_pin;
  }
}

static const i_tiny_digital_output_api_t clock_api = { write_clock };

static void write_data(i_tiny_digital_output_t* self, bool value) {
  (void)self;

  if(value) {
    GPIOC->ODR |= data_pin;
  }
  else {
    GPIOC->ODR &= ~data_pin;
  }
}

static const i_tiny_digital_output_api_t data_api = { write_data };

i_tiny_digital_output_t* matrix_pins_clock(void) {
  GPIOC->CR1 |= clock_pin;
  GPIOC->DDR |= clock_pin;

  static i_tiny_digital_output_t clock;
  clock.api = &clock_api;

  return &clock;
}

i_tiny_digital_output_t* matrix_pins_data(void) {
  GPIOC->CR1 |= data_pin;
  GPIOC->DDR |= data_pin;

  static i_tiny_digital_output_t data;
  data.api = &data_api;

  return &data;
}
