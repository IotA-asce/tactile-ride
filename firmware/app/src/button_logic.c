#include <stddef.h>

#include <tactile_ride/button_logic.h>

static bool debounce_elapsed(uint32_t now_ms, uint32_t then_ms, uint32_t interval_ms)
{
	return (uint32_t)(now_ms - then_ms) >= interval_ms;
}

static bool deadline_reached(uint32_t now_ms, uint32_t deadline_ms)
{
	return (int32_t)(now_ms - deadline_ms) >= 0;
}

void button_logic_init(struct button_logic *logic, enum media_action action,
		       uint32_t debounce_ms, uint32_t repeat_delay_ms,
		       uint32_t repeat_interval_ms)
{
	if (logic == NULL) {
		return;
	}

	*logic = (struct button_logic){
		.action = action,
		.debounce_ms = debounce_ms,
		.repeat_delay_ms = repeat_delay_ms,
		.repeat_interval_ms = repeat_interval_ms,
	};
}

enum button_event_type button_logic_update(struct button_logic *logic,
					   bool raw_pressed, uint32_t now_ms)
{
	if (logic == NULL) {
		return BUTTON_EVENT_NONE;
	}

	if (raw_pressed != logic->candidate_pressed) {
		logic->candidate_pressed = raw_pressed;
		logic->candidate_since_ms = now_ms;
	}

	if (logic->stable_pressed != logic->candidate_pressed &&
	    debounce_elapsed(now_ms, logic->candidate_since_ms, logic->debounce_ms)) {
		logic->stable_pressed = logic->candidate_pressed;

		if (logic->stable_pressed) {
			if (media_action_is_volume(logic->action)) {
				logic->next_repeat_ms = now_ms + logic->repeat_delay_ms;
			}
			return BUTTON_EVENT_PRESSED;
		}

		return BUTTON_EVENT_RELEASED;
	}

	if (logic->stable_pressed && media_action_is_volume(logic->action) &&
	    deadline_reached(now_ms, logic->next_repeat_ms)) {
		logic->next_repeat_ms = now_ms + logic->repeat_interval_ms;
		return BUTTON_EVENT_REPEAT;
	}

	return BUTTON_EVENT_NONE;
}
