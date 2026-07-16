# TactileRide

TactileRide is an open-source, glove-friendly Bluetooth handlebar controller for
eyes-free media control on motorcycles. It is intended to let a rider use
deliberately different physical controls rather than small touchscreen targets.

## Problem and product concept

A phone mounted on a motorcycle handlebar can provide navigation and media, but
its touchscreen media controls are difficult to operate safely or reliably with
gloves. TactileRide explores a small controller near the left grip that sends
standard Bluetooth HID Consumer Control actions to a paired phone. The initial
reference scenario is a Samsung Galaxy S23 Ultra mounted horizontally on a
Royal Enfield Hunter 350.

The provisional V1 interface is a vertical volume rocker, a large concave
play/pause button, a raised forward next-track paddle, and a guarded or recessed
previous-track paddle. These are ergonomic hypotheses, not final CAD
requirements.

## Current status

**Bootstrap and planning only.** This repository contains requirements,
decision records, a test strategy, and project scaffolding. It does not contain
BLE firmware, a validated electrical design, a final enclosure, or evidence of
on-road suitability.

## V1 scope

- Volume up and volume down.
- Play/pause, next track, and previous track.
- Bluetooth Low Energy HID Consumer Control compatibility.
- A battery-powered, bench-tested prototype before any motorcycle power work.
- Tactile controls that are intended to be reachable by the left thumb while
  retaining the grip.

V1 explicitly excludes touchscreen simulation, a display, voice control, a
mandatory mobile app, navigation or GPS processing, CAN-bus integration,
safety-critical vehicle control, audio streaming, cloud services, production
PCB files, and final enclosure CAD.

## High-level architecture

The current candidate architecture is a low-power BLE HID Consumer Control
peripheral on an nRF52840-class development board. Firmware framework selection
is deliberately reversible: Zephyr RTOS is the preferred initial candidate but
has not been committed as a permanent choice. Hardware-specific inputs, power,
and BLE transport will be kept behind narrow interfaces when firmware begins.

## Repository layout

- [`docs/`](docs/) — product definition, architecture, testing, roadmap, ADRs,
  and backlog.
- [`firmware/`](firmware/) — future application, board definitions, and tests;
  no firmware is implemented yet.
- [`electronics/`](electronics/) — future schematics, PCB work, and bill of
  materials.
- [`mechanical/`](mechanical/) — future CAD, prototypes, and exports.
- [`tools/`](tools/) — lightweight repository validation.
- [`.github/`](.github/) — CI and community templates.
- [`LICENSES/`](LICENSES/) — documented licence candidates; no final grant has
  been selected.

## Development warning and safety

TactileRide is experimental and **not certified for road use**. It has not been
shown to be waterproof, vibration resistant, road-legal, safe while riding, or
compatible with any particular motorcycle or phone. Develop and test it on the
bench first. Do not use it in a way that distracts a rider or affects a
motorcycle's safety-critical controls. See [`docs/SAFETY.md`](docs/SAFETY.md).

## Contributing

Read [`CONTRIBUTING.md`](CONTRIBUTING.md), the project requirements, and the
relevant ADRs before proposing a change. Use one focused branch per meaningful
change, run the applicable checks, and document changed assumptions or decisions.

## Planned milestones

The planned sequence is requirements and architecture, desktop BLE HID proof of
concept, breadboard controller, static ergonomic mock-up, battery optimisation,
enclosure prototypes, environmental testing, and a reproducible reference
build. All phases are pending; details are in [`docs/ROADMAP.md`](docs/ROADMAP.md).

## Licence status

The project is evaluating separate permissive software, open-source-hardware,
and documentation licences. Until a final licence set is adopted, no licence
grant should be inferred from this repository. See [`LICENSES/README.md`](LICENSES/README.md)
and [`docs/adr/0007-licensing-strategy.md`](docs/adr/0007-licensing-strategy.md).
