# TactileRide Phase 1 Firmware

## Scope

This Zephyr application is a desktop and bench BLE HID Consumer Control proof
of concept. It targets five standard Consumer Page actions and has no companion
application. It is not a production firmware release, physical-control design,
or road-use artifact.

## Pinned environment

| Component | Required version |
| --- | --- |
| Zephyr | v4.4.0, commit `684c9e8f32e4373a21098559f748f06915f950c9` |
| Zephyr SDK | 1.0.1 |
| west | 1.5.0 |
| CMake and Ninja | Host-supported versions required by Zephyr v4.4.0 |
| Python | A version supported by Zephyr v4.4.0 and its requirements file |

`west.yml` pins the Zephyr commit and imports its pinned module revisions.

## Workspace setup

Create a workspace **outside** the repository checkout so west modules and the
SDK do not pollute the Git worktree. Replace `<workspace>` with an absolute path.

```bash
mkdir -p <workspace>
cd <workspace>
git clone https://github.com/IotA-asce/tactile-ride.git tactile-ride
python3 -m venv .venv
. .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install west==1.5.0
west init -l tactile-ride
west update
west zephyr-export
python -m pip install -r zephyr/scripts/requirements.txt
cd zephyr
west sdk install -d ../zephyr-sdk-1.0.1 -t arm-zephyr-eabi
cd ..
export ZEPHYR_SDK_INSTALL_DIR="$(pwd)/zephyr-sdk-1.0.1"
```

To reproduce a pull request before it merges, check out its branch in
`tactile-ride` before running `west init -l tactile-ride`.

## Supported board targets

| Target | Role | Status |
| --- | --- | --- |
| `xiao_ble/nrf52840` | Seeed Studio XIAO BLE Phase 1 reference target | Built in CI |
| `xiao_ble/nrf52840/sense` | Optional XIAO BLE Sense Zephyr variant | Not built or tested by this project |
| `native_sim` | Host target for hardware-independent logic tests | Run in Linux CI |

The XIAO target is a reference board only. There are intentionally no control
GPIO assignments or switch overlays in this phase.

## Build

From `<workspace>` after setup:

```bash
west build -s tactile-ride/firmware/app -b xiao_ble/nrf52840 \
  -d build/xiao_ble --pristine
```

## Flash

The XIAO BLE's stock bootloader supports UF2. Put the board in bootloader mode
as documented by Seeed/Zephyr, mount it on the host, then copy:

```text
<workspace>/build/xiao_ble/zephyr/zephyr.uf2
```

to the root of that mounted volume. `west flash` requires a separately connected
and configured external debug probe for this board; it is not assumed to work
through the stock UF2 bootloader.

## Tests

Run the hardware-independent suite from `<workspace>`:

```bash
west twister -T tactile-ride/firmware/tests/logic -p native_sim --inline-logs
```

The `native_sim` test run is executed in Linux CI. On hosts where Zephyr cannot
run native unit tests, use the CI result and do not claim a local test pass.

## Configuration points

- `CONFIG_TACTILE_RIDE_DEBOUNCE_MS` controls stable input qualification.
- `CONFIG_TACTILE_RIDE_VOLUME_REPEAT_DELAY_MS` controls the delay before a held
  volume action repeats.
- `CONFIG_TACTILE_RIDE_VOLUME_REPEAT_INTERVAL_MS` defaults to a conservative
  four actions per second maximum rate.
- `CONFIG_TACTILE_RIDE_DEV_AUTO_DEMO=y` enables an explicitly development-only
  synthetic input sequence; it is disabled by default.

Example development-only build:

```bash
west build -s tactile-ride/firmware/app -b xiao_ble/nrf52840 \
  -d build/xiao_ble_demo --pristine -- -DCONFIG_TACTILE_RIDE_DEV_AUTO_DEMO=y
```

## Known limitations

- Physical buttons and GPIO assignments are intentionally unconfigured.
- Pairing reset is exposed only as a documented interface stub; no safe runtime
  trigger exists yet.
- Android, YouTube Music, locked-screen, flash, bond-reset, reconnect, and
  physical-control tests are pending recorded bench evidence.
- This firmware does not support motorcycle power, vehicle wiring, a PCB,
  enclosure, weather resistance, certification, or road use.

## Troubleshooting

- Run `west boards | grep xiao_ble` in the pinned workspace if the board target
  is not recognised.
- Run `west sdk list` from the `zephyr` directory if the compiler is not found.
- Rebuild with `--pristine` after changing Kconfig values or the Zephyr revision.
- Capture serial or debug-probe logs with the board, firmware revision, host OS,
  and phone/OS details before filing a hardware test report.
