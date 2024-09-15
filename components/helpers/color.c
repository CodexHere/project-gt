#include "color.h"

void hsv_to_rgb(uint32_t hue, uint32_t saturation, uint32_t value, uint32_t *red, uint32_t *green, uint32_t *blue)
{
  hue %= 360; // hue -> [0,360]
  uint32_t rgb_max = value * 2.55f;
  uint32_t rgb_min = rgb_max * (100 - saturation) / 100.0f;

  uint32_t i = hue / 60;
  uint32_t diff = hue % 60;

  // RGB adjustment amount by hue
  uint32_t rgb_adj = (rgb_max - rgb_min) * diff / 60;

  switch (i)
  {
  case 0:
    *red = rgb_max;
    *green = rgb_min + rgb_adj;
    *blue = rgb_min;
    break;
  case 1:
    *red = rgb_max - rgb_adj;
    *green = rgb_max;
    *blue = rgb_min;
    break;
  case 2:
    *red = rgb_min;
    *green = rgb_max;
    *blue = rgb_min + rgb_adj;
    break;
  case 3:
    *red = rgb_min;
    *green = rgb_max - rgb_adj;
    *blue = rgb_max;
    break;
  case 4:
    *red = rgb_min + rgb_adj;
    *green = rgb_min;
    *blue = rgb_max;
    break;
  default:
    *red = rgb_max;
    *green = rgb_min;
    *blue = rgb_max - rgb_adj;
    break;
  }
}
