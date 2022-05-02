#ifndef MODBUS_LIB_H_INCLUDED
#define MODBUS_LIB_H_INCLUDED

#include <stdint.h>
#include "mod_crc.h"
#define   Read_Holding_Register Read_Holding_Registers()
#define   Write_Single_Register Write_Single_Registers()
void  modulus_lib(unsigned char  *datamodbus,uint8_t id_modbus,uint8_t String_len,uint8_t * registers,uint8_t * send_date,uint8_t * len_send_date);

#endif // MODBUS_LIB_H_INCLUDED
