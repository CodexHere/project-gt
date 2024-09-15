#include "task_led_cycle.h"

void task_led_cycle(void *pvParameters)
{
  ESP_LOGI(TAG, "\n\nLED Rainbow Started!\n\n");

  // Cast our pointer to the type we expect
  led_cycle_config_handle_t led_cycle_config = (led_cycle_config_handle_t)pvParameters;

  ESP_LOGI(TAG, "Task Starting: LED Cycle");
  ESP_LOGI(TAG, "\t- led_cycle_config->next_delay\t%d", led_cycle_config->next_delay);
  ESP_LOGI(TAG, "\t- led_cycle_config->next_offset\t%d", led_cycle_config->next_offset);
  ESP_LOGI(TAG, "\t- led_cycle_config->value\t%d", led_cycle_config->value);

  // Kick off loop!
  led_cycle(led_cycle_config);
}

void start_task_led_cycle(led_strip_handle_t led_strip_handle)
{
  // Build our LED Cycle Config struct
  led_cycle_config_handle_t led_cycle_config_handle = malloc(sizeof(led_cycle_config_t));

  *led_cycle_config_handle = (led_cycle_config_t){
      .led_strip_h = led_strip_handle,
      .num_leds = 1,
      .next_delay = LED_CYCLE_DELAY_NEXT,
      .next_offset = LED_CYCLE_OFFSET_NEXT,
      .saturation = 100,
      .value = LED_CYCLE_HSV_VALUE,
  };

  task_led_cycle((void *)led_cycle_config_handle);
}
