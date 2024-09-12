#include "main.h"

#define LED_STRIP_BLINK_GPIO GPIO_NUM_48
#define LED_STRIP_LED_NUMBERS 1
#define LED_STRIP_DELAY_NEXT 10
#define LED_STRIP_OFFSET_NEXT 1

// 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ (10 * 1000 * 1000)

static const char *TAG = "LED Driver";

// static QueueHandle_t qh_strip = NULL;

// Task defs...
static void task_Cycle_LED(void *pvParameters);

void app_main(void)
{
    // qh_strip = xQueueCreate(1, sizeof(led_strip_handle_t));

    led_strip_handle_t led_strip = configure_led();

    // Clear Strip on start!
    ESP_ERROR_CHECK(led_strip_clear(led_strip));

    vTaskDelay(pdMS_TO_TICKS(1000));

    xTaskCreate(task_Cycle_LED, "CycleLED", configMINIMAL_STACK_SIZE, (void *)&led_strip, configMAX_PRIORITIES - 1, NULL);
}

static void task_Cycle_LED(void *pvParameters)
{
    uint32_t red = 0;
    uint32_t green = 0;
    uint32_t blue = 0;
    uint16_t hue = 0;
    uint16_t start_rgb = 0;

    ESP_LOGI(TAG, "\n\nLED Rainbow Started!\n\n");

    led_strip_handle_t *led_strip_ptr = (led_strip_handle_t *)pvParameters;
    led_strip_handle_t led_strip = *led_strip_ptr;

    // led_strip_handle_t led_strip = *((led_strip_handle_t *)pvParameters);

    for (;;)
    {
        for (int currLed = 0; currLed < LED_STRIP_LED_NUMBERS; currLed++)
        {
            // Build RGB pixels
            hue = currLed * 360 / LED_STRIP_LED_NUMBERS + start_rgb;
            led_strip_hsv2rgb(hue, 100, 20, &red, &green, &blue);

            ESP_LOGI(TAG, "\033[48;2;%lu;%lu;%lum\033[38;2;255;255;255m           R: %3lu, G: %3lu, B: %3lu           %s", red, green, blue, red, green, blue, LOG_RESET_COLOR);

            ESP_LOGI(TAG, "Pointers: %p, %p, %p, %p ---- ", led_strip_ptr, *led_strip_ptr, led_strip, &led_strip);

            // Set Pixel Color
            ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, currLed, red, green, blue));
            // Refresh the strip to send data
            ESP_ERROR_CHECK(led_strip_refresh(led_strip));

            fflush(stdout);

            // Minor delay until next update
            vTaskDelay(pdMS_TO_TICKS(LED_STRIP_DELAY_NEXT));
        }

        start_rgb += LED_STRIP_OFFSET_NEXT;
    }
}

led_strip_handle_t configure_led()
{
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_BLINK_GPIO,   // The GPIO that connected to the LED strip's data line
        .max_leds = LED_STRIP_LED_NUMBERS,        // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812,            // LED strip model
        .flags.invert_out = false,                // whether to invert the output signal
    };

    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .flags.with_dma = false,               // DMA feature is available on ESP target like ESP32-S3
    };

    // LED Strip object handle
    led_strip_handle_t led_strip;

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    ESP_LOGI(TAG, "Created LED strip object with RMT backend");

    return led_strip;
}
