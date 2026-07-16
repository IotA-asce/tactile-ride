#include <errno.h>

#include <zephyr/ztest.h>

#include <tactile_ride/button_logic.h>
#include <tactile_ride/consumer_report.h>
#include <tactile_ride/media_controller.h>

struct fake_transport {
	bool ready;
	uint8_t reports[3];
	uint8_t report_count;
};

static bool fake_is_ready(void *context)
{
	return ((struct fake_transport *)context)->ready;
}

static int fake_send_input_report(void *context, uint8_t report)
{
	struct fake_transport *transport = context;

	if (transport->report_count >= ARRAY_SIZE(transport->reports)) {
		return -ENOMEM;
	}

	transport->reports[transport->report_count++] = report;
	return 0;
}

static struct media_controller make_controller(struct fake_transport *transport)
{
	struct media_controller controller;
	const struct media_transport interface = {
		.is_ready = fake_is_ready,
		.send_input_report = fake_send_input_report,
		.context = transport,
	};

	zassert_ok(media_controller_init(&controller, &interface));
	return controller;
}

ZTEST(tactile_ride_logic, test_consumer_action_bit_mapping)
{
	uint8_t report;

	zassert_ok(consumer_report_press(MEDIA_ACTION_VOLUME_INCREMENT, &report));
	zassert_equal(report, CONSUMER_REPORT_VOLUME_INCREMENT);
	zassert_ok(consumer_report_press(MEDIA_ACTION_VOLUME_DECREMENT, &report));
	zassert_equal(report, CONSUMER_REPORT_VOLUME_DECREMENT);
	zassert_ok(consumer_report_press(MEDIA_ACTION_PLAY_PAUSE, &report));
	zassert_equal(report, CONSUMER_REPORT_PLAY_PAUSE);
	zassert_ok(consumer_report_press(MEDIA_ACTION_NEXT_TRACK, &report));
	zassert_equal(report, CONSUMER_REPORT_NEXT_TRACK);
	zassert_ok(consumer_report_press(MEDIA_ACTION_PREVIOUS_TRACK, &report));
	zassert_equal(report, CONSUMER_REPORT_PREVIOUS_TRACK);
}

ZTEST(tactile_ride_logic, test_command_sends_press_then_release)
{
	struct fake_transport transport = {.ready = true};
	struct media_controller controller = make_controller(&transport);

	zassert_ok(media_controller_trigger(&controller, MEDIA_ACTION_NEXT_TRACK));
	zassert_equal(transport.report_count, 2U);
	zassert_equal(transport.reports[0], CONSUMER_REPORT_NEXT_TRACK);
	zassert_equal(transport.reports[1], CONSUMER_REPORT_RELEASE);
}

ZTEST(tactile_ride_logic, test_disconnected_command_is_dropped)
{
	struct fake_transport transport = {.ready = false};
	struct media_controller controller = make_controller(&transport);

	zassert_equal(media_controller_trigger(&controller, MEDIA_ACTION_PLAY_PAUSE),
		      -ENOTCONN);
	zassert_equal(transport.report_count, 0U);
}

ZTEST(tactile_ride_logic, test_debounce_requires_stable_press_and_release)
{
	struct button_logic logic;

	button_logic_init(&logic, MEDIA_ACTION_PLAY_PAUSE, 30U, 400U, 250U);
	zassert_equal(button_logic_update(&logic, true, 0U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, true, 29U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, true, 30U), BUTTON_EVENT_PRESSED);
	zassert_equal(button_logic_update(&logic, false, 40U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, false, 70U), BUTTON_EVENT_RELEASED);
}

ZTEST(tactile_ride_logic, test_short_bounce_is_not_a_press)
{
	struct button_logic logic;

	button_logic_init(&logic, MEDIA_ACTION_NEXT_TRACK, 30U, 400U, 250U);
	zassert_equal(button_logic_update(&logic, true, 0U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, false, 10U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, false, 100U), BUTTON_EVENT_NONE);
}

ZTEST(tactile_ride_logic, test_held_volume_repeats_at_the_configured_rate)
{
	struct button_logic logic;

	button_logic_init(&logic, MEDIA_ACTION_VOLUME_INCREMENT, 30U, 400U, 250U);
	zassert_equal(button_logic_update(&logic, true, 0U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, true, 30U), BUTTON_EVENT_PRESSED);
	zassert_equal(button_logic_update(&logic, true, 429U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, true, 430U), BUTTON_EVENT_REPEAT);
	zassert_equal(button_logic_update(&logic, true, 679U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, true, 680U), BUTTON_EVENT_REPEAT);
}

ZTEST(tactile_ride_logic, test_held_non_volume_action_does_not_repeat)
{
	struct button_logic logic;

	button_logic_init(&logic, MEDIA_ACTION_PREVIOUS_TRACK, 30U, 400U, 250U);
	zassert_equal(button_logic_update(&logic, true, 0U), BUTTON_EVENT_NONE);
	zassert_equal(button_logic_update(&logic, true, 30U), BUTTON_EVENT_PRESSED);
	zassert_equal(button_logic_update(&logic, true, 1000U), BUTTON_EVENT_NONE);
}

ZTEST_SUITE(tactile_ride_logic, NULL, NULL, NULL, NULL, NULL);
