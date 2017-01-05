#ifndef led_h
#define led_h

#include <stdbool.h>
#include <stdint.h>

int led_init();

int add_led_to_list_with_brightness(int row, char column, uint8_t brightness);
void clear_led_list();

int led_apply_values_to_driver();
#endif
