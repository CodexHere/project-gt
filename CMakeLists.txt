# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

if(DEFINED ENV{KILL_LOGGING})
  set(MY_ENV_VAR $ENV{KILL_LOGGING})
  add_definitions(-DMY_DEFINE_VALUE=${MY_ENV_VAR})
else()
  message(STATUS "Use KILL_LOGGING env var to disable logging functionality (speeds up runtime)")
endif()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(main)
