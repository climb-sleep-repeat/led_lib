#include "i2cmodel.h"
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>

i2c_model *s_port_1 = NULL;
i2c_model *s_port_2 = NULL;

int i2c_model_init(i2c_model *p_i2c_model)
{
  //open the appropriate port
  if(p_i2c_model->m_port == i2c_1)
    p_i2c_model->m_fd = open("/dev/i2c-1", O_RDWR);
  else if(p_i2c_model->m_port == i2c_2)
    p_i2c_model->m_fd = open("/dev/i2c-2", O_RDWR);
  else
    {
      printf("invalid i2c port\n");
      return -1;
    }
  //check to see if there is a valid i2c fd
  if (p_i2c_model->m_fd < 0)
    {
      perror("open()");
      return -1;
    }
  else  
    //success!
    return 0;
}

int i2c_model_set_singleton(i2c_model *p_i2c_model, i2c_port port)
{
  //find appropriate port
  if(port == i2c_1)
    {
      //has the singleton already been set?
      if(!s_port_1)
	{
	  //if not, set it
	  s_port_1 = p_i2c_model;
	}
      else
	{
	  //if yes, return error and alert user
	  printf("error: port already in use");
	  return -1;
	}
    }
  //same as above, for port 2
  else if(port == i2c_2)
    {
      if(!s_port_2)
	{
	  s_port_2 = p_i2c_model;
	}
      else
	{
	  printf("error: port already set\n");
	  return -1;
	}
    }
  //only 2 valid ports
  else
    {
      //return error and alert user
      printf("error: invalid port\n");
      return -1;
    }

  //store port number
  p_i2c_model->m_port = port;
  //return success
  return 0;
}

i2c_model * i2c_model_get_singleton(i2c_port port)
{
  //which port?
    if(port == i2c_1)
      {
	//if object exists
	if (s_port_1)
	  //return accessor
	  return s_port_1;
	else
	  {
	    printf("error: port not set\n");
	  }
      }
    //same as above for port 2
    else if(port == i2c_2)
      {
	if (s_port_2)
	  return s_port_2;
	else
	  {
	    printf("error: port not set\n");
	  }
      }
    else
      {
	printf("invalid port number\n");
      }
    return NULL;
}

int i2c_model_set_address(i2c_model *p_i2c_model, int address)
{
  //setup port for i2c with appropriate slave address
  if(ioctl(p_i2c_model->m_fd, I2C_SLAVE, address) < 0)
    {
      perror("ioctl");
      return -1;
    }
  //success
  else
    return 0;
}

int i2c_model_write_data(i2c_model *p_i2c_model, void *data, uint8_t size)
{
  if(write(p_i2c_model->m_fd, data, size) != size)
    {
      perror("write");
      return -1;
    }
  else
    return 0;
}

int i2c_model_read_data(i2c_model *p_i2c_model, void *data, uint8_t size)
{
  if(read(p_i2c_model->m_fd, data, size) != size)
    {
      perror("read");
      return -1;
    }
  else
    return 0;
}
