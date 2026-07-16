# Architecture

## Phase 1 architecture

TactileRide Phase 1 is a desktop and bench BLE HID Consumer Control peripheral
on Zephyr v4.4.0. Its reference target is the Seeed Studio XIAO BLE using
`xiao_ble/nrf52840`; that target is not a production-board selection. The proof
of concept sends one-byte Consumer Page input reports for five actions and does
not need a mobile application.

```text
Raw input -> button input -> debounce/repeat -> logical media action -> Consumer report -> HID GATT notify -> host
                                    |                    |                 |
                                    +--- app orchestrator-+--- BLE state ---+
                                                        |
                                                  power-policy boundary
```

The app orchestrator receives logical action samples from the input abstraction;
it never sees a GPIO number. The reference board has no switch overlay because
the physical switch circuit and assignments are not yet documented. A
development-only auto-demo can exercise the same input path at compile time.

## Confirmed decisions

- Use BLE HID Consumer Control instead of touchscreen automation for V1.
- Use Zephyr v4.4.0 for Phase 1; revisit the framework before later hardware
  work if evidence warrants it.
- Use `xiao_ble/nrf52840` as the Phase 1 reference target only.
- Keep hardware-specific code behind clear input, power, and transport
  interfaces.
- Organise firmware, electronics, mechanical, documentation, and tooling as
  separate repository areas.
- Start with a battery-powered bench prototype rather than motorcycle power.

## Current assumptions

- A one-byte input report can express the five required Consumer Page usages as
  independent bits, followed by an all-zero release report.
- Bond persistence and reconnection can use Zephyr Bluetooth settings support;
  host behaviour still needs bench evidence.

## Open questions

- Exact Android host behaviour, pairing-reset UX, physical switch circuit,
  GPIO assignment, reconnect latency, power-state model, and test-host coverage.

## Deferred ideas

- Vehicle electrical interfaces, CAN, mobile integration, display, voice, audio
  streaming, and any cloud component.

## Acceptance criteria

- Build the app for the reference target and run the hardware-independent test
  suite.
- Record every actual Android, YouTube Music, locked-screen, flash, and
  reconnection observation separately from the intended procedure.
- Keep board-specific code isolated from media-action logic and update ADRs for
  material changes.
