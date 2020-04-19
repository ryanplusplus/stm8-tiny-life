/*!
 * @file
 * @brief
 */

#ifndef matrix_pins_h
#define matrix_pins_h

#include "hal/i_tiny_digital_output.h"

i_tiny_digital_output_t* matrix_pins_clock(void);
i_tiny_digital_output_t* matrix_pins_data(void);

#endif
