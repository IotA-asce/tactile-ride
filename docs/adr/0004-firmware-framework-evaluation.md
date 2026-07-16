# ADR 0004: Firmware Framework Evaluation

## Status

Proposed

## Context

The likely MCU class has BLE support, and Zephyr RTOS is the preferred initial
candidate. The project does not yet have a board, HID proof of concept, power
measurements, or maintainability evidence.

## Decision

Evaluate Zephyr against lighter alternatives before creating application
firmware. Compare documented BLE HID Consumer Control support, board support,
power-management facilities, test/debug workflow, build reproducibility,
licensing, community maintenance, and contributor accessibility. Record the
result in a superseding ADR.

## Alternatives

- Adopt Zephyr immediately without evaluation.
- Use a vendor SDK directly.
- Use an Arduino-style framework or another lightweight RTOS/framework.

## Consequences

The first implementation is delayed until comparison evidence exists, reducing
the risk of embedding a reversible choice throughout the repository.

## Follow-up work

Select a candidate development board, define a desktop HID proof-of-concept test,
and document results for at least Zephyr and one lighter alternative.
