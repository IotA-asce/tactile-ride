# Implementation Plan

## Current state

Phase 1 BLE HID implementation is in progress. Zephyr v4.4.0 and the XIAO BLE
reference target are recorded in ADRs 0004 and 0005. There is no schematic, PCB
layout, enclosure CAD, physical switch wiring, or physical test result yet.

## Next increments

1. Implement and test Consumer Page report construction, debounce, press
   handling, release reports, volume repeat, and disconnected handling.
2. Build the Zephyr application for `xiao_ble/nrf52840`.
3. Run the documented Android bench procedure and record observations rather
   than inferring compatibility from a successful build.
4. Review framework and board evidence before adding physical switch wiring.
5. Add a five-input breadboard controller only after the transport behaviour is
   demonstrated on the bench.

## Confirmed implementation constraints

- Do not implement touchscreen automation, a companion app, vehicle interfaces,
  or a production hardware design in V1.
- Keep input mapping independent of board-specific pin configuration and BLE
  transport implementation.
- Make small, reviewable commits; validate every generated artifact.

## Current assumptions

- A desktop proof of concept reduces uncertainty before physical-control work.
- Zephyr v4.4.0 and the XIAO BLE reference target are adequate for Phase 1 but
  remain reversible before a reference hardware release.

## Open questions

- Test host, Android behaviour, HID host details, input components, battery,
  power targets, and GPIO assignments.

## Deferred ideas

- Enclosure finalisation, PCB fabrication, vehicle electrical connection,
  environmental qualification, and optional extensions.

## Acceptance criteria for the next task

- The reference-target build and logic tests pass.
- The manual verification guide names the Android observations to record.
- Unperformed hardware tests remain explicitly pending.
