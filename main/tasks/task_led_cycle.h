#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "config.h"
#include "logging.h"

#include "led.h"
#include "led_cycle.h"

#ifndef TAG
#define TAG "Task - LED Cycler"
#endif

void start_task_led_cycle(led_strip_handle_t led_strip_handle);
