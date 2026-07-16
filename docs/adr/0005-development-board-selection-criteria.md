# ADR 0005: Development-Board Selection Criteria

## Status

Accepted

## Context

The project needs a first board for bench experiments without claiming that a
specific board definition, pinout, or electrical characteristic is settled. The
Phase 1 task needs an actual Zephyr target for a desktop and bench BLE HID build.

## Decision

Select the Seeed Studio XIAO BLE as the **Phase 1 reference target** and build
with Zephyr board target `xiao_ble/nrf52840`. Zephyr v4.4.0 documents that target
for the nRF52840 XIAO BLE board. The Sense target
`xiao_ble/nrf52840/sense` remains a separate optional variant; no Sense feature
is used by this proof of concept.

This selection uses the existing BLE support, compact reproducible development
board, available debug/UF2 paths, and accessible GPIO for a later prototype. It
does not select final production hardware or assign any tactile-control pins.

## Alternatives

- Use a Nordic development kit with onboard debug probe.
- Design a custom board before validation.
- Use another nRF52840-class board with a documented Zephyr target.

## Consequences

The app must keep input and media mapping independent of this board's GPIO
assignments. A later board comparison may replace this reference target without
changing the Consumer Control domain logic.

## Follow-up work

Build the POC for `xiao_ble/nrf52840`, record actual flash and host-test
observations, and compare alternative boards before a reproducible reference
release. Do not add an overlay until the switch circuit and pins are documented.
