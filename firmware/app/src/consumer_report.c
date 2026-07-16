#include <errno.h>
#include <stddef.h>

#include <tactile_ride/consumer_report.h>

int consumer_report_press(enum media_action action, uint8_t *report)
{
	if (report == NULL) {
		return -EINVAL;
	}

	switch (action) {
	case MEDIA_ACTION_VOLUME_INCREMENT:
		*report = CONSUMER_REPORT_VOLUME_INCREMENT;
		return 0;
	case MEDIA_ACTION_VOLUME_DECREMENT:
		*report = CONSUMER_REPORT_VOLUME_DECREMENT;
		return 0;
	case MEDIA_ACTION_PLAY_PAUSE:
		*report = CONSUMER_REPORT_PLAY_PAUSE;
		return 0;
	case MEDIA_ACTION_NEXT_TRACK:
		*report = CONSUMER_REPORT_NEXT_TRACK;
		return 0;
	case MEDIA_ACTION_PREVIOUS_TRACK:
		*report = CONSUMER_REPORT_PREVIOUS_TRACK;
		return 0;
	case MEDIA_ACTION_COUNT:
		return -EINVAL;
	}

	return -EINVAL;
}

void consumer_report_release(uint8_t *report)
{
	if (report != NULL) {
		*report = CONSUMER_REPORT_RELEASE;
	}
}
