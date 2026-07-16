# ADR 0001: Repository Structure

## Status

Accepted

## Context

TactileRide has coupled firmware, electronics, mechanical, documentation, and
community work, but no implementation should be invented merely to fill folders.

## Decision

Use a monorepo with `.github/`, `docs/`, `docs/adr/`, `firmware/`,
`firmware/app/`, `firmware/boards/`, `firmware/tests/`, `electronics/`,
`electronics/schematics/`, `electronics/pcb/`, `electronics/bom/`,
`mechanical/`, `mechanical/cad/`, `mechanical/prototypes/`,
`mechanical/exports/`, `tools/`, and `LICENSES/`. Empty implementation areas use
only `.gitkeep` files until real work exists.

## Alternatives

- Keep all work in a flat repository.
- Use separate repositories for firmware, hardware, and mechanical design.

## Consequences

The monorepo makes cross-discipline decisions and reproducible reference builds
easier to trace. It also requires owners to avoid coupling work prematurely.

## Follow-up work

Add substantive artifacts to their owning directories only when an approved
increment needs them. Revisit repository boundaries if release processes make a
split demonstrably useful.
