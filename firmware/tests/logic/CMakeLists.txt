# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(tactile_ride_logic)

target_sources(app PRIVATE
  src/main.c
  ${CMAKE_CURRENT_LIST_DIR}/../../app/src/button_logic.c
  ${CMAKE_CURRENT_LIST_DIR}/../../app/src/consumer_report.c
  ${CMAKE_CURRENT_LIST_DIR}/../../app/src/media_controller.c
)

target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../../app/include
)
