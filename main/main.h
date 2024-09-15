#pragma once

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"

#include "logging.h"

#include "config.h"

// Tasks
#include "tasks/task_led_cycle.h"

// Override LOG_FORMAT to reduce color-spew
#undef LOG_FORMAT
#define LOG_FORMAT(letter, format) LOG_COLOR_##letter #letter " (%" PRIu32 ") " LOG_RESET_COLOR "%s: " format "\n"

#undef TAG
#define TAG "LED Drive Demo"

void start_tasks();
