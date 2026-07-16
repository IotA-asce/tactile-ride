#include <errno.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include <tactile_ride/button_input.h>

LOG_MODULE_REGISTER(tactile_input, LOG_LEVEL_INF);

#define DEV_POLL_INTERVAL_MS 10U
#define DEV_NON_VOLUME_HOLD_MS 100U
#define DEV_VOLUME_HOLD_MS 950U

static button_input_callback_t input_callback;

#if defined(CONFIG_TACTILE_RIDE_DEV_AUTO_DEMO) && CONFIG_TACTILE_RIDE_DEV_AUTO_DEMO
static struct k_work_delayable demo_work;
static enum media_action demo_action;
static bool demo_pressed;
static uint32_t demo_phase_started_ms;

static bool elapsed(uint32_t now_ms, uint32_t then_ms, uint32_t interval_ms)
{
	return (uint32_t)(now_ms - then_ms) >= interval_ms;
}

static void demo_work_handler(struct k_work *work)
{
	uint32_t now_ms = k_uptime_get_32();
	uint32_t hold_ms;

	ARG_UNUSED(work);
	hold_ms = media_action_is_volume(demo_action) ? DEV_VOLUME_HOLD_MS :
		  DEV_NON_VOLUME_HOLD_MS;

	if (demo_pressed && elapsed(now_ms, demo_phase_started_ms, hold_ms)) {
		demo_pressed = false;
		demo_phase_started_ms = now_ms;
	} else if (!demo_pressed && elapsed(now_ms, demo_phase_started_ms,
				       CONFIG_TACTILE_RIDE_DEV_AUTO_DEMO_INTERVAL_MS)) {
		demo_action = (enum media_action)((demo_action + 1) % MEDIA_ACTION_COUNT);
		demo_pressed = true;
		demo_phase_started_ms = now_ms;
	}

	input_callback(demo_action, demo_pressed, now_ms);
	k_work_schedule(&demo_work, K_MSEC(DEV_POLL_INTERVAL_MS));
}
#endif

int button_input_start(button_input_callback_t callback)
{
	if (callback == NULL) {
		return -EINVAL;
	}

	input_callback = callback;

#if defined(CONFIG_TACTILE_RIDE_DEV_AUTO_DEMO) && CONFIG_TACTILE_RIDE_DEV_AUTO_DEMO
	demo_action = MEDIA_ACTION_VOLUME_INCREMENT;
	demo_pressed = true;
	demo_phase_started_ms = k_uptime_get_32();
	k_work_init_delayable(&demo_work, demo_work_handler);
	k_work_schedule(&demo_work, K_NO_WAIT);
	LOG_WRN("Development-only synthetic input demo enabled");
#else
	LOG_INF("No physical GPIO input is configured for Phase 1");
#endif

	return 0;
}
