# Product Requirements Document

## Purpose

TactileRide explores a tactile, glove-friendly Bluetooth media controller near
the left handlebar grip. The primary problem is avoiding tiny, visual touchscreen
media controls while a phone is mounted on a motorcycle.

## Confirmed requirements

- V1 must expose volume up, volume down, play/pause, next track, and previous
  track.
- V1 must use standard Bluetooth HID Consumer Control compatibility.
- V1 must not require a companion mobile application.
- Development starts with bench testing; no riding test is implied.
- The project must remain open, replaceable, reproducible, and suitable for a
  future 3D-printable enclosure and mount.

## Current assumptions

- The reference phone is a Samsung Galaxy S23 Ultra mounted horizontally on a
  Royal Enfield Hunter 350.
- The controller is mounted near the left grip and operated by the left thumb.
- A vertical rocker, concave central button, raised forward paddle, and guarded
  rear paddle are promising ways to differentiate the five actions.
- A BLE HID peripheral on an nRF52840-class MCU is a suitable starting point.

## Open questions

- Which development board best balances BLE support, power measurement access,
  input pins, availability, and reproducibility?
- What dimensions, switch forces, travel, and guard geometry work with common
  motorcycle gloves?
- Which host behaviours vary across Android, desktop, and other HID hosts?
- What battery chemistry, charging approach, and sleep target are appropriate?

## Deferred ideas and exclusions

- Touchscreen simulation, display, voice control, mobile app, GPS, navigation,
  motorcycle CAN, safety-critical control, audio streaming, and cloud services.
- Production PCB files and final enclosure CAD.
- Waterproofing, road legality, certification, and safety claims.

## Acceptance criteria for the first proof of concept

1. A documented development board is paired to a desktop test host.
2. Each of the five actions produces the intended standard HID Consumer Control
   event in a repeatable bench procedure.
3. Reconnection behaviour is observed and recorded after a host restart or
   connection interruption.
4. The result, host environment, and unresolved compatibility limits are
   recorded; no riding claim is made.
