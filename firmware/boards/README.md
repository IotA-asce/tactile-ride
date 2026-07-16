# Board Policy

## Phase 1 reference target

The Phase 1 reference target is the Seeed Studio XIAO BLE Zephyr target
`xiao_ble/nrf52840`, selected in ADR 0005. The application does not use the
Sense-only variant and does not require any Sense hardware feature.

## Intentionally absent configuration

No Devicetree overlay, GPIO assignment, or switch circuit is included here.
Physical controls have not been selected or bench-tested, so assigning pins
would fabricate an electrical design. The application receives logical raw
button samples through `button_input` instead.

`CONFIG_TACTILE_RIDE_DEV_AUTO_DEMO=y` is a development-only, compile-time input
source for exercising the input/debounce/media/HID path. It is not a substitute
for hardware testing and is disabled by default.

## Future change rule

When a physical switch circuit is documented, add a board-specific overlay and
input driver in this directory or a documented board layer. Keep raw GPIO access
outside the media-action, report-construction, and BLE connection modules.
