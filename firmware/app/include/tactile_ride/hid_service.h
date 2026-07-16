#ifndef TACTILE_RIDE_HID_SERVICE_H_
#define TACTILE_RIDE_HID_SERVICE_H_

#include <stdbool.h>
#include <stdint.h>

void hid_service_init(void);
bool hid_service_notifications_enabled(void);
int hid_service_send_input_report(uint8_t report);

#endif /* TACTILE_RIDE_HID_SERVICE_H_ */
