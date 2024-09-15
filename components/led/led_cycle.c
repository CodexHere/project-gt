#include "led_cycle.h"

#ifndef TAG
#define TAG "LED Cycler"
#endif

void led_cycle(led_cycle_config_handle_t led_cycle_cfg)
{
    uint32_t red, green, blue;
    uint16_t hue, start_rgb;
    start_rgb = red = green = blue = 0;

    for (;;)
    {
        for (int currLed = 0; currLed < led_cycle_cfg->num_leds; currLed++)
        {
            // Build RGB pixels
            hue = currLed * 360 / led_cycle_cfg->num_leds + start_rgb;
            hsv_to_rgb(
                hue,
                led_cycle_cfg->saturation,
                led_cycle_cfg->value,
                &red,
                &green,
                &blue);

            // Output colorful log
            ESP_LOGI(TAG, "\033[48;2;%lu;%lu;%lum\033[38;2;255;255;255m           R: %3lu, G: %3lu, B: %3lu           %s", red, green, blue, red, green, blue, LOG_RESET_COLOR);

            // Set Pixel Color
            ESP_ERROR_CHECK(led_strip_set_pixel(led_cycle_cfg->led_strip_h, currLed, red, green, blue));
            // Refresh the strip to send data
            ESP_ERROR_CHECK(led_strip_refresh(led_cycle_cfg->led_strip_h));

            // Minor delay until next update
            vTaskDelay(pdMS_TO_TICKS(led_cycle_cfg->next_delay));
        }

        start_rgb += led_cycle_cfg->next_offset;
    }
}
