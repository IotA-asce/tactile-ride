# ADR 0006: Initial Battery-Powered Prototype

## Status

Accepted

## Context

Motorcycle electrical integration introduces unknown voltage, transient,
grounding, protection, installation, and safety considerations that are not
needed to validate five BLE media actions.

## Decision

Start with a battery-powered bench prototype. Defer any motorcycle electrical
connection until its own requirements, design review, test plan, and safety
assessment exist.

## Alternatives

- Power the first prototype from the motorcycle.
- Use a permanently wired prototype without battery testing.
- Delay all work until a production power system is designed.

## Consequences

Early experiments can focus on input, HID, reconnection, and sleep behaviour.
Vehicle power requirements remain deliberately unresolved rather than hidden.

## Follow-up work

Define the prototype battery and charging safety requirements, measure power
states, and create a separate decision record before considering vehicle power.
