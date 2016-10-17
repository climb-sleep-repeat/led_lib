#include "led.h"
#include "i2cmodel.h"

#define DRIVER_0 Ox1100000
#define DRIVER_1 Ox1100001
#define DRIVER_2 Ox1100010
#define DRIVER_3 Ox1100011
#define DRIVER_4 Ox1100100
#define DRIVER_5 Ox1100101
#define DRIVER_6 Ox1100110
#define DRIVER_7 Ox1100111
#define DRIVER_8 0x1101000
#define DRIVER_9 0x1101001

#define PWM_0 Ox02
#define PWM_1 Ox03
#define PWM_2 Ox04
#define PWM_3 Ox05
#define PWM_4 Ox06
#define PWM_5 Ox07
#define PWM_6 Ox08
#define PWM_7 Ox09
#define PWM_8 Ox0A
#define PWM_9 Ox0B
#define PWM_10 Ox0C
#define PWM_11 Ox0D
#define PWM_12 Ox0E
#define PWM_13 Ox0F
#define PWM_14 Ox10


static int led_get_address(int row, char column);

int led_turn_on_off(int row, char column, bool on){
  int address,reg;
  if(led_get_address(row, column, &address, &reg))
    printf("led get address error\n");
  
}

int led_set_brightness(int row, char column, float brightness){

}

int led_set_brightness_all(float brightness){

}

int led_get_address_and_reg(int row, char column, int * address, int * reg){
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
}
