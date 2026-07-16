# Requirements

## Confirmed functional requirements

| ID | Requirement | Acceptance criterion |
| --- | --- | --- |
| FR-01 | Send volume-up input. | Bench host observes the standard HID action. |
| FR-02 | Send volume-down input. | Bench host observes the standard HID action. |
| FR-03 | Send play/pause input. | Bench host observes the standard HID action. |
| FR-04 | Send next-track input. | Bench host observes the standard HID action. |
| FR-05 | Send previous-track input. | Bench host observes the standard HID action. |
| FR-06 | Pair and reconnect to a previously paired phone where supported. | Procedure and observed result are recorded. |

## Confirmed non-functional requirements

| ID | Requirement | Acceptance criterion |
| --- | --- | --- |
| NFR-01 | Controls support eyes-free tactile differentiation. | Static ergonomic test protocol is executed and recorded. |
| NFR-02 | Controls are usable with motorcycle gloves. | Test participants can identify intended controls in a controlled mock-up. |
| NFR-03 | V1 uses BLE HID Consumer Control. | HID report design and host observations are documented. |
| NFR-04 | V1 has no mandatory companion app. | The five actions work through host HID support alone. |
| NFR-05 | Initial work is bench-first. | No installation or riding test precedes documented bench results. |

## Current assumptions

- An nRF52840-class MCU can satisfy the early BLE HID investigation.
- A vertical rocker and three distinct press controls can be differentiated by a
  gloved left thumb.
- The controller can be battery powered for the first hardware prototype.

## Open questions

- Supported host matrix, HID usage details, latency budget, target battery life,
  charging safety, switch selection, mounting range, and vibration targets.

## Deferred requirements

- IP rating, regulatory certification, road-legal status, final CAD, production
  PCB, and motorcycle electrical integration.
