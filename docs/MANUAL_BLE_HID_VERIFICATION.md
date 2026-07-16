# Manual BLE HID Verification

## Scope and safety boundary

This procedure records a controlled, stationary bench check of the Phase 1 BLE
HID Consumer Control proof of concept. It is not a riding procedure, a safety
assessment, or evidence of compatibility with an Android device or media app
until observations are recorded. Keep the board, phone, and any test fixture
stationary throughout the procedure.

All result fields in this document are **pending**. Copy the checklist into a
test record and fill it with the actual board revision, firmware commit, phone
details, observations, logs, and failures. Do not replace a pending field with
an assumption based on a successful firmware build.

## Preflight record

Record these details before pairing:

| Field | Result |
| --- | --- |
| Date and tester | Pending |
| Board revision and bootloader method | Pending |
| Firmware Git commit and build configuration | Pending |
| Host operating system and Bluetooth adapter | Pending |
| Android phone model, Android version, and Bluetooth state | Pending |
| Media application and version | Pending |
| Power method and serial/debug log capture method | Pending |

## 1. Build the firmware

From the documented west workspace, build the reference target:

```bash
west build -s tactile-ride/firmware/app -b xiao_ble/nrf52840 \
  -d build/xiao_ble --pristine
```

If testing the development-only synthetic trigger, use the separate build
configuration below. It is not a substitute for physical controls:

```bash
west build -s tactile-ride/firmware/app -b xiao_ble/nrf52840 \
  -d build/xiao_ble_demo --pristine -- -DCONFIG_TACTILE_RIDE_DEV_AUTO_DEMO=y
```

Record the command, exit status, firmware commit, and generated artifact path.

## 2. Flash the board

Put the XIAO BLE into its stock UF2 bootloader mode, mount the volume, and copy
`build/xiao_ble/zephyr/zephyr.uf2` to its root. Use `west flash` only when an
external debug probe is connected and configured for the board. Record the
method, artifact checksum, serial/debug log start, and whether the board began
advertising.

Result: **Pending — no board has been flashed for this change.**

## 3. Pair with Android

With the phone and board stationary, open Android Bluetooth settings, scan for
the advertised TactileRide device, pair it, and accept any system prompt. Note
the device label, whether Android identifies an input device, pairing outcome,
and any security or bonding prompts. Then power-cycle or reset the board and
record whether it reconnects as expected.

Result: **Pending — Android pairing and reconnect behaviour have not been
observed.**

## 4. Test YouTube Music

After a successful, recorded pairing, open YouTube Music and test each action
from the table below while the phone remains stationary. Record the exact app
version, playback state, observed response, latency impression, and failures.
Do not claim YouTube Music support if this step has not been run.

Result: **Pending — no YouTube Music result is recorded.**

## 5. Test another media application

Repeat the action table with a second Android media application. Record the app
and version, any different behavior, and whether the application was foreground
or backgrounded. This comparison is required because Consumer Control handling
is host and application dependent.

Result: **Pending — no second media-application result is recorded.**

## 6. Test the locked screen

Lock the stationary phone after starting playback, then test the same actions.
Record whether Android allows each action and any display, security, or
background behavior. Do not unlock or operate the phone while riding; this is a
controlled bench observation only.

Result: **Pending — locked-screen behavior has not been observed.**

## 7. Record each Consumer Control action

For each row, perform a press and release. The development-only automatic demo
may be used to observe report flow, but it does not demonstrate a physical
button. The expected HID intent is not an actual host result.

| Action | Consumer usage | Expected HID intent | Android/media observation | Pass/fail or note |
| --- | --- | --- | --- | --- |
| Volume up | `0xE9` | Increase volume once, then release | Pending | Pending |
| Volume down | `0xEA` | Decrease volume once, then release | Pending | Pending |
| Play/pause | `0xCD` | Toggle playback once, then release | Pending | Pending |
| Next track | `0xB5` | Advance track once, then release | Pending | Pending |
| Previous track | `0xB6` | Go to previous track once, then release | Pending | Pending |

For a held volume action, record the observed repeat cadence. The firmware caps
repeat at four actions per second by default; that setting is a design limit,
not proof of host-visible behavior.

## 8. Remove the bond and pair again

First use Android Bluetooth settings to forget the TactileRide device, then
repeat the pairing and reconnection steps. The current firmware API intentionally
does **not** expose a device-side bond-reset trigger; it returns `-ENOTSUP`
until a safe, reviewed mechanism exists. Record the Android-side forget result
and leave device-side clearing marked pending rather than claiming it occurred.

Result: **Pending — no bond removal or second-pairing result is recorded.**

## 9. Capture failures and disconnect handling

During all tests, record advertising start, connect, disconnect, re-advertising,
bonding, notification-subscription, and dropped-action log messages. For each
failure, preserve the raw log and record the preceding action, phone state,
application state, board power state, and recovery attempt.

| Failure or unexpected observation | Reproduction steps | Log/artifact location | Recovery attempt | Outcome |
| --- | --- | --- | --- | --- |
| Pending | Pending | Pending | Pending | Pending |

## Completion record

Manual verification is complete only when the preflight record, all five action
observations, a disconnect/reconnect observation, and any failures are attached
to a dated test artifact. Until then, the firmware remains a build-validated
proof of concept with no Android or media-application compatibility claim.
