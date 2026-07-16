# ADR 0005: Development-Board Selection Criteria

## Status

Accepted

## Context

The project needs a first board for bench experiments without claiming that a
specific board definition, pinout, or electrical characteristic is settled.

## Decision

Select an nRF52840-class development board using documented criteria: BLE HID
support in candidate frameworks, availability, reproducibility, debug access,
power measurement capability, sufficient accessible GPIO, battery-prototype
compatibility, documentation quality, cost, and community support. Record the
chosen board and its evidence in a new ADR.

## Alternatives

- Choose a board based only on current availability.
- Design a custom board before validation.
- Use an MCU class without a documented BLE HID path.

## Consequences

Board selection stays evidence-driven and reversible. It adds a short research
step before firmware work but avoids inventing board-specific APIs.

## Follow-up work

Create a comparison table with sources, select a board, and add only the board
configuration that its verified framework documentation supports.
