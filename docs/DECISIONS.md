# Decisions Index

## Current decisions

| ADR | Decision | Status |
| --- | --- | --- |
| 0001 | Separate documentation, firmware, electronics, mechanical, tooling, and community areas. | Accepted |
| 0002 | Use BLE HID Consumer Control rather than touchscreen automation for V1. | Accepted |
| 0003 | Do not require a mobile app for V1. | Accepted |
| 0004 | Evaluate Zephyr against lighter alternatives before implementation. | Proposed |
| 0005 | Select the development board through documented criteria. | Accepted |
| 0006 | Start with a battery-powered prototype before motorcycle electrical integration. | Accepted |
| 0007 | Keep software, hardware, and documentation licensing candidates separate pending review. | Proposed |

Read the individual records in [`docs/adr/`](adr/). A future decision must add a
new ADR or supersede the relevant record rather than silently changing this
index.

## Confirmed decision process

- Each ADR uses status, context, decision, alternatives, consequences, and
  follow-up work.
- Decisions are reversible when evidence is incomplete.

## Current assumptions

- Separate decision records make it easier for contributors to understand why
  scope boundaries exist.

## Open questions

- Framework, board, exact licence set, electrical design, enclosure geometry,
  and test targets.

## Deferred ideas

- Decisions about production release, vehicle integration, or optional features.
