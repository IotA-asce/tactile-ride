#include <errno.h>
#include <stddef.h>

#include <tactile_ride/consumer_report.h>
#include <tactile_ride/media_controller.h>

int media_controller_init(struct media_controller *controller,
			  const struct media_transport *transport)
{
	if (controller == NULL || transport == NULL || transport->is_ready == NULL ||
	    transport->send_input_report == NULL) {
		return -EINVAL;
	}

	controller->transport = *transport;
	return 0;
}

int media_controller_trigger(struct media_controller *controller,
			     enum media_action action)
{
	uint8_t report;
	int err;

	if (controller == NULL) {
		return -EINVAL;
	}

	if (!controller->transport.is_ready(controller->transport.context)) {
		return -ENOTCONN;
	}

	err = consumer_report_press(action, &report);
	if (err != 0) {
		return err;
	}

	err = controller->transport.send_input_report(controller->transport.context, report);
	if (err != 0) {
		return err;
	}

	consumer_report_release(&report);
	return controller->transport.send_input_report(controller->transport.context, report);
}
