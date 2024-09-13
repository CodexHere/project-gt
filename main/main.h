#pragma once

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_err.h"

#include "logging.h"

#include "color.h"
#include "led.h"
#include "led_cycle.h"

// Overridden LED control values
#define LED_STRIP_DELAY_NEXT 1
#define LED_STRIP_OFFSET_NEXT 1

// Override LOG_FORMAT to reduce color-spew
#undef LOG_FORMAT
#define LOG_FORMAT(letter, format) LOG_COLOR_##letter #letter " (%" PRIu32 ") " LOG_RESET_COLOR "%s: " format "\n"
