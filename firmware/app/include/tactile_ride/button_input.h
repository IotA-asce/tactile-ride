#ifndef TACTILE_RIDE_BUTTON_INPUT_H_
#define TACTILE_RIDE_BUTTON_INPUT_H_

#include <stdbool.h>
#include <stdint.h>

#include <tactile_ride/media_action.h>

typedef void (*button_input_callback_t)(enum media_action action, bool raw_pressed,
					uint32_t now_ms);

int button_input_start(button_input_callback_t callback);

#endif /* TACTILE_RIDE_BUTTON_INPUT_H_ */
