cmake_minimum_required(VERSION 3.16)

include(DisableLogging.cmake)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

include_directories(includes)

project(main)
