#include <errno.h>

#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include <tactile_ride/ble_connection.h>
#include <tactile_ride/button_input.h>
#include <tactile_ride/button_logic.h>
#include <tactile_ride/hid_service.h>
#include <tactile_ride/media_controller.h>
#include <tactile_ride/power_policy.h>

LOG_MODULE_REGISTER(tactile_app, LOG_LEVEL_INF);

static struct button_logic button_logic[MEDIA_ACTION_COUNT];
static struct media_controller media_controller;

static bool transport_is_ready(void *context)
{
	ARG_UNUSED(context);
	return ble_connection_is_connected() && hid_service_notifications_enabled();
}

static int transport_send_input_report(void *context, uint8_t report)
{
	ARG_UNUSED(context);
	return hid_service_send_input_report(report);
}

static void handle_button_sample(enum media_action action, bool raw_pressed,
				 uint32_t now_ms)
{
	enum button_event_type event;
	int err;

	if (action >= MEDIA_ACTION_COUNT) {
		LOG_WRN("Ignoring unknown input action %d", action);
		return;
	}

	event = button_logic_update(&button_logic[action], raw_pressed, now_ms);
	if (event != BUTTON_EVENT_PRESSED && event != BUTTON_EVENT_REPEAT) {
		return;
	}

	err = media_controller_trigger(&media_controller, action);
	if (err == -ENOTCONN) {
		LOG_INF("Dropped action %d: no connected subscribed HID host", action);
	} else if (err != 0) {
		LOG_WRN("Action %d failed (%d)", action, err);
	} else {
		LOG_INF("Sent action %d%s", action,
			event == BUTTON_EVENT_REPEAT ? " (repeat)" : "");
	}
}

int main(void)
{
	const struct media_transport transport = {
		.is_ready = transport_is_ready,
		.send_input_report = transport_send_input_report,
		.context = NULL,
	};
	int err;

	for (enum media_action action = MEDIA_ACTION_VOLUME_INCREMENT;
	     action < MEDIA_ACTION_COUNT; action++) {
		button_logic_init(&button_logic[action], action,
				  CONFIG_TACTILE_RIDE_DEBOUNCE_MS,
				  CONFIG_TACTILE_RIDE_VOLUME_REPEAT_DELAY_MS,
				  CONFIG_TACTILE_RIDE_VOLUME_REPEAT_INTERVAL_MS);
	}

	err = media_controller_init(&media_controller, &transport);
	if (err != 0) {
		LOG_ERR("Media controller init failed (%d)", err);
		return 0;
	}

	hid_service_init();
	power_policy_init();

	err = ble_connection_start();
	if (err != 0) {
		LOG_ERR("BLE connection setup failed (%d)", err);
		return 0;
	}

	err = button_input_start(handle_button_sample);
	if (err != 0) {
		LOG_ERR("Button input init failed (%d)", err);
	}

	return 0;
}
