#ifndef TACTILE_RIDE_CONSUMER_REPORT_H_
#define TACTILE_RIDE_CONSUMER_REPORT_H_

#include <stdint.h>

#include <tactile_ride/media_action.h>

#define CONSUMER_REPORT_VOLUME_INCREMENT (UINT8_C(1) << 0)
#define CONSUMER_REPORT_VOLUME_DECREMENT (UINT8_C(1) << 1)
#define CONSUMER_REPORT_PLAY_PAUSE (UINT8_C(1) << 2)
#define CONSUMER_REPORT_NEXT_TRACK (UINT8_C(1) << 3)
#define CONSUMER_REPORT_PREVIOUS_TRACK (UINT8_C(1) << 4)
#define CONSUMER_REPORT_RELEASE 0U

int consumer_report_press(enum media_action action, uint8_t *report);
void consumer_report_release(uint8_t *report);

#endif /* TACTILE_RIDE_CONSUMER_REPORT_H_ */
