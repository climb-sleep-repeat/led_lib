#include "led.h"
#include "i2cmodel.h"
#include <stdio.h>
#include <stdlib.h>

#define DRIVER_0 0b1100000
#define DRIVER_1 0b1100001
#define DRIVER_2 0b1100010
#define DRIVER_3 0b1100011
#define DRIVER_4 0b1100100
#define DRIVER_5 0b1100101
#define DRIVER_6 0b1100110
#define DRIVER_7 0b1100111
#define DRIVER_8 0b1101000
#define DRIVER_9 0b1101001

#define PWM_0 0x01
#define PWM_1 0x02
#define PWM_2 0x03
#define PWM_3 0x04
#define PWM_4 0x05
#define PWM_5 0x06
#define PWM_6 0x07
#define PWM_7 0x08
#define PWM_8 0x09
#define PWM_9 0x0A
#define PWM_10 0x0B
#define PWM_11 0x0C
#define PWM_12 0x0D
#define PWM_13 0x0E
#define PWM_14 0x0F
#define PWM_15 0x10

#define NO_AUTO_INC 0x00
#define MAX_LEDS 15
#define DEFAULT_BRIGHTNESS 128

static i2c_model *s_i2c_model = 0;
struct led{
  uint8_t brightness;
  int row;
  char column;
  bool on;
};

static struct led *leds[MAX_LEDS] = {NULL};

struct __attribute__((__packed__)) packet {
  uint8_t address;
  uint8_t data;
};

static struct led * find_led(int row, char column);
static int led_get_address_and_reg(int row, char column, uint8_t * address, uint8_t * reg);
static struct led * new_led(int row, char column, uint8_t brightness);

void led_init(){
  s_i2c_model = (i2c_model *)malloc(sizeof(i2c_model));
}

void led_quit(){
  free(s_i2c_model);
  for(int i = 0;i<MAX_LEDS;i++){
    if(leds[i])
      free(leds[i]);
    else
      return;
  }
}

int led_turn_on_off(int row, char column, bool on){
  uint8_t address,reg;
  struct packet p;
  struct led * p_led = find_led(column, row);
  if(p_led){
    if(p_led->on == on){
      return 1;
    }
  }
  else{
    p_led = new_led(row, column, DEFAULT_BRIGHTNESS);
  }
  if(led_get_address_and_reg(row, column, &address, &reg)){
    printf("led get address error\n");
    return -1;
  }

  p.address = (NO_AUTO_INC|reg);
  p.data = ((uint8_t)on|p_led->brightness);
  
  i2c_model_set_address(s_i2c_model, address);
  i2c_model_write_data(s_i2c_model, &p, sizeof(struct packet));
  p_led->on = true;
  return 0;
}

int led_set_brightness(int row, char column, float brightness){
  struct led * p_led = find_led(row,column);
  if(p_led){
    p_led->brightness = (uint8_t)(256*brightness/100.0);
    led_turn_on_off(row,column,true);
    return 0;
  }
  else
    return -1;
}

int led_set_brightness_all(float brightness){
  return 0;
}

struct led * new_led(int row, char column, uint8_t brightness){
  for(int i = 0;i<MAX_LEDS;i++){
    if(leds[i] == NULL){
      leds[i] = (struct led *)malloc(sizeof(struct led));
      leds[i]->row = row;
      leds[i]->column = column;
      leds[i]->brightness = brightness;
      leds[i]->on = false;
    }
  }
  return NULL;
}
  
struct led * find_led(int row, char column){
  for(int i = 0;i<MAX_LEDS;i++){
    if(leds[i] == NULL)
      return NULL;
    else if(leds[i]->row == row && leds[i]->column == column)
      return leds[i];
  }
  return NULL;
}

int led_get_address_and_reg(int row, char column, uint8_t * address, uint8_t * reg){
  switch(row){
  case 2:
    switch(column){
    case 'g':
      *address=DRIVER_9;
      *reg = PWM_6;
      break;
    case 'j':
      *address=DRIVER_9;
      *reg = PWM_7;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 3:
    switch(column){
    case 'b':
      *address=DRIVER_8;
      *reg = PWM_5;
      break;
    case 'd':
      *address=DRIVER_8;
      *reg = PWM_6;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 4:
    switch(column){
    case 'b':
      *address=DRIVER_8;
      *reg = PWM_4;
      break;
    case 'g':
      *address=DRIVER_9;
      *reg = PWM_4;
      break;
    case 'i':
      *address=DRIVER_9;
      *reg = PWM_5;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 5:
    switch(column){
    case 'a':
      *address=DRIVER_8;
      *reg = PWM_0;
      break;
    case 'c':
      *address=DRIVER_8;
      *reg = PWM_1;
      break;
    case 'd':
      *address=DRIVER_8;
      *reg = PWM_2;
      break;
    case 'f':
      *address=DRIVER_8;
      *reg = PWM_3;
      break;
    case 'h':
      *address=DRIVER_9;
      *reg = PWM_0;
      break;
    case 'i':
      *address=DRIVER_9;
      *reg = PWM_1;
      break;
    case 'j':
      *address=DRIVER_9;
      *reg = PWM_2;
      break;
    case 'k':
      *address=DRIVER_9;
      *reg = PWM_3;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 6:
    switch(column){
    case 'b':
      *address=DRIVER_6;
      *reg = PWM_10;
      break;
    case 'c':
      *address=DRIVER_6;
      *reg = PWM_11;
      break;
    case 'd':
      *address=DRIVER_6;
      *reg = PWM_12;
      break;
    case 'e':
      *address=DRIVER_6;
      *reg = PWM_13;
      break;
    case 'f':
      *address=DRIVER_6;
      *reg = PWM_14;
      break;
    case 'g':
      *address=DRIVER_7;
      *reg = PWM_11;
      break;
    case 'h':
      *address=DRIVER_7;
      *reg = PWM_12;
      break;
    case 'i':
      *address=DRIVER_7;
      *reg = PWM_13;
      break;
    case 'j':
      *address=DRIVER_7;
      *reg = PWM_14;
      break;
    case 'k':
      *address=DRIVER_7;
      *reg = PWM_15;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 7:
    switch(column){
    case 'b':
      *address=DRIVER_6;
      *reg = PWM_5;
      break;
    case 'c':
      *address=DRIVER_6;
      *reg = PWM_6;
      break;
    case 'd':
      *address=DRIVER_6;
      *reg = PWM_7;
      break;
    case 'e':
      *address=DRIVER_6;
      *reg = PWM_8;
      break;
    case 'f':
      *address=DRIVER_6;
      *reg = PWM_9;
      break;
    case 'g':
      *address=DRIVER_7;
      *reg = PWM_6;
      break;
    case 'h':
      *address=DRIVER_7;
      *reg = PWM_7;
      break;
    case 'i':
      *address=DRIVER_7;
      *reg = PWM_8;
      break;
    case 'j':
      *address=DRIVER_7;
      *reg = PWM_9;
      break;
    case 'k':
      *address=DRIVER_7;
      *reg = PWM_10;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;    
  case 8:
    switch(column){
    case 'b':
      *address=DRIVER_6;
      *reg = PWM_0;
      break;
    case 'c':
      *address=DRIVER_6;
      *reg = PWM_1;
      break;
    case 'd':
      *address=DRIVER_6;
      *reg = PWM_2;
      break;
    case 'e':
      *address=DRIVER_6;
      *reg = PWM_3;
      break;
    case 'f':
      *address=DRIVER_6;
      *reg = PWM_4;
      break;
    case 'g':
      *address=DRIVER_7;
      *reg = PWM_1;
      break;
    case 'h':
      *address=DRIVER_7;
      *reg = PWM_2;
      break;
    case 'i':
      *address=DRIVER_7;
      *reg = PWM_3;
      break;
    case 'j':
      *address=DRIVER_7;
      *reg = PWM_4;
      break;
    case 'k':
      *address=DRIVER_7;
      *reg = PWM_5;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 9:
    switch(column){
    case 'a':
      *address=DRIVER_4;
      *reg = PWM_11;
      break;
    case 'b':
      *address=DRIVER_4;
      *reg = PWM_12;
      break;
    case 'c':
      *address=DRIVER_4;
      *reg = PWM_13;
      break;
    case 'd':
      *address=DRIVER_4;
      *reg = PWM_14;
      break;
    case 'e':
      *address=DRIVER_4;
      *reg = PWM_15;
      break;
    case 'f':
      *address=DRIVER_5;
      *reg = PWM_11;
      break;
    case 'g':
      *address=DRIVER_5;
      *reg = PWM_12;
      break;
    case 'h':
      *address=DRIVER_5;
      *reg = PWM_13;
      break;
    case 'i':
      *address=DRIVER_5;
      *reg = PWM_14;
      break;
    case 'j':
      *address=DRIVER_5;
      *reg = PWM_15;
      break;
    case 'k':
      *address=DRIVER_7;
      *reg = PWM_0;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 10:
    switch(column){
    case 'a':
      *address=DRIVER_4;
      *reg = PWM_6;
      break;
    case 'b':
      *address=DRIVER_4;
      *reg = PWM_7;
      break;
    case 'c':
      *address=DRIVER_4;
      *reg = PWM_8;
      break;
    case 'd':
      *address=DRIVER_4;
      *reg = PWM_9;
      break;
    case 'e':
      *address=DRIVER_4;
      *reg = PWM_10;
      break;
    case 'f':
      *address=DRIVER_5;
      *reg = PWM_5;
      break;
    case 'g':
      *address=DRIVER_5;
      *reg = PWM_6;
      break;
    case 'h':
      *address=DRIVER_5;
      *reg = PWM_7;
      break;
    case 'i':
      *address=DRIVER_5;
      *reg = PWM_8;
      break;
    case 'j':
      *address=DRIVER_5;
      *reg = PWM_9;
      break;
    case 'k':
      *address=DRIVER_5;
      *reg = PWM_10;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 11:
    switch(column){
    case 'a':
      *address=DRIVER_4;
      *reg = PWM_0;
      break;
    case 'b':
      *address=DRIVER_4;
      *reg = PWM_1;
      break;
    case 'c':
      *address=DRIVER_4;
      *reg = PWM_2;
      break;
    case 'd':
      *address=DRIVER_4;
      *reg = PWM_3;
      break;
    case 'e':
      *address=DRIVER_4;
      *reg = PWM_4;
      break;
    case 'f':
      *address=DRIVER_4;
      *reg = PWM_5;
      break;
    case 'g':
      *address=DRIVER_5;
      *reg = PWM_0;
      break;
    case 'h':
      *address=DRIVER_5;
      *reg = PWM_1;
      break;
    case 'i':
      *address=DRIVER_5;
      *reg = PWM_2;
      break;
    case 'j':
      *address=DRIVER_5;
      *reg = PWM_3;
      break;
    case 'k':
      *address=DRIVER_5;
      *reg = PWM_4;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 12:
    switch(column){
    case 'a':
      *address=DRIVER_2;
      *reg = PWM_11;
      break;
    case 'b':
      *address=DRIVER_2;
      *reg = PWM_12;
      break;
    case 'c':
      *address=DRIVER_2;
      *reg = PWM_13;
      break;
    case 'd':
      *address=DRIVER_2;
      *reg = PWM_14;
      break;
    case 'e':
      *address=DRIVER_2;
      *reg = PWM_15;
      break;
    case 'f':
      *address=DRIVER_2;
      *reg = PWM_10;
      break;
    case 'g':
      *address=DRIVER_3;
      *reg = PWM_11;
      break;
    case 'h':
      *address=DRIVER_3;
      *reg = PWM_12;
      break;
    case 'i':
      *address=DRIVER_3;
      *reg = PWM_13;
      break;
    case 'j':
      *address=DRIVER_3;
      *reg = PWM_14;
      break;
    case 'k':
      *address=DRIVER_3;
      *reg = PWM_15;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 13:
    switch(column){
    case 'a':
      *address=DRIVER_2;
      *reg = PWM_5;
      break;
    case 'b':
      *address=DRIVER_2;
      *reg = PWM_6;
      break;
    case 'c':
      *address=DRIVER_2;
      *reg = PWM_7;
      break;
    case 'd':
      *address=DRIVER_2;
      *reg = PWM_8;
      break;
    case 'e':
      *address=DRIVER_2;
      *reg = PWM_9;
      break;
    case 'f':
      *address=DRIVER_2;
      *reg = PWM_10;
      break;
    case 'g':
      *address=DRIVER_3;
      *reg = PWM_5;
      break;
    case 'h':
      *address=DRIVER_3;
      *reg = PWM_6;
      break;
    case 'i':
      *address=DRIVER_3;
      *reg = PWM_7;
      break;
    case 'j':
      *address=DRIVER_3;
      *reg = PWM_8;
      break;
    case 'k':
      *address=DRIVER_3;
      *reg = PWM_9;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 14:
    switch(column){
    case 'a':
      *address=DRIVER_2;
      *reg = PWM_0;
      break;
    case 'c':
      *address=DRIVER_2;
      *reg = PWM_1;
      break;
    case 'd':
      *address=DRIVER_2;
      *reg = PWM_2;
      break;
    case 'e':
      *address=DRIVER_2;
      *reg = PWM_3;
      break;
    case 'f':
      *address=DRIVER_2;
      *reg = PWM_4;
      break;
    case 'g':
      *address=DRIVER_3;
      *reg = PWM_0;
      break;
    case 'h':
      *address=DRIVER_3;
      *reg = PWM_1;
      break;
    case 'i':
      *address=DRIVER_3;
      *reg = PWM_2;
      break;
    case 'j':
      *address=DRIVER_3;
      *reg = PWM_3;
      break;
    case 'k':
      *address=DRIVER_3;
      *reg = PWM_4;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 15:
    switch(column){
    case 'a':
      *address=DRIVER_0;
      *reg = PWM_11;
      break;
    case 'b':
      *address=DRIVER_0;
      *reg = PWM_12;
      break;
    case 'c':
      *address=DRIVER_0;
      *reg = PWM_13;
      break;
    case 'd':
      *address=DRIVER_0;
      *reg = PWM_14;
      break;
    case 'e':
      *address=DRIVER_1;
      *reg = PWM_11;
      break;
    case 'f':
      *address=DRIVER_1;
      *reg = PWM_12;
      break;
    case 'g':
      *address=DRIVER_1;
      *reg = PWM_13;
      break;
    case 'i':
      *address=DRIVER_0;
      *reg = PWM_14;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 16:
    switch(column){
    case 'a':
      *address=DRIVER_0;
      *reg = PWM_6;
      break;
    case 'b':
      *address=DRIVER_0;
      *reg = PWM_7;
      break;
    case 'c':
      *address=DRIVER_0;
      *reg = PWM_8;
      break;
    case 'd':
      *address=DRIVER_0;
      *reg = PWM_9;
      break;
    case 'e':
      *address=DRIVER_0;
      *reg = PWM_10;
      break;
    case 'f':
      *address=DRIVER_1;
      *reg = PWM_5;
      break;
    case 'g':
      *address=DRIVER_1;
      *reg = PWM_6;
      break;
    case 'h':
      *address=DRIVER_1;
      *reg = PWM_7;
      break;
    case 'i':
      *address=DRIVER_0;
      *reg = PWM_8;
      break;
    case 'j':
      *address=DRIVER_0;
      *reg = PWM_9;
      break;
    case 'k':
      *address=DRIVER_0;
      *reg = PWM_10;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 17:
    switch(column){
    case 'd':
      *address=DRIVER_0;
      *reg = PWM_5;
      break;
    case 'g':
      *address=DRIVER_1;
      *reg = PWM_4;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 18:
    switch(column){
    case 'a':
      *address=DRIVER_0;
      *reg = PWM_0;
      break;
    case 'b':
      *address=DRIVER_0;
      *reg = PWM_1;
      break;
    case 'c':
      *address=DRIVER_0;
      *reg = PWM_2;
      break;
    case 'd':
      *address=DRIVER_0;
      *reg = PWM_3;
      break;
    case 'e':
      *address=DRIVER_0;
      *reg = PWM_4;
      break;
    case 'g':
      *address=DRIVER_1;
      *reg = PWM_0;
      break;
    case 'h':
      *address=DRIVER_1;
      *reg = PWM_1;
      break;
    case 'i':
      *address=DRIVER_0;
      *reg = PWM_2;
      break;
    case 'k':
      *address=DRIVER_0;
      *reg = PWM_3;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  default:
   break;
  }
  return 0;
}
