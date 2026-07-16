# ADR 0003: No Mandatory Mobile Application for V1

## Status

Accepted

## Context

A companion application adds platform maintenance, pairing/configuration
dependencies, privacy considerations, and more rider-facing surface area.

## Decision

V1 must function through standard host HID support without a mandatory mobile
application. Optional tooling may be considered only as a separately scoped,
non-required extension.

## Alternatives

- Android-only companion application.
- Cross-platform companion application.
- Web, cloud, or account-backed configuration service.

## Consequences

Initial setup and behaviour are constrained by host Bluetooth HID capabilities,
but the baseline remains platform-independent where practical and has fewer
software dependencies.

## Follow-up work

Verify pairing and reconnection expectations on selected hosts. Revisit only if
an optional tool demonstrably solves a documented need without becoming required.
