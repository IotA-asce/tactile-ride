# ADR 0004: Firmware Framework Evaluation

## Status

Accepted for Phase 1

## Context

The likely MCU class has BLE support, and Zephyr RTOS was the preferred initial
candidate. The Phase 1 task requires a testable desktop and bench BLE HID proof
of concept while retaining the ability to reconsider the framework before later
hardware work.

## Decision

Use Zephyr v4.4.0, pinned by `west.yml` to commit
`684c9e8f32e4373a21098559f748f06915f950c9`, for Phase 1. Zephyr provides the
official BLE HID peripheral sample used as a service-shape reference, the
verified XIAO board target, a reproducible manifest, and ztest/twister support
for the hardware-independent logic.

This is a Phase 1 implementation decision, not a permanent framework lock for
all future TactileRide hardware.

## Alternatives

- Use a vendor SDK directly.
- Use an Arduino-style framework or another lightweight RTOS/framework.
- Delay firmware until a broader framework comparison has completed.

## Consequences

Phase 1 gets a documented, current Zephyr path rather than blocking on a broad
comparison. The app keeps media logic independent of Zephyr GPIO APIs and board
pins, which limits framework coupling. A future alternative still needs its own
evidence and superseding decision record.

## Follow-up work

Build and test the Phase 1 proof of concept, record actual host observations,
and revisit the framework selection before production-oriented hardware or a
release build.
