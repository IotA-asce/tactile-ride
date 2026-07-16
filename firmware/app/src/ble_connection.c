#include <errno.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>

#include <tactile_ride/ble_connection.h>

LOG_MODULE_REGISTER(tactile_ble, LOG_LEVEL_INF);

static struct bt_conn *active_connection;

static const struct bt_data advertising_data[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_HIDS_VAL)),
};

static const struct bt_data scan_response_data[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME,
		sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

static int start_advertising(void)
{
	int err;

	err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1, advertising_data,
			      ARRAY_SIZE(advertising_data), scan_response_data,
			      ARRAY_SIZE(scan_response_data));
	if (err != 0) {
		LOG_ERR("Advertising start failed (%d)", err);
		return err;
	}

	LOG_INF("Advertising BLE HID Consumer Control service");
	return 0;
}

static void connected(struct bt_conn *conn, uint8_t err)
{
	char address[BT_ADDR_LE_STR_LEN];
	int security_err;

	bt_addr_le_to_str(bt_conn_get_dst(conn), address, sizeof(address));
	if (err != 0U) {
		LOG_WRN("Connection to %s failed (0x%02x)", address, err);
		return;
	}

	if (active_connection != NULL) {
		bt_conn_unref(active_connection);
	}
	active_connection = bt_conn_ref(conn);
	LOG_INF("Connected to %s", address);

	security_err = bt_conn_set_security(conn, BT_SECURITY_L2);
	if (security_err != 0 && security_err != -EALREADY) {
		LOG_WRN("Encryption request failed (%d)", security_err);
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	char address[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), address, sizeof(address));
	LOG_INF("Disconnected from %s (0x%02x)", address, reason);

	if (active_connection == conn) {
		bt_conn_unref(active_connection);
		active_connection = NULL;
	}

	(void)start_advertising();
}

static void security_changed(struct bt_conn *conn, bt_security_t level,
			     enum bt_security_err err)
{
	char address[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), address, sizeof(address));
	if (err == BT_SECURITY_ERR_SUCCESS) {
		LOG_INF("Security level %u established with %s", level, address);
	} else {
		LOG_WRN("Security change for %s failed (%d)", address, err);
	}
}

BT_CONN_CB_DEFINE(tactile_connection_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
	.security_changed = security_changed,
};

int ble_connection_start(void)
{
	int err;

	err = bt_enable(NULL);
	if (err != 0) {
		LOG_ERR("Bluetooth init failed (%d)", err);
		return err;
	}

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		err = settings_load();
		if (err != 0) {
			LOG_WRN("Bond settings load failed (%d)", err);
		}
	}

	return start_advertising();
}

bool ble_connection_is_connected(void)
{
	return active_connection != NULL;
}

int ble_connection_reset_bonds(void)
{
	LOG_WRN("Bond reset has no safe runtime trigger in Phase 1");
	return -ENOTSUP;
}
