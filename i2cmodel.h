#ifndef i2cmodel_h
#define i2cmodel_h

#include <stdint.h>

typedef enum i2c_port_t{
  i2c_1 = 1,
  i2c_2 = 2
}i2c_port;

typedef struct i2c_model_t{
  int m_fd;
  i2c_port m_port;
}i2c_model;

//should be called from main before any init functions of objects that use i2c
int i2c_model_init(i2c_model *p_i2c_model);

//this is how to access a global object that should be instantiated in main
int i2c_model_set_singleton(i2c_model *p_i2c_model, i2c_port port);
i2c_model * i2c_model_get_singleton(i2c_port port);

//use to change the i2c address before reading and writing to a new sensor
int i2c_model_set_address(i2c_model *p_i2c_model, int address);

//read and write
int i2c_model_write_data(i2c_model *p_i2c_model, void *data, uint8_t size);
int i2c_model_read_data(i2c_model *p_i2c_model, void *data, uint8_t size);

#endif
