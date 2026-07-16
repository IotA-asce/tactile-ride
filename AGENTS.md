# Agent Instructions

## Working agreement

- Inspect the repository and current Git state before editing.
- Never work directly on `main`; use one branch per meaningful change.
- Explain a proposed change before broad architectural work.
- Prefer small, reviewable commits and preserve useful existing files.
- Run relevant tests, linting, builds, and validation. Never report an
  unexecuted command as successful.
- Update ADRs and project documentation when an architectural decision changes.
- Avoid unnecessary dependencies and keep hardware-specific code behind clear
  interfaces.
- Do not generate final CAD, production PCB files, certification claims, or
  safety claims without evidence.
- Do not claim a milestone, a physical characteristic, a board API, or a test
  result that repository evidence does not support.

## TactileRide guardrails

- Maintain eyes-free, glove-friendly, left-thumb operation as the ergonomic
  objective; treat any physical layout as provisional until it is tested.
- Use standard Bluetooth HID Consumer Control rather than touchscreen automation
  unless a documented decision changes that scope.
- Keep a mandatory mobile app, vehicle integration, and safety-critical controls
  out of V1.
- Test on the bench before static motorcycle mock-ups, and use controlled tests
  before any riding evaluation.

## Task close-out

End every task with:

1. Files changed.
2. Commands run and their results.
3. Any unexecuted checks.
4. Unresolved assumptions, risks, or follow-up work.
