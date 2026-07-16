# Roadmap

All phases below are **pending** unless a future repository artifact and test
record demonstrate otherwise. Ordering communicates dependencies, not delivery
dates.

| Phase | Outcome | Entry conditions | Exit acceptance criteria | Status |
| --- | --- | --- | --- | --- |
| 0 | Requirements and architecture | Repository bootstrap | Requirements, ADRs, safety, test plan, and backlog reviewed | Pending review |
| 1 | Desktop BLE HID proof of concept | ADRs 0004 and 0005 select the Phase 1 framework and reference target | Five consumer-control actions and reconnection are observed on a bench host | In progress; bench evidence pending |
| 2 | Breadboard tactile controller | Phase 1 evidence | Five physical inputs are mapped and documented on a battery-powered bench prototype | Pending |
| 3 | Static motorcycle ergonomic mock-up | Phase 2 evidence and safe mock-up plan | Reach, differentiation, and accidental-activation observations are recorded without riding | Pending |
| 4 | Battery and sleep optimisation | Phase 2 power baseline | Measured power states and wake/reconnect behaviour meet a documented prototype target | Pending |
| 5 | Enclosure and mount prototypes | Ergonomic findings | Reproducible prototype CAD and mounting evaluations are documented | Pending |
| 6 | Controlled environmental and vibration testing | Prototype fixture and test protocol | Controlled test results and limitations are recorded; no certification claim is made | Pending |
| 7 | Reproducible open-source reference build | Validated prototype evidence | Build instructions, BOM, source, and test evidence reproduce a reference build | Pending |
| 8 | Optional extensions | Phase 7 review | Any extension has separate scope, safety review, and ADR | Deferred |

## Confirmed requirements

- Work progresses from bench evidence toward increasingly representative static
  and controlled testing.
- No roadmap phase is reported complete without repository evidence.

## Current assumptions

- Phase 1 can be performed with a development board and desktop test host before
  a custom tactile assembly exists.

## Open questions

- Exact phase gates, measurement targets, test participants, budget, and host
  compatibility matrix remain to be defined.

## Deferred ideas

- Vehicle electrical integration and feature expansion are outside the current
  roadmap baseline.
