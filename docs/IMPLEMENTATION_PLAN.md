# Implementation Plan

## Current state

This repository is at the documentation bootstrap. No BLE firmware, schematic,
PCB layout, enclosure CAD, or physical test result exists yet.

## Next increments

1. Select a development board against the criteria in ADR 0005 and record the
   evidence in a new ADR or decision update.
2. Evaluate Zephyr and at least one lighter alternative against BLE HID support,
   test tooling, power-management support, documentation, and reproducibility.
3. Define a minimal desktop BLE HID proof-of-concept test procedure before adding
   application code.
4. Implement only the selected proof-of-concept path, including one action at a
   time and a documented host-observation method.
5. Add a five-input breadboard controller only after the transport behaviour is
   demonstrated on the bench.

## Confirmed implementation constraints

- Do not implement touchscreen automation, a companion app, vehicle interfaces,
  or a production hardware design in V1.
- Keep input mapping independent of board-specific pin configuration and BLE
  transport implementation.
- Make small, reviewable commits; validate every generated artifact.

## Current assumptions

- A desktop proof of concept reduces uncertainty before mechanical work.
- Zephyr is the preferred initial candidate but not a settled framework choice.

## Open questions

- Board, framework, test host, HID report details, input components, battery,
  and power targets.

## Deferred ideas

- Enclosure finalisation, PCB fabrication, vehicle electrical connection,
  environmental qualification, and optional extensions.

## Acceptance criteria for the next task

- A board-selection record exists with reproducibility and power-measurement
  rationale.
- The task plan names the test host and expected five-action observations.
- No firmware is added until that selection and plan are reviewed.
