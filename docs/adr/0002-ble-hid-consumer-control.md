# ADR 0002: BLE HID Consumer Control Rather Than Touchscreen Automation

## Status

Accepted

## Context

V1 needs five conventional media actions while avoiding a mandatory application
and phone-specific UI automation.

## Decision

Target standard Bluetooth Low Energy HID Consumer Control usage for volume up,
volume down, play/pause, next track, and previous track. Do not implement
touchscreen simulation in V1.

## Alternatives

- Touchscreen automation or accessibility-based control.
- A proprietary phone protocol with a companion application.
- Bluetooth audio remote profiles or audio streaming.

## Consequences

HID narrows V1 to host-supported actions and avoids reproducing a phone UI. Host
behaviour and exact report details still require bench verification.

## Follow-up work

Document the HID report design and a host compatibility matrix during the desktop
proof of concept. Record deviations or unsupported behaviour as evidence, not
assumptions.
