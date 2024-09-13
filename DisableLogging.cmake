option(KILL_LOGGING "Disable logging" OFF)

# Add the preprocessor definition
if(KILL_LOGGING)
    message(STATUS "Logging disabled using KILL_LOGGING")
    add_definitions(-DKILL_LOGGING)
else()
    message(STATUS "Logging enabled")
endif()