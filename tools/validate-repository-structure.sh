#!/usr/bin/env bash

# Validate the documentation-first scaffold without requiring a firmware toolchain
# or third-party package installation. External links are intentionally excluded:
# availability and redirects are not reliable in local or CI environments.
set -euo pipefail

repository_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$repository_root"

status=0

fail() {
  printf 'ERROR: %s\n' "$*" >&2
  status=1
}

required_directories=(
  .github
  .github/ISSUE_TEMPLATE
  docs
  docs/adr
  firmware
  firmware/app
  firmware/boards
  firmware/tests
  electronics
  electronics/schematics
  electronics/pcb
  electronics/bom
  mechanical
  mechanical/cad
  mechanical/prototypes
  mechanical/exports
  tools
  LICENSES
)

required_files=(
  README.md
  AGENTS.md
  CONTRIBUTING.md
  CODE_OF_CONDUCT.md
  SECURITY.md
  LICENSES/README.md
  docs/PRD.md
  docs/GOALS.md
  docs/REQUIREMENTS.md
  docs/ARCHITECTURE.md
  docs/BACKLOG.md
  docs/ROADMAP.md
  docs/IMPLEMENTATION_PLAN.md
  docs/TEST_PLAN.md
  docs/SAFETY.md
  docs/DECISIONS.md
  docs/adr/0001-repository-structure.md
  docs/adr/0002-ble-hid-consumer-control.md
  docs/adr/0003-no-mandatory-mobile-app.md
  docs/adr/0004-firmware-framework-evaluation.md
  docs/adr/0005-development-board-selection-criteria.md
  docs/adr/0006-battery-powered-prototype.md
  docs/adr/0007-licensing-strategy.md
  .github/ISSUE_TEMPLATE/bug_report.md
  .github/ISSUE_TEMPLATE/feature_request.md
  .github/ISSUE_TEMPLATE/hardware_test_report.md
  .github/ISSUE_TEMPLATE/design_proposal.md
  .github/pull_request_template.md
  firmware/app/.gitkeep
  firmware/boards/.gitkeep
  firmware/tests/.gitkeep
  electronics/schematics/.gitkeep
  electronics/pcb/.gitkeep
  electronics/bom/.gitkeep
  mechanical/cad/.gitkeep
  mechanical/prototypes/.gitkeep
  mechanical/exports/.gitkeep
)

for directory in "${required_directories[@]}"; do
  [[ -d "$directory" ]] || fail "missing required directory: $directory"
done

for file in "${required_files[@]}"; do
  [[ -f "$file" ]] || fail "missing required file: $file"
done

markdown_files=(README.md AGENTS.md CONTRIBUTING.md CODE_OF_CONDUCT.md SECURITY.md LICENSES/README.md)
while IFS= read -r -d '' markdown_file; do
  markdown_files+=("$markdown_file")
done < <(find docs -type f -name '*.md' -print0)

for markdown_file in "${markdown_files[@]}"; do
  grep -q '^# ' "$markdown_file" || fail "missing H1 heading: $markdown_file"

  if grep -nE '[[:blank:]]+$' "$markdown_file"; then
    fail "trailing whitespace: $markdown_file"
  fi

  while IFS= read -r target; do
    target="${target%%#*}"
    case "$target" in
      '' | http://* | https://* | mailto:*)
        continue
        ;;
    esac

    if [[ "$target" == /* ]]; then
      destination="$repository_root$target"
    else
      destination="$(dirname "$markdown_file")/$target"
    fi

    [[ -e "$destination" ]] || fail "broken local link in $markdown_file: $target"
  done < <(grep -oE '\]\([^)]+' "$markdown_file" | cut -c3- || true)
done

if [[ "$status" -ne 0 ]]; then
  exit "$status"
fi

printf 'Repository structure and documentation validation passed.\n'
