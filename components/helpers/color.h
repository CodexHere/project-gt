#pragma once

#include "freertos/FreeRTOS.h"

void hsv_to_rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b);
