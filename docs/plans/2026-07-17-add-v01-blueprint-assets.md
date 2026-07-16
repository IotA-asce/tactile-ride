# V0.1 Blueprint Assets Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Preserve the supplied V0.1 blueprint sources in clear repository homes while keeping the static/bench-only status and unresolved hardware claims explicit.

**Architecture:** Store editable mechanical and electronics artifacts under their existing discipline folders, and use a blueprint index as the single provenance and safety boundary. Link that index from repository documentation without treating its draft wiring, dimensions, or concept imagery as firmware configuration or validated product behavior.

**Tech Stack:** Markdown, CSV, SVG, OpenSCAD, Bash repository validation.

---

### Task 1: Add an indexed V0.1 blueprint record

**Files:**
- Create: `docs/blueprints/v0.1/README.md`
- Create: `docs/blueprints/v0.1/TactileRide_V0.1_Control_Coordinates.csv`
- Create: `docs/blueprints/v0.1/TactileRide_V0.1_Front_Panel.svg`
- Modify: `README.md`

**Step 1: Write the asset-status contract**

State the source location, V0.1 scope, links to the canonical copied artifacts,
and the reasons the concept PNG and duplicate ZIP are not tracked.

**Step 2: Copy the documentation-facing source artifacts**

Preserve their filenames and record that the PDF and ZIP are source-pack
snapshots, while the CSV and SVG remain version-controlled editable sources.

**Step 3: Link the blueprint index from the repository overview**

Use language that limits it to a stationary ergonomic mock-up and bench
prototype reference.

**Step 4: Validate links**

Run: `bash tools/validate-repository-structure.sh`

Expected: `Repository structure and documentation validation passed.`

**Step 5: Commit**

```bash
git add docs/blueprints README.md
git commit -m "docs: add v0.1 blueprint reference"
```

### Task 2: Add provisional mechanical and electronics sources

**Files:**
- Create: `mechanical/prototypes/v0.1/TactileRide_V0.1_Reference_Model.scad`
- Create: `electronics/prototypes/v0.1/TactileRide_V0.1_Wiring.svg`
- Create: `electronics/bom/v0.1/TactileRide_V0.1_Provisional_BOM.csv`
- Create: `mechanical/prototypes/v0.1/README.md`
- Create: `electronics/prototypes/v0.1/README.md`

**Step 1: Copy only editable or directly useful sources**

Keep the OpenSCAD source, SVG wiring reference, and CSV BOM. Do not track the
generated STL because it can be regenerated from the SCAD source and is not a
validated printable release.

**Step 2: Add scope guards beside the sources**

Explain that the dimensions, switch/BOM choices, and wiring map are provisional;
the wiring map does not assign firmware GPIOs and the current firmware exposes
no device-side pairing-reset action.

**Step 3: Validate that the source tree has no accidental production claim**

Run: `rg -n "road-ready|certified|IPX|weather resistant" docs/blueprints electronics/prototypes mechanical/prototypes`

Expected: only the explicit negated/provisional wording, if any.

**Step 4: Commit**

```bash
git add mechanical electronics
git commit -m "docs: add provisional v0.1 prototype sources"
```

### Task 3: Make the blueprint discoverable without changing project scope

**Files:**
- Modify: `README.md`
- Modify: `tools/validate-repository-structure.sh`

**Step 1: Add traceable references**

Link the blueprint index from the repository overview without making it a
completed hardware design or changing a project-plan status.

**Step 2: Capture the conflicts and measurements required**

Record the missing physical measurements and the mismatch between the supplied
wiring/reset suggestion and an adopted firmware scope in the blueprint index.

**Step 3: Require the asset index in the structure validator**

Add the blueprint index and its canonical editable sources to `required_files`.

**Step 4: Run final validation**

Run: `bash tools/validate-repository-structure.sh && git diff --check`

Expected: structure validation passes with no whitespace errors.

**Step 5: Commit**

```bash
git add README.md docs tools
git commit -m "docs: trace v0.1 blueprint assumptions"
```

### Task 4: Publish the reviewed asset integration

**Files:**
- Modify: all staged V0.1 asset and documentation files above

**Step 1: Inspect staged file list and provenance**

Run: `git diff --cached --stat && git status --short`

Expected: no duplicate ZIP, concept PNG, or generated STL is staged.

**Step 2: Re-run relevant validation**

Run: `bash tools/validate-repository-structure.sh && git diff --check`

Expected: both commands succeed.

**Step 3: Push and open a draft PR**

Run: `git push -u origin feat/add-v01-blueprint-assets`

Expected: branch tracks `origin/feat/add-v01-blueprint-assets`.

**Step 4: Report exclusions and unresolved scope**

List the ignored concept image, duplicate archive, generated STL, unvalidated
wiring/pairing-reset notes, and all bench/static-test work still required.
