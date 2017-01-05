#include "led.h"
#include "i2cmodel.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define ALL_CALL 0b1101000 

#define MODE_1 0x00
#define CONFIG 0xA1
#define AUTO_INC 0xA0
#define PWM_0 0x02
#define MAX_LEDS 25
#define NUM_DRIVERS 10
#define NUM_LEDS_PER_DRIVER 16
#define DEFAULT_BRIGHTNESS 128

static uint8_t led_driver_address[] = {0b1100000, 0b1100001, 0b1100010, 0b1100011, 0b1100100, 0b1100101, 0b1100110, 0b1100111, 0b1101001, 0b1101010};
static i2c_model *s_i2c_model = 0;

struct led_driver{
  uint8_t led_brightness[NUM_LEDS_PER_DRIVER];
};

static struct led_driver driver[NUM_DRIVERS];

struct __attribute__((__packed__)) command {
  uint8_t reg;
  uint8_t data;
};

struct __attribute__((__packed__)) packet{
  uint8_t reg;
  uint8_t data[16];
};

static int led_get_driver_and_pwm_indices(int row, char column, uint8_t * driver_index, uint8_t * pwm_index);

int led_init(){
  s_i2c_model = (i2c_model *)malloc(sizeof(i2c_model));
  i2c_model_set_singleton(s_i2c_model, i2c_1);

  i2c_model_init(s_i2c_model);
  uint8_t address = ALL_CALL;
  struct command c;

  c.reg = MODE_1;
  c.data = CONFIG;	

  if(i2c_model_set_address(s_i2c_model, address)==-1){
    printf("set address error\n");
    return -1;
  }

  if(i2c_model_write_data(s_i2c_model, &c, sizeof(struct command))==-1){
    printf("write data error");
    return -1;
  }
  sleep(1);  
//setup ledout registers.

  c.reg = 0x14;
  c.data = 0xAA;

  if(i2c_model_write_data(s_i2c_model, &c, sizeof(struct command))==-1){
    printf("write data error");
    return -1;
  }
 c.reg = 0x15;
 c.data = 0xAA;
  if(i2c_model_write_data(s_i2c_model, &c, sizeof(struct command))==-1){
    printf("write data error");
    return -1;
  }
 c.reg = 0x16;
 c.data = 0xAA;
  if(i2c_model_write_data(s_i2c_model, &c, sizeof(struct command))==-1){
    printf("write data error");
    return -1;
  }
 c.reg = 0x17;
 c.data = 0xAA;

  if(i2c_model_write_data(s_i2c_model, &c, sizeof(struct command))==-1){
    printf("write data error");
    return -1;
  }
return 0;
}

int add_led_to_list_with_brightness(int row, char column, uint8_t brightness){
  uint8_t driver_index;
  uint8_t pwm_index;
  if(led_get_driver_and_pwm_indices(row, column, &driver_index, &pwm_index)==0){
    driver[driver_index].led_brightness[pwm_index] = brightness;
    return 0;
  }
  return -1;
}

void clear_led_list(){
  memset(driver, 0, sizeof(struct led_driver));
}

int led_apply_values_to_driver(){
  for(int i = 0; i<NUM_DRIVERS; i++){
    if(i2c_model_set_address(s_i2c_model, led_driver_address[i])==-1){
      printf("set address error\n");
      return -1;
    }
    struct packet p;
    p.reg = AUTO_INC|PWM_0;
    memcpy(&p.data, &driver[i].led_brightness, NUM_LEDS_PER_DRIVER*sizeof(uint8_t));
    if(i2c_model_write_data(s_i2c_model, &p, sizeof(struct packet))==-1){
      printf("write data error");
      return -1;
    }  
  }
  return 0;
}

int led_get_driver_and_pwm_indices(int row, char column, uint8_t * driver_index, uint8_t * pwm_index){
  switch(row){
  case 2:
    switch(column){
    case 'g':
      *driver_index= 9;
      *pwm_index =  6;
      break;
    case 'j':
      *driver_index= 9;
      *pwm_index =  7;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 3:
    switch(column){
    case 'b':
      *driver_index= 8;
      *pwm_index =  5;
      break;
    case 'd':
      *driver_index= 8;
      *pwm_index =  6;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 4:
    switch(column){
    case 'b':
      *driver_index= 8;
      *pwm_index =  4;
      break;
    case 'g':
      *driver_index= 9;
      *pwm_index =  4;
      break;
    case 'i':
      *driver_index= 9;
      *pwm_index =  5;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 5:
    switch(column){
    case 'a':
      *driver_index= 8;
      *pwm_index =  0;
      break;
    case 'c':
      *driver_index= 8;
      *pwm_index =  1;
      break;
    case 'd':
      *driver_index= 8;
      *pwm_index =  2;
      break;
    case 'f':
      *driver_index= 8;
      *pwm_index =  3;
      break;
    case 'h':
      *driver_index= 9;
      *pwm_index =  0;
      break;
    case 'i':
      *driver_index= 9;
      *pwm_index =  1;
      break;
    case 'j':
      *driver_index= 9;
      *pwm_index =  2;
      break;
    case 'k':
      *driver_index= 9;
      *pwm_index =  3;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 6:
    switch(column){
    case 'b':
      *driver_index= 6;
      *pwm_index =  10;
      break;
    case 'c':
      *driver_index= 6;
      *pwm_index =  11;
      break;
    case 'd':
      *driver_index= 6;
      *pwm_index =  12;
      break;
    case 'e':
      *driver_index= 6;
      *pwm_index =  13;
      break;
    case 'f':
      *driver_index= 6;
      *pwm_index =  14;
      break;
    case 'g':
      *driver_index= 7;
      *pwm_index =  11;
      break;
    case 'h':
      *driver_index= 7;
      *pwm_index =  12;
      break;
    case 'i':
      *driver_index= 7;
      *pwm_index =  13;
      break;
    case 'j':
      *driver_index= 7;
      *pwm_index =  14;
      break;
    case 'k':
      *driver_index= 7;
      *pwm_index =  15;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 7:
    switch(column){
    case 'b':
      *driver_index= 6;
      *pwm_index =  5;
      break;
    case 'c':
      *driver_index= 6;
      *pwm_index =  6;
      break;
    case 'd':
      *driver_index= 6;
      *pwm_index =  7;
      break;
    case 'e':
      *driver_index= 6;
      *pwm_index =  8;
      break;
    case 'f':
      *driver_index= 6;
      *pwm_index =  9;
      break;
    case 'g':
      *driver_index= 7;
      *pwm_index =  6;
      break;
    case 'h':
      *driver_index= 7;
      *pwm_index =  7;
      break;
    case 'i':
      *driver_index= 7;
      *pwm_index =  8;
      break;
    case 'j':
      *driver_index= 7;
      *pwm_index =  9;
      break;
    case 'k':
      *driver_index= 7;
      *pwm_index =  10;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;    
  case 8:
    switch(column){
    case 'b':
      *driver_index= 6;
      *pwm_index =  0;
      break;
    case 'c':
      *driver_index= 6;
      *pwm_index =  1;
      break;
    case 'd':
      *driver_index= 6;
      *pwm_index =  2;
      break;
    case 'e':
      *driver_index= 6;
      *pwm_index =  3;
      break;
    case 'f':
      *driver_index= 6;
      *pwm_index =  4;
      break;
    case 'g':
      *driver_index= 7;
      *pwm_index =  1;
      break;
    case 'h':
      *driver_index= 7;
      *pwm_index =  2;
      break;
    case 'i':
      *driver_index= 7;
      *pwm_index =  3;
      break;
    case 'j':
      *driver_index= 7;
      *pwm_index =  4;
      break;
    case 'k':
      *driver_index= 7;
      *pwm_index =  5;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 9:
    switch(column){
    case 'a':
      *driver_index= 4;
      *pwm_index =  11;
      break;
    case 'b':
      *driver_index= 4;
      *pwm_index =  12;
      break;
    case 'c':
      *driver_index= 4;
      *pwm_index =  13;
      break;
    case 'd':
      *driver_index= 4;
      *pwm_index =  14;
      break;
    case 'e':
      *driver_index= 4;
      *pwm_index =  15;
      break;
    case 'f':
      *driver_index= 5;
      *pwm_index =  11;
      break;
    case 'g':
      *driver_index= 5;
      *pwm_index =  12;
      break;
    case 'h':
      *driver_index= 5;
      *pwm_index =  13;
      break;
    case 'i':
      *driver_index= 5;
      *pwm_index =  14;
      break;
    case 'j':
      *driver_index= 5;
      *pwm_index =  15;
      break;
    case 'k':
      *driver_index= 7;
      *pwm_index =  0;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 10:
    switch(column){
    case 'a':
      *driver_index= 4;
      *pwm_index =  6;
      break;
    case 'b':
      *driver_index= 4;
      *pwm_index =  7;
      break;
    case 'c':
      *driver_index= 4;
      *pwm_index =  8;
      break;
    case 'd':
      *driver_index= 4;
      *pwm_index =  9;
      break;
    case 'e':
      *driver_index= 4;
      *pwm_index =  10;
      break;
    case 'f':
      *driver_index= 5;
      *pwm_index =  5;
      break;
    case 'g':
      *driver_index= 5;
      *pwm_index =  6;
      break;
    case 'h':
      *driver_index= 5;
      *pwm_index =  7;
      break;
    case 'i':
      *driver_index= 5;
      *pwm_index =  8;
      break;
    case 'j':
      *driver_index= 5;
      *pwm_index =  9;
      break;
    case 'k':
      *driver_index= 5;
      *pwm_index =  10;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 11:
    switch(column){
    case 'a':
      *driver_index= 4;
      *pwm_index =  0;
      break;
    case 'b':
      *driver_index= 4;
      *pwm_index =  1;
      break;
    case 'c':
      *driver_index= 4;
      *pwm_index =  2;
      break;
    case 'd':
      *driver_index= 4;
      *pwm_index =  3;
      break;
    case 'e':
      *driver_index= 4;
      *pwm_index =  4;
      break;
    case 'f':
      *driver_index= 4;
      *pwm_index =  5;
      break;
    case 'g':
      *driver_index= 5;
      *pwm_index =  0;
      break;
    case 'h':
      *driver_index= 5;
      *pwm_index =  1;
      break;
    case 'i':
      *driver_index= 5;
      *pwm_index =  2;
      break;
    case 'j':
      *driver_index= 5;
      *pwm_index =  3;
      break;
    case 'k':
      *driver_index= 5;
      *pwm_index =  4;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 12:
    switch(column){
    case 'a':
      *driver_index= 2;
      *pwm_index =  11;
      break;
    case 'b':
      *driver_index= 2;
      *pwm_index =  12;
      break;
    case 'c':
      *driver_index= 2;
      *pwm_index =  13;
      break;
    case 'd':
      *driver_index= 2;
      *pwm_index =  14;
      break;
    case 'e':
      *driver_index= 2;
      *pwm_index =  15;
      break;
    case 'f':
      *driver_index= 2;
      *pwm_index =  10;
      break;
    case 'g':
      *driver_index= 3;
      *pwm_index =  11;
      break;
    case 'h':
      *driver_index= 3;
      *pwm_index =  12;
      break;
    case 'i':
      *driver_index= 3;
      *pwm_index =  13;
      break;
    case 'j':
      *driver_index= 3;
      *pwm_index =  14;
      break;
    case 'k':
      *driver_index= 3;
      *pwm_index =  15;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 13:
    switch(column){
    case 'a':
      *driver_index= 2;
      *pwm_index =  5;
      break;
    case 'b':
      *driver_index= 2;
      *pwm_index =  6;
      break;
    case 'c':
      *driver_index= 2;
      *pwm_index =  7;
      break;
    case 'd':
      *driver_index= 2;
      *pwm_index =  8;
      break;
    case 'e':
      *driver_index= 2;
      *pwm_index =  9;
      break;
    case 'f':
      *driver_index= 2;
      *pwm_index =  10;
      break;
    case 'g':
      *driver_index= 3;
      *pwm_index =  5;
      break;
    case 'h':
      *driver_index= 3;
      *pwm_index =  6;
      break;
    case 'i':
      *driver_index= 3;
      *pwm_index =  7;
      break;
    case 'j':
      *driver_index= 3;
      *pwm_index =  8;
      break;
    case 'k':
      *driver_index= 3;
      *pwm_index =  9;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 14:
    switch(column){
    case 'a':
      *driver_index= 2;
      *pwm_index =  0;
      break;
    case 'c':
      *driver_index= 2;
      *pwm_index =  1;
      break;
    case 'd':
      *driver_index= 2;
      *pwm_index =  2;
      break;
    case 'e':
      *driver_index= 2;
      *pwm_index =  3;
      break;
    case 'f':
      *driver_index= 2;
      *pwm_index =  4;
      break;
    case 'g':
      *driver_index= 3;
      *pwm_index =  0;
      break;
    case 'h':
      *driver_index= 3;
      *pwm_index =  1;
      break;
    case 'i':
      *driver_index= 3;
      *pwm_index =  2;
      break;
    case 'j':
      *driver_index= 3;
      *pwm_index =  3;
      break;
    case 'k':
      *driver_index= 3;
      *pwm_index =  4;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 15:
    switch(column){
    case 'a':
      *driver_index= 0;
      *pwm_index =  11;
      break;
    case 'b':
      *driver_index= 0;
      *pwm_index =  12;
      break;
    case 'c':
      *driver_index= 0;
      *pwm_index =  13;
      break;
    case 'd':
      *driver_index= 0;
      *pwm_index =  14;
      break;
    case 'e':
      *driver_index= 1;
      *pwm_index =  11;
      break;
    case 'f':
      *driver_index= 1;
      *pwm_index =  12;
      break;
    case 'g':
      *driver_index= 1;
      *pwm_index =  13;
      break;
    case 'i':
      *driver_index= 1;
      *pwm_index =  14;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 16:
    switch(column){
    case 'a':
      *driver_index= 0;
      *pwm_index =  6;
      break;
    case 'b':
      *driver_index= 0;
      *pwm_index =  7;
      break;
    case 'c':
      *driver_index= 0;
      *pwm_index =  8;
      break;
    case 'd':
      *driver_index= 0;
      *pwm_index =  9;
      break;
    case 'e':
      *driver_index= 0;
      *pwm_index =  10;
      break;
    case 'f':
      *driver_index= 1;
      *pwm_index =  5;
      break;
    case 'g':
      *driver_index= 1;
      *pwm_index =  6;
      break;
    case 'h':
      *driver_index= 1;
      *pwm_index =  7;
      break;
    case 'i':
      *driver_index= 1;
      *pwm_index =  8;
      break;
    case 'j':
      *driver_index= 1;
      *pwm_index =  9;
      break;
    case 'k':
      *driver_index= 1;
      *pwm_index =  10;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 17:
    switch(column){
    case 'd':
      *driver_index= 0;
      *pwm_index =  5;
      break;
    case 'g':
      *driver_index= 1;
      *pwm_index =  4;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  case 18:
    switch(column){
    case 'a':
      *driver_index= 0;
      *pwm_index =  0;
      break;
    case 'b':
      *driver_index= 0;
      *pwm_index =  1;
      break;
    case 'c':
      *driver_index= 0;
      *pwm_index =  2;
      break;
    case 'd':
      *driver_index= 0;
      *pwm_index =  3;
      break;
    case 'e':
      *driver_index= 0;
      *pwm_index =  4;
      break;
    case 'g':
      *driver_index= 1;
      *pwm_index =  0;
      break;
    case 'h':
      *driver_index= 1;
      *pwm_index =  1;
      break;
    case 'i':
      *driver_index= 1;
      *pwm_index =  2;
      break;
    case 'k':
      *driver_index= 1;
      *pwm_index =  3;
      break;
    default:
      printf("invalid hold\n");
      break;
    }
    break;
  default:
    printf("invalid column\n");
    return -1;
    break;
  }
  return 0;
}
