# TactileRide Bootstrap Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Establish a documentation-first monorepo scaffold for the TactileRide
V1 discovery and prototype work without implementing BLE firmware.

**Architecture:** Store product decisions and open questions in Markdown,
separate future firmware, electronics, and mechanical work by responsibility,
and validate the scaffold with a dependency-free shell check in CI. Preserve
reversibility by documenting candidates rather than creating platform code.

**Tech Stack:** Git, Markdown, POSIX-compatible shell, GitHub Actions.

---

### Task 1: Establish the repository structure and project definition

**Files:**

- Modify: `README.md`, `AGENTS.md`
- Create: `docs/PRD.md`, `docs/GOALS.md`, `docs/REQUIREMENTS.md`,
  `docs/ARCHITECTURE.md`, `docs/ROADMAP.md`, `docs/IMPLEMENTATION_PLAN.md`,
  `docs/TEST_PLAN.md`, `docs/SAFETY.md`, `docs/DECISIONS.md`,
  `docs/BACKLOG.md`
- Create: `firmware/{app,boards,tests}/.gitkeep`,
  `electronics/{schematics,pcb,bom}/.gitkeep`, and
  `mechanical/{cad,prototypes,exports}/.gitkeep`

**Step 1: Write the documentation acceptance checklist**

Record confirmed requirements, assumptions, open questions, deferred ideas, and
acceptance criteria in the product documents.

**Step 2: Run the structure check to verify the initial failure**

Run: `bash tools/validate-repository-structure.sh`

Expected: FAIL because the validator and required project files do not yet exist.

**Step 3: Add the minimal documentation and placeholders**

Create only the requested documents and `.gitkeep` files needed to preserve
empty future-work directories. Do not add firmware or CAD placeholders.

**Step 4: Run the structure check**

Run: `bash tools/validate-repository-structure.sh`

Expected: PASS after Task 3 creates the validator and the required structure.

**Step 5: Commit**

```bash
git add README.md AGENTS.md docs firmware electronics mechanical
git commit -m "chore: bootstrap project documentation"
```

### Task 2: Record decisions, community process, and licence candidates

**Files:**

- Create: `docs/adr/0001-repository-structure.md` through
  `docs/adr/0007-licensing-strategy.md`
- Create: `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`, `SECURITY.md`,
  `LICENSES/README.md`, `.github/ISSUE_TEMPLATE/*.md`,
  `.github/pull_request_template.md`

**Step 1: Write ADRs using one template**

Each ADR must contain `Status`, `Context`, `Decision`, `Alternatives`,
`Consequences`, and `Follow-up work`.

**Step 2: Verify no final licence text or unsupported safety claim was added**

Run: `rg -n -i "certified|waterproof|road-legal|safe while riding" README.md docs LICENSES`

Expected: Matches occur only in warnings or explicit non-claims.

**Step 3: Add the governance and licence-candidate files**

Use the candidate matrix to defer final licence selection and keep contribution
and security policy proportional to an early-stage project.

**Step 4: Validate the repository**

Run: `bash tools/validate-repository-structure.sh`

Expected: PASS.

**Step 5: Commit**

```bash
git add docs/adr CONTRIBUTING.md CODE_OF_CONDUCT.md SECURITY.md LICENSES .github
git commit -m "chore: add project governance"
```

### Task 3: Add documentation CI and verify the full bootstrap

**Files:**

- Create: `tools/validate-repository-structure.sh`,
  `.github/workflows/docs.yml`

**Step 1: Write the failing validation cases**

The validator must fail for a missing required file, missing required directory,
or Markdown document without an H1 heading.

**Step 2: Manually check a controlled failure**

Run: `tmp=$(mktemp); mv docs/GOALS.md "$tmp"; bash tools/validate-repository-structure.sh; mv "$tmp" docs/GOALS.md`

Expected: FAIL and name `docs/GOALS.md`; restore the file immediately.

**Step 3: Implement the smallest portable validator and CI workflow**

Use shell and standard GitHub Actions checkout only; do not introduce a firmware
build system or a package manager for this documentation-only bootstrap.

**Step 4: Run all bootstrap checks**

Run: `bash tools/validate-repository-structure.sh && git diff --check && git status --short`

Expected: validator and whitespace check PASS; status lists only intended files.

**Step 5: Commit, push, and open a draft pull request when authorised**

```bash
git add .github tools .markdownlint.json
git commit -m "ci: validate documentation scaffold"
git push -u origin chore/bootstrap-tactile-ride
```

Create a draft pull request but do not merge it automatically.

## Execution handoff

This plan was executed directly because the repository request explicitly
authorised the complete bootstrap. For later plans, choose either a task-by-task
subagent-driven session or a separate execution session with checkpoints.
