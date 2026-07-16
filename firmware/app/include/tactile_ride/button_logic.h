#ifndef TACTILE_RIDE_BUTTON_LOGIC_H_
#define TACTILE_RIDE_BUTTON_LOGIC_H_

#include <stdbool.h>
#include <stdint.h>

#include <tactile_ride/media_action.h>

enum button_event_type {
	BUTTON_EVENT_NONE = 0,
	BUTTON_EVENT_PRESSED,
	BUTTON_EVENT_RELEASED,
	BUTTON_EVENT_REPEAT,
};

struct button_logic {
	enum media_action action;
	bool stable_pressed;
	bool candidate_pressed;
	uint32_t candidate_since_ms;
	uint32_t next_repeat_ms;
	uint32_t debounce_ms;
	uint32_t repeat_delay_ms;
	uint32_t repeat_interval_ms;
};

void button_logic_init(struct button_logic *logic, enum media_action action,
		       uint32_t debounce_ms, uint32_t repeat_delay_ms,
		       uint32_t repeat_interval_ms);

enum button_event_type button_logic_update(struct button_logic *logic,
					   bool raw_pressed, uint32_t now_ms);

#endif /* TACTILE_RIDE_BUTTON_LOGIC_H_ */
