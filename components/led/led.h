#pragma once

#include "esp_log.h"

#include "logging.h"

#include "led_strip.h"

#ifndef TAG
#define TAG "LED Configurer"
#endif
#ifndef LED_STRIP_BLINK_GPIO
#define LED_STRIP_BLINK_GPIO 48
#endif
#ifndef LED_STRIP_LED_NUMBERS
#define LED_STRIP_LED_NUMBERS 1
#endif
#ifndef LED_STRIP_RMT_RES_HZ
// 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ (10 * 1000 * 1000)
#endif

led_strip_handle_t configure_led();
