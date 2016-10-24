#ifndef led_h
#define led_h

#include <stdbool.h>

// turn on/off : true for on , false for off
int led_turn_on_off(int row, char column, bool on);
//set individual LED brightness: 0-100.0%
int led_set_brightness(int row, char column, float brightness);
//set all LED brightness: 0-100.0%
int led_set_brightness_all(float brightness);

#endif
