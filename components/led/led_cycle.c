#include "led_cycle.h"

#define TAG "LED Cycler"

void led_cycle(led_strip_handle_t led_strip, uint16_t num_leds, uint16_t next_delay, uint16_t offset)
{
    uint32_t red, green, blue;
    uint16_t hue, start_rgb;
    start_rgb = red = green = blue = 0;

    for (;;)
    {
        for (int currLed = 0; currLed < num_leds; currLed++)
        {
            // Build RGB pixels
            hue = currLed * 360 / num_leds + start_rgb;
            hsv_to_rgb(hue, 100, 20, &red, &green, &blue);

            ESP_LOGI(TAG, "\033[48;2;%lu;%lu;%lum\033[38;2;255;255;255m           R: %3lu, G: %3lu, B: %3lu           %s", red, green, blue, red, green, blue, LOG_RESET_COLOR);

            // Pointer logic failing mid-loop? Must be a task thing? For some reason `*led_strip_ptr` is
            // only the right value twice, then never again. Meanwhile if I store it as in `led_strip`, it
            // sticks around the entire loop. I'm thinking this is a cleanup thing from the injected value,
            // and the compiler is optimizing something about the pointer still pointing to the original "copy".
            // Strange, honestly...
            // ESP_LOGI(TAG, "Pointers: %p, %p, %p, %p ---- ", led_strip_ptr, *led_strip_ptr, led_strip, &led_strip);

            // Set Pixel Color
            ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, currLed, red, green, blue));
            // Refresh the strip to send data
            ESP_ERROR_CHECK(led_strip_refresh(led_strip));

            // Minor delay until next update
            vTaskDelay(pdMS_TO_TICKS(next_delay));
        }

        start_rgb += offset;
    }
}