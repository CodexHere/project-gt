#include "main.h"

void app_main(void)
{
  // ! FIXME: Convert to task that gates the entire app first! (remove include)
  // ! Consider a lifecycle for the app... Bootstrapping, then start.
  led_strip_handle_t led_strip_handle = led_strip_configure();

  // Clear Strip on start!
  ESP_ERROR_CHECK(led_strip_clear(led_strip_handle));

  vTaskDelay(pdMS_TO_TICKS(500));

  start_tasks(led_strip_handle);
}

void start_tasks(led_strip_handle_t led_strip_handle)
{
  start_task_led_cycle(led_strip_handle);
}
