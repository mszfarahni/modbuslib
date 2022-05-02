#ifndef MODBUSLIB_H_INCLUDED
#define MODBUSLIB_H_INCLUDED
#include <stdint.h>
#include <stdio.h>
#include "modbuslib.c"
#define Read_Holding_Registers Read_Holding_Register()
void modbus(uint8_t modbus_id,uint8_t * modbus_data,uint8_t modbus_data_len,uint8_t * ragiser,uint8_t *ragiser_trasmit)
#endif