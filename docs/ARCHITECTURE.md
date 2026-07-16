# Architecture

## Current architecture

TactileRide is planned as a battery-powered BLE HID Consumer Control peripheral.
The physical control layer detects five deliberate input actions. A firmware
input layer converts them into logical media actions, and a transport layer
publishes standard HID Consumer Control reports to a paired host.

```text
Tactile controls -> input abstraction -> media-action mapping -> BLE HID Consumer Control -> host
                         |                       |
                         +--- power state --------+
```

This is a proposed boundary, not implemented firmware. The framework evaluation
ADR records why Zephyr is a candidate rather than an irreversible commitment.

## Confirmed decisions

- Use BLE HID Consumer Control instead of touchscreen automation for V1.
- Keep hardware-specific code behind clear input, power, and transport
  interfaces when implementation begins.
- Organise firmware, electronics, mechanical, documentation, and tooling as
  separate repository areas.
- Start with a battery-powered bench prototype rather than motorcycle power.

## Current assumptions

- An nRF52840-class development board is a suitable family to evaluate.
- The selected firmware framework will provide BLE, HID, power-management, and
  test support without a companion application.

## Open questions

- Zephyr versus lighter alternatives, board selection, pairing policy,
  reconnection strategy, input debouncing, power-state model, and test host
  coverage.

## Deferred ideas

- Vehicle electrical interfaces, CAN, mobile integration, display, voice, audio
  streaming, and any cloud component.

## Acceptance criteria

- The first firmware design documents module boundaries and HID report behaviour
  before implementation.
- Board-specific code is isolated from media-action logic.
- Architecture changes are made through a new or superseding ADR.
