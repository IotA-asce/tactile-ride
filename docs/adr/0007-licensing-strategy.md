# ADR 0007: Licensing Strategy

## Status

Proposed

## Context

Software, hardware design files, and documentation have different sharing and
attribution needs. Selecting one ambiguous licence for all artifacts risks
confusing contributors and downstream users.

## Decision

Maintain separate candidate tracks until a contributor and project-governance
review selects final texts:

| Artifact class | Candidate | Rationale to evaluate |
| --- | --- | --- |
| Firmware and tools | Apache-2.0 or MIT | Permissive software licensing candidates; Apache-2.0 has an explicit patent grant. |
| Electronics and mechanical design | CERN-OHL-S v2 or CERN-OHL-P v2 | Open hardware candidates with different reciprocity expectations. |
| Documentation and content | CC BY 4.0 | Attribution-oriented documentation/content candidate. |

No candidate is adopted and no licence grant is made by this ADR alone.

## Alternatives

- Apply one software licence to every artifact.
- Select final licences without hardware/documentation review.
- Leave all licensing discussion undocumented.

## Consequences

The repository remains clear about its preliminary state while avoiding an
unsupported claim of compatibility. Contributors must not assume that future
firmware, hardware, and documentation will share one licence.

## Follow-up work

Verify the current official texts and compatibility implications, obtain project
governance approval, add exact licence texts and file-level notices, and replace
this proposal with an adopted decision before a public reference release.
