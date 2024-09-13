#include "main.h"

#undef TAG
#define TAG "LED Drive Demo"

// Task defs...
void task_Cycle_LED(void *pvParameters);

void app_main(void)
{
    led_strip_handle_t led_strip = configure_led();

    // Clear Strip on start!
    ESP_ERROR_CHECK(led_strip_clear(led_strip));

    vTaskDelay(pdMS_TO_TICKS(500));

    xTaskCreate(task_Cycle_LED, "CycleLED", 1024 * 3, (void *)&led_strip, configMAX_PRIORITIES - 1, NULL);

    // task_Cycle_LED((void *)&led_strip);
}

void task_Cycle_LED(void *pvParameters)
{
    ESP_LOGI(TAG, "\n\nLED Rainbow Started!\n\n");

    led_strip_handle_t *led_strip_ptr = (led_strip_handle_t *)pvParameters;
    led_strip_handle_t led_strip = *led_strip_ptr;

    // Shorthand also works as above, but explicitly using `*led_strip_ptr` below will somehow
    // reference memory at a different address and incorrectly at some point....
    // led_strip_handle_t led_strip = *((led_strip_handle_t *)pvParameters);

    led_cycle(led_strip, LED_STRIP_LED_NUMBERS, LED_STRIP_DELAY_NEXT, LED_STRIP_OFFSET_NEXT);
}
