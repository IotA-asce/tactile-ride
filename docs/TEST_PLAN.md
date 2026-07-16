# Test Plan

## Test philosophy

TactileRide uses a bench-first progression. Tests should establish observable
behaviour in controlled conditions before moving to static ergonomic mock-ups or
environmental fixtures. Riding tests are not part of the current plan.

## Test levels

| Level | Objective | Evidence | Status |
| --- | --- | --- | --- |
| Documentation | Validate required files, headings, and local links. | CI log and repository validation output. | Available after bootstrap |
| Firmware unit | Verify action mapping, debounce, and state logic. | Automated test output. | Deferred until framework selection |
| BLE HID bench | Verify pairing, each media action, and reconnection. | Host/board versions, procedure, and observations. | Planned |
| Breadboard input | Verify five tactile inputs and accidental activation resistance. | Wiring, input log, and repeatable procedure. | Planned |
| Static ergonomic mock-up | Evaluate left-thumb reach and differentiation with gloves. | Protocol, participants, conditions, results, limitations. | Planned |
| Power | Measure active, idle, sleep, wake, and reconnect behaviour. | Measurement method and raw values. | Planned |
| Environmental/vibration | Evaluate controlled test conditions only. | Fixture, conditions, observations, failures. | Deferred |

## Confirmed requirements

- Every claimed result must state method, hardware/firmware revision, and known
  limitations.
- Bench verification precedes any installation or riding evaluation.
- Tests must never imply certification, waterproofing, road legality, or rider
  safety.

## Current assumptions

- A desktop BLE host can provide useful initial HID observations.
- Static mock-ups can assess reach and tactile differentiation before any dynamic
  use is considered.

## Open questions

- Specific hosts, measurement equipment, sample size, glove set, repeat counts,
  pass thresholds, and vibration profile.

## Deferred ideas

- Formal environmental qualification, certification testing, and on-road tests.

## Acceptance criteria for Phase 1 test evidence

1. Identify board, firmware revision, host OS, host Bluetooth adapter, and test
   date.
2. Record pairing, all five actions, disconnection, and reconnection steps.
3. Record actual observations, including failures and unsupported host behaviour.
4. Keep raw notes or logs with the test artifact.
