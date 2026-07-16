#ifndef TACTILE_RIDE_MEDIA_CONTROLLER_H_
#define TACTILE_RIDE_MEDIA_CONTROLLER_H_

#include <stdbool.h>
#include <stdint.h>

#include <tactile_ride/media_action.h>

struct media_transport {
	bool (*is_ready)(void *context);
	int (*send_input_report)(void *context, uint8_t report);
	void *context;
};

struct media_controller {
	struct media_transport transport;
};

int media_controller_init(struct media_controller *controller,
			  const struct media_transport *transport);
int media_controller_trigger(struct media_controller *controller,
			     enum media_action action);

#endif /* TACTILE_RIDE_MEDIA_CONTROLLER_H_ */
