# Test Plan

## Test philosophy

TactileRide uses a bench-first progression. Tests should establish observable
behaviour in controlled conditions before moving to static ergonomic mock-ups or
environmental fixtures. Riding tests are not part of the current plan.

## Test levels

| Level | Objective | Evidence | Status |
| --- | --- | --- | --- |
| Documentation | Validate required files, headings, and local links. | CI log and repository validation output. | Available after bootstrap |
| Firmware unit | Verify action mapping, debounce, repeat, release, and disconnected logic. | `native_sim` ztest output. | In progress |
| BLE HID bench | Verify pairing, each media action, and reconnection. | Host/board versions, procedure, and observations. | Planned; hardware evidence pending |
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

- A `native_sim` logic suite can exercise non-Bluetooth domain logic while the
  reference-target build verifies the Zephyr integration compiles.
- A desktop BLE host can provide useful initial HID observations.
- Static mock-ups can assess reach and tactile differentiation before any dynamic
  use is considered.

## Open questions

- Specific Android device/OS build, YouTube Music version, desktop hosts,
  measurement equipment, sample size, glove set, repeat counts, pass thresholds,
  and vibration profile.

## Deferred ideas

- Formal environmental qualification, certification testing, and on-road tests.

## Acceptance criteria for Phase 1 test evidence

1. Identify board, firmware revision, host OS, host Bluetooth adapter, and test
   date.
2. Record pairing, all five actions, disconnection, and reconnection steps.
3. Record actual observations, including failures and unsupported host behaviour.
4. Keep raw notes or logs with the test artifact.

## Phase 1 automated acceptance criteria

1. The logic suite covers debounce state transitions, rejected short bounce,
   held-volume repeat, non-repeating media actions, Consumer Page bit mapping,
   zero release reports, and disconnected drops.
2. The Zephyr application builds for `xiao_ble/nrf52840` using the documented
   workspace manifest and toolchain.
3. A successful build is not reported as Android, YouTube Music, locked-screen,
   flash, or reconnection evidence.

## Current automated evidence

The pinned Zephyr workspace has built `xiao_ble/nrf52840` locally and in the
[Linux firmware-validation workflow](https://github.com/IotA-asce/tactile-ride/actions/runs/29529088670).
That workflow also passed the seven-case `native_sim` Twister suite. The same
scenario is statically filtered on the current macOS host because Zephyr
requires Linux for that platform; the filtered local run is not a test pass.
Neither automated result is BLE host or Android bench evidence.
