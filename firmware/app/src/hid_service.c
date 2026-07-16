#include <errno.h>
#include <string.h>

#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/logging/log.h>

#include <tactile_ride/hid_service.h>

LOG_MODULE_REGISTER(tactile_hids, LOG_LEVEL_INF);

enum {
	HIDS_REMOTE_WAKE = BIT(0),
	HIDS_NORMALLY_CONNECTABLE = BIT(1),
	HIDS_INPUT = 0x01,
	HIDS_INPUT_REPORT_ATTRIBUTE_INDEX = 5,
};

struct hids_info {
	uint16_t version;
	uint8_t country_code;
	uint8_t flags;
} __packed;

struct hids_report_reference {
	uint8_t id;
	uint8_t type;
} __packed;

static const struct hids_info hids_info = {
	.version = 0x0111,
	.country_code = 0x00,
	.flags = HIDS_NORMALLY_CONNECTABLE,
};

static const struct hids_report_reference input_report_reference = {
	.id = 0x01,
	.type = HIDS_INPUT,
};

/*
 * Report ID 1 contains one Consumer Page input byte:
 * bit 0 Volume Increment (0xE9), bit 1 Volume Decrement (0xEA),
 * bit 2 Play/Pause (0xCD), bit 3 Scan Next Track (0xB5), and
 * bit 4 Scan Previous Track (0xB6). Bits 5-7 are constant padding.
 */
static const uint8_t consumer_report_map[] = {
	0x05, 0x0c, /* Usage Page (Consumer) */
	0x09, 0x01, /* Usage (Consumer Control) */
	0xa1, 0x01, /* Collection (Application) */
	0x85, 0x01, /*   Report ID (1) */
	0x15, 0x00, /*   Logical Minimum (0) */
	0x25, 0x01, /*   Logical Maximum (1) */
	0x75, 0x01, /*   Report Size (1) */
	0x95, 0x05, /*   Report Count (5) */
	0x09, 0xe9, /*   Usage (Volume Increment) */
	0x09, 0xea, /*   Usage (Volume Decrement) */
	0x09, 0xcd, /*   Usage (Play/Pause) */
	0x09, 0xb5, /*   Usage (Scan Next Track) */
	0x09, 0xb6, /*   Usage (Scan Previous Track) */
	0x81, 0x02, /*   Input (Data, Variable, Absolute) */
	0x75, 0x03, /*   Report Size (3) */
	0x95, 0x01, /*   Report Count (1) */
	0x81, 0x03, /*   Input (Constant, Variable, Absolute) */
	0xc0,       /* End Collection */
};

static uint8_t last_input_report;
static bool notifications_enabled;
static uint8_t control_point;

static ssize_t read_hids_info(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			      void *buf, uint16_t len, uint16_t offset)
{
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(hids_info));
}

static ssize_t read_report_map(struct bt_conn *conn, const struct bt_gatt_attr *attr,
			       void *buf, uint16_t len, uint16_t offset)
{
	return bt_gatt_attr_read(conn, attr, buf, len, offset, consumer_report_map,
				 sizeof(consumer_report_map));
}

static ssize_t read_input_report(struct bt_conn *conn, const struct bt_gatt_attr *attr,
				 void *buf, uint16_t len, uint16_t offset)
{
	return bt_gatt_attr_read(conn, attr, buf, len, offset, &last_input_report,
				 sizeof(last_input_report));
}

static ssize_t read_report_reference(struct bt_conn *conn, const struct bt_gatt_attr *attr,
				     void *buf, uint16_t len, uint16_t offset)
{
	return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data,
				 sizeof(input_report_reference));
}

static ssize_t write_control_point(struct bt_conn *conn, const struct bt_gatt_attr *attr,
				   const void *buf, uint16_t len, uint16_t offset,
				   uint8_t flags)
{
	if (offset + len > sizeof(control_point)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(&control_point + offset, buf, len);
	return len;
}

static void input_ccc_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	notifications_enabled = value == BT_GATT_CCC_NOTIFY;
	LOG_INF("Consumer input notifications %s",
		notifications_enabled ? "enabled" : "disabled");
}

BT_GATT_SERVICE_DEFINE(tactile_hids_service,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_HIDS),
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_INFO, BT_GATT_CHRC_READ, BT_GATT_PERM_READ,
			       read_hids_info, NULL, (void *)&hids_info),
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT_MAP, BT_GATT_CHRC_READ,
			       BT_GATT_PERM_READ, read_report_map, NULL, NULL),
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_REPORT, BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ_ENCRYPT, read_input_report, NULL, NULL),
	BT_GATT_CCC(input_ccc_changed, BT_GATT_PERM_READ_ENCRYPT | BT_GATT_PERM_WRITE_ENCRYPT),
	BT_GATT_DESCRIPTOR(BT_UUID_HIDS_REPORT_REF, BT_GATT_PERM_READ, read_report_reference,
			   NULL, (void *)&input_report_reference),
	BT_GATT_CHARACTERISTIC(BT_UUID_HIDS_CTRL_POINT, BT_GATT_CHRC_WRITE_WITHOUT_RESP,
			       BT_GATT_PERM_WRITE, NULL, write_control_point, &control_point),
);

void hid_service_init(void)
{
	LOG_INF("Consumer Control HID service ready (report ID 1)");
}

bool hid_service_notifications_enabled(void)
{
	return notifications_enabled;
}

int hid_service_send_input_report(uint8_t report)
{
	int err;

	if (!notifications_enabled) {
		return -EACCES;
	}

	last_input_report = report;
	err = bt_gatt_notify(NULL,
			     &tactile_hids_service.attrs[HIDS_INPUT_REPORT_ATTRIBUTE_INDEX],
			     &last_input_report, sizeof(last_input_report));
	if (err != 0) {
		LOG_WRN("Consumer report notification failed (%d)", err);
	}

	return err;
}
