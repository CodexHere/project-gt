idf_component_register(
    INCLUDE_DIRS    "."
    REQUIRES        espressif__led_strip
    PRIV_REQUIRES   helpers
    SRCS            "led.c" "led_cycle.c"
)
