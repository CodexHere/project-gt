#ifdef KILL_LOGGING
#undef ESP_LOG_LEVEL
#define ESP_LOG_LEVEL(tag, format, ...) (void)0
#endif
