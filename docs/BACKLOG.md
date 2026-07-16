# Project Backlog

## Backlog rules

All entries are planned unless their status says otherwise. An item may only be
marked complete when its stated acceptance criterion has repository evidence.
Dependencies are prerequisites, not proof that the dependent work is complete.

## Product research

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| PR-001 | Define a host compatibility research protocol. | Supported host candidates, observation method, and evidence format are documented. | ADR 0002 | Planned |
| PR-002 | Characterise reference use conditions. | Phone orientation, controller region, left-thumb reach assumptions, and non-riding boundary are documented. | PR-001 | Planned |

## Firmware

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| FW-001 | Use Zephyr for the reversible Phase 1 proof of concept. | Zephyr v4.4.0 is pinned; ADR 0004 records scope and reconsideration point. | ADR 0004 | Complete for Phase 1 |
| FW-002 | Build desktop BLE HID proof of concept. | Five actions and reconnect observation are recorded using the reference board and host. | FW-001, EL-001 | In progress; bench evidence pending |
| FW-003 | Define hardware-independent input mapping. | Interface and unit tests isolate button logic from GPIO assignments. | FW-001 | In progress; Linux CI execution pending |

## Electronics

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| EL-001 | Maintain the Phase 1 reference-board decision. | ADR 0005 records `xiao_ble/nrf52840`; no final-board or GPIO claim is made. | ADR 0005 | Complete for Phase 1 |
| EL-002 | Define five-input breadboard experiment. | Switch candidates, wiring plan, and safe bench procedure are documented. | FW-002, ER-001 | Planned |
| EL-003 | Define prototype battery and charging requirements. | Chemistry, protection assumptions, measurement plan, and unresolved hazards are recorded. | PO-001 | Planned |

## Mechanical design

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| ME-001 | Create non-final tactile layout studies. | At least two reversible, dimensioned concepts map all five actions without final CAD claims. | PR-002 | Planned |
| ME-002 | Create static mounting mock-up studies. | Mock-up attachment assumptions and reach-adjustment range are documented. | ME-001, ER-001 | Planned |
| ME-003 | Define enclosure and mount prototype requirements. | Findings are translated into requirements without claiming weather or vibration resistance. | ME-002, EV-001 | Deferred |

## Ergonomic testing

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| ER-001 | Define static gloved-thumb test protocol. | Controls, glove variation, repetitions, observations, abort conditions, and consent/privacy handling are documented. | PR-002, docs/SAFETY.md | Planned |
| ER-002 | Run static tactile differentiation evaluation. | Results identify each input's reach, confusion, and accidental-activation observations; no riding claim is made. | ER-001, ME-001 | Planned |

## Power optimisation

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| PO-001 | Define power measurement method and targets. | Tools, measurement points, active/idle/sleep/wake states, and provisional targets are documented. | EL-001, FW-001 | Planned |
| PO-002 | Measure prototype power states. | Raw measurements, method, conditions, and limitations are retained with the result. | FW-002, EL-003, PO-001 | Planned |
| PO-003 | Evaluate sleep and reconnect trade-offs. | Evidence compares latency, reconnect behaviour, and power for selected states. | PO-002 | Planned |

## Environmental testing

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| EV-001 | Define controlled environmental and vibration test plan. | Fixture, conditions, instrumentation, pass/fail observations, and abort criteria are reviewed. | ME-002, docs/SAFETY.md | Deferred |
| EV-002 | Execute controlled prototype evaluation. | Test log records actual results, failures, and limitations without certification claims. | EV-001, ME-003, PO-002 | Deferred |

## Documentation

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| DOC-001 | Maintain traceability from requirements to evidence. | PRD, requirements, ADR, test-plan, and backlog links are updated for each completed increment. | All implementation work | Ongoing |
| DOC-002 | Publish reference build documentation. | Reproducible build, BOM, test evidence, and limitation statements are complete. | FW-003, EL-003, ME-003, EV-002 | Deferred |
| DOC-003 | Adopt final licences and notices. | Official texts, file-level notices, and superseding ADR are approved. | ADR 0007 review | Deferred |

## Community and releases

| ID | Objective | Acceptance criteria | Dependencies | Status |
| --- | --- | --- | --- | --- |
| COM-001 | Define contribution triage and maintainer ownership. | Issue labels, review responsibility, and security contact path are confirmed by project governance. | Community feedback | Planned |
| COM-002 | Prepare an evidence-based prototype release checklist. | Scope, known limitations, licences, documentation, and reproducibility checks are documented. | DOC-002, DOC-003 | Deferred |

## Confirmed backlog constraints

- No entry authorises vehicle integration, production PCB fabrication, final CAD,
  certification, or road-use claims without a separately documented decision and
  evidence.
- Bench evidence precedes static mock-ups; static mock-ups precede any proposed
  controlled environmental work.

## Current assumptions

- Board and framework selection are the highest-leverage next uncertainties.
- The current backlog is intentionally small and will be refined by evidence.

## Open questions

- The host matrix, test measurements, ergonomic targets, battery targets,
  contributors, budget, and release process are not yet set.

## Deferred ideas

- Optional features, motorcycle electrical integration, and any claims of
  operational suitability.
