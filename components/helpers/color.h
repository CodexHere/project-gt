#pragma once

#include "freertos/FreeRTOS.h"

/// @brief Simple helper function, converting HSV color space to RGB color space
///
/// Wiki: https://en.wikipedia.org/wiki/HSL_and_HSV
void hsv_to_rgb(uint32_t hue, uint32_t saturation, uint32_t value, uint32_t *red, uint32_t *green, uint32_t *blue);
