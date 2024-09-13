#pragma once

#include "color.h"
#include "esp_log.h"
#include "esp_err.h"

#include "logging.h"

#include "led_strip.h"

void led_cycle(led_strip_handle_t led_strip, uint16_t num_leds, uint16_t next_delay, uint16_t offset);
