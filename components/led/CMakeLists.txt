idf_component_register(
    SRCS            "led.c" "led_cycle.c"
    INCLUDE_DIRS    "."
    REQUIRES        espressif__led_strip
    PRIV_REQUIRES   helpers
)
