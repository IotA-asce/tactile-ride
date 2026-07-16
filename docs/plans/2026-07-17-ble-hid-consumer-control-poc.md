# BLE HID Consumer Control Proof of Concept Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Build a Zephyr-based, desktop and bench-only BLE HID Consumer Control
proof of concept that can send five media actions without a mobile application.

**Architecture:** Keep raw input acquisition, deterministic debounce/repeat
logic, logical actions, Consumer Page report construction, BLE connection state,
and HID transport as separate layers. The XIAO BLE is one documented reference
target; no GPIO assignment, PCB, enclosure, battery, or vehicle work is part of
this increment.

**Tech Stack:** Zephyr v4.4.0 at `684c9e8f32e4373a21098559f748f06915f950c9`,
Zephyr SDK 1.0.1, west 1.5.0, C, ztest/twister, GitHub Actions.

---

### Task 1: Record Phase 1 decisions and reproducible workspace

**Files:**

- Create: `west.yml`, `docs/plans/2026-07-17-ble-hid-consumer-control-poc.md`
- Modify: `docs/adr/0004-firmware-framework-evaluation.md`,
  `docs/adr/0005-development-board-selection-criteria.md`,
  `docs/DECISIONS.md`, `README.md`, `docs/ARCHITECTURE.md`,
  `docs/IMPLEMENTATION_PLAN.md`, `docs/TEST_PLAN.md`, `docs/ROADMAP.md`,
  `docs/BACKLOG.md`

**Step 1: Record the reference target and framework decision**

Set Zephyr v4.4.0 and its immutable commit as the Phase 1 framework. Select
`xiao_ble/nrf52840` as a reference target only and retain other board options
for later evidence-based decisions.

**Step 2: Verify the manifest revision before writing firmware**

Run: `git -C /tmp/tactile-ride-zephyr-v4.4.0 rev-parse HEAD`

Expected: `684c9e8f32e4373a21098559f748f06915f950c9`.

**Step 3: Add the manifest and document the decisions**

```yaml
projects:
  - name: zephyr
    revision: 684c9e8f32e4373a21098559f748f06915f950c9
    import: true
```

**Step 4: Validate documentation syntax**

Run: `bash tools/validate-repository-structure.sh && git diff --check`

Expected: PASS.

**Step 5: Commit**

```bash
git add west.yml docs README.md
git commit -m "docs: record phase one firmware decisions"
```

### Task 2: Write hardware-independent failing tests for input and reports

**Files:**

- Create: `firmware/tests/logic/CMakeLists.txt`, `firmware/tests/logic/prj.conf`,
  `firmware/tests/logic/testcase.yaml`, `firmware/tests/logic/src/main.c`
- Create: `firmware/app/include/tactile_ride/media_action.h`,
  `consumer_report.h`, `button_logic.h`, `media_controller.h`
- Create: `firmware/app/src/consumer_report.c`, `button_logic.c`,
  `media_controller.c`

**Step 1: Write the failing test cases**

```c
ZTEST(tactile_ride_logic, test_volume_press_then_release)
{
    struct media_controller controller = make_connected_controller();

    zassert_ok(media_controller_trigger(&controller, MEDIA_ACTION_VOLUME_UP));
    zassert_equal(sent_reports[0], CONSUMER_REPORT_VOLUME_UP);
    zassert_equal(sent_reports[1], CONSUMER_REPORT_RELEASE);
}
```

Include debounce, short bounce rejection, held volume repeat, non-volume
non-repeat, Consumer usage bit mapping, zero release report, and disconnected
behaviour.

**Step 2: Run the logic suite to verify it fails**

Run: `west twister -T firmware/tests/logic -p native_sim --inline-logs`

Expected: FAIL before the source modules exist.

**Step 3: Add the smallest deterministic logic implementation**

```c
uint8_t consumer_report_press(enum media_action action)
{
    return BIT(action);
}
```

Replace the illustrative `BIT(action)` mapping with explicit Consumer Page bit
constants so the HID report layout is stable.

**Step 4: Run the logic suite**

Run: `west twister -T firmware/tests/logic -p native_sim --inline-logs`

Expected: PASS.

**Step 5: Commit**

```bash
git add firmware/app/include firmware/app/src/consumer_report.c \
  firmware/app/src/button_logic.c firmware/app/src/media_controller.c \
  firmware/tests/logic
git commit -m "feat: add media control logic tests"
```

### Task 3: Integrate the BLE HID application

**Files:**

- Create: `firmware/app/CMakeLists.txt`, `firmware/app/Kconfig`,
  `firmware/app/prj.conf`, `firmware/app/src/main.c`,
  `firmware/app/src/hid_service.c`, `firmware/app/src/ble_connection.c`,
  `firmware/app/src/button_input.c`, `firmware/app/src/power_policy.c`
- Create: `firmware/app/include/tactile_ride/hid_service.h`,
  `ble_connection.h`, `button_input.h`, `power_policy.h`
- Create: `firmware/boards/README.md`
- Delete: `firmware/app/.gitkeep`, `firmware/boards/.gitkeep`,
  `firmware/tests/.gitkeep`

**Step 1: Verify the Consumer Page report descriptor design**

Use report ID 1 and a one-byte input report whose first five bits are Volume
Increment (0xE9), Volume Decrement (0xEA), Play/Pause (0xCD), Scan Next Track
(0xB5), and Scan Previous Track (0xB6). The remaining three bits are constant.

**Step 2: Integrate the GATT HID service and connection state**

Base the service shape on Zephyr's official `peripheral_hids` sample, but use
the custom Consumer Page map. Send the action byte, then an all-zero byte, for
each command. Enable bonded settings persistence and restart advertising after a
disconnect.

**Step 3: Add the board-independent input pipeline**

The input interface sends logical action and raw pressed state to the
orchestrator. A development-only auto-demo can exercise the full input path;
physical GPIO is intentionally unconfigured until a documented switch design
exists.

**Step 4: Build the reference target**

Run: `west build -s firmware/app -b xiao_ble/nrf52840 -d build/xiao_ble --pristine`

Expected: PASS with no warning-as-error policy.

**Step 5: Commit**

```bash
git add firmware/app firmware/boards
git commit -m "feat: add zephyr consumer control peripheral"
```

### Task 4: Document verification and add CI

**Files:**

- Create: `docs/MANUAL_BLE_HID_VERIFICATION.md`, `.github/workflows/firmware.yml`
- Modify: `firmware/app/README.md`, `tools/validate-repository-structure.sh`,
  `README.md`, `docs/ARCHITECTURE.md`, `docs/IMPLEMENTATION_PLAN.md`,
  `docs/TEST_PLAN.md`, `docs/ROADMAP.md`, `docs/BACKLOG.md`

**Step 1: Document exact build, flash, test, and Android bench procedures**

Mark Android, YouTube Music, locked-screen, reconnection, and bond-reset checks
as pending until actual test evidence is committed.

**Step 2: Add transparent CI setup**

Install pinned west, initialise the local manifest, update dependencies, install
only `arm-zephyr-eabi` from Zephyr SDK 1.0.1, build the XIAO target, and run the
native logic test. Cache the dependency workspace and SDK using the manifest
hash as part of the key.

**Step 3: Run all available validation**

Run: `bash tools/validate-repository-structure.sh && git diff --check && west
twister -T firmware/tests/logic -p native_sim --inline-logs && west build -s
firmware/app -b xiao_ble/nrf52840 -d build/xiao_ble --pristine`

Expected: all available local checks PASS.

**Step 4: Commit, push, and open a draft PR**

```bash
git add README.md docs .github tools firmware
git commit -m "ci: verify zephyr proof of concept"
git push -u origin feat/ble-hid-consumer-control-poc
```

Open a draft pull request and do not merge it automatically.

## Execution handoff

This plan is being executed directly because the request explicitly authorises
the complete Phase 1 proof of concept. Later work should use a separate,
evidence-based task plan before adding physical controls, power hardware, or
mechanical artifacts.
