# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(tactile_ride_ble_hid_poc)

target_sources(app PRIVATE
  src/main.c
  src/ble_connection.c
  src/button_input.c
  src/button_logic.c
  src/consumer_report.c
  src/hid_service.c
  src/media_controller.c
  src/power_policy.c
)

target_include_directories(app PRIVATE include)
