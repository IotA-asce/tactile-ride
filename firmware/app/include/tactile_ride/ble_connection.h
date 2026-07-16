#ifndef TACTILE_RIDE_BLE_CONNECTION_H_
#define TACTILE_RIDE_BLE_CONNECTION_H_

#include <stdbool.h>

int ble_connection_start(void);
bool ble_connection_is_connected(void);
int ble_connection_reset_bonds(void);

#endif /* TACTILE_RIDE_BLE_CONNECTION_H_ */
