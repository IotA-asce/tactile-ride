# Safety and Responsible Development

## Development status warning

TactileRide is an experimental project. It is not certified, waterproof,
road-legal, or proven safe for use while riding. Nothing in this repository is a
claim of compliance, fitness for a purpose, or safe vehicle operation.

## Confirmed safeguards

- V1 does not control motorcycle safety-critical systems or connect to vehicle
  CAN bus.
- Development is bench-first, followed only by static mock-ups and controlled
  tests when their protocols are defined.
- The project does not claim a final enclosure, production PCB, environmental
  rating, or electrical integration.

## Current assumptions

- Tactile differentiation may reduce the need to look at a phone, but it must be
  validated and must not be treated as a safety assurance.
- A battery-powered prototype isolates early learning from motorcycle electrical
  systems.

## Open questions

- Appropriate electrical protection, battery/charging design, ingress targets,
  mounting retention, vibration resistance, thermal behaviour, and legal
  requirements.

## Deferred ideas

- Any public statement of road suitability, certification, weather resistance,
  or safe riding use.

## Required practices

1. Do not use a prototype in a way that distracts the rider.
2. Do not connect early prototypes to motorcycle power or safety-critical
   systems.
3. Stop a test after unexpected heat, swelling, damage, intermittent control, or
   mounting movement; document the observation.
4. Treat every field condition as unvalidated until a controlled protocol and
   evidence exist.

## Acceptance criteria

- Future test plans state their safety boundaries and abort conditions.
- Future documentation distinguishes observed evidence from assumptions.
- No release describes the project as certified, waterproof, road-legal, or safe
  for use while riding without verifiable evidence.
