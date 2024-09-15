#pragma once

#include "color.h"
#include "esp_err.h"

#include "logging.h"

#include "led_strip.h"

/// @brief Configuration type for LED Cycle operation.
///
/// Hue is calculated as part of the Cycle operation.
typedef struct led_cycle_config_t
{
    led_strip_handle_t led_strip_h;
    uint16_t num_leds;
    uint16_t next_delay;
    uint16_t saturation;
    uint16_t value;
    uint16_t next_offset;
} led_cycle_config_t;

/// @brief Pointer handle to an LED Cycle Config
typedef led_cycle_config_t *led_cycle_config_handle_t;

// LED Cycle Default Configuration
#define LED_CYCLE_CONFIG_DEFAULT(led_strip_handle) \
    {                                              \
        .led_strip_h = led_strip_handle,           \
        .num_leds = 1,                             \
        .next_delay = 100,                         \
        .next_offset = 1,                          \
        .saturation = 100,                         \
        .value = 100,                              \
    }

/// @brief WARNING: INFINITE LOOP!
///
/// This will simply loop through RGB values based on the HSV scale.
/// The input config will control most of the limits between the
///
/// @param led_cycle_cfg Configuration for LED Cycle loop
void led_cycle(led_cycle_config_handle_t led_cycle_cfg);
