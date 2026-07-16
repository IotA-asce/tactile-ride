# Contributing to TactileRide

## Before starting

Read the product documents, relevant ADRs, and [`AGENTS.md`](AGENTS.md). This is
an early-stage project: useful evidence is more valuable than speculative
implementation.

## Contribution workflow

1. Inspect the current repository and open issues before proposing work.
2. Explain broad architectural or safety-impacting changes before implementing
   them.
3. Create one focused branch; never make the change directly on `main`.
4. Keep commits small, understandable, and limited to the stated task.
5. Run the applicable validation, tests, linting, and builds. State commands not
   run and why.
6. Update requirements, test plans, ADRs, and safety documentation when a change
   affects them.
7. Open a pull request using the checklist and include evidence, limitations, and
   unresolved risks.

## Hardware and ergonomic contributions

- Do not present final CAD, production PCB work, weather resistance, vibration
  resistance, certification, road legality, or riding safety as established
  without supporting evidence.
- Keep test conditions, component versions, measurement methods, and raw
  observations with the contribution where practical.
- Start with bench or static mock-up work. Do not introduce motorcycle
  safety-critical control or vehicle bus integration.

## Issues and proposals

Use the supplied templates for reproducible bugs, feature requests, hardware
test reports, and design proposals. Design proposals should identify confirmed
requirements, assumptions, open questions, alternatives, and acceptance
criteria.
