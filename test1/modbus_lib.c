#include <stdint.h>
#include "modbus_lib.h"
void modulus_lib(unsigned char  *datamodbus,uint8_t id_modbus,uint8_t String_len,uint8_t * registers,uint8_t * send_date,uint8_t  * len_send_date)
{

    void Read_Holding_Registers(){
        int startaddres=(datamodbus[2]*256)+datamodbus[3];
        int endaddres=(datamodbus[4]*256)+datamodbus[5];

        uint8_t send_data[256]={id_modbus,0x03,endaddres*2};
        // if برای اینکه از ۱۲۵ تا بیشتر نشه باید هایه خواندن ریجستر

        for(int z=startaddres+3,b=0;z<(endaddres*2)+3;z++,b++)
        {
            send_data[z]=registers[b];
        }
        uint8_t lan_registers_send=(endaddres*2)+3;
        uint16_t crc_send = CRC16(send_data,lan_registers_send);

                printf("test");

        send_data[lan_registers_send]=crc_send;
        send_data[lan_registers_send+1]=crc_send>>8;



             *send_date=send_data;
             *len_send_date=lan_registers_send+2;

    }


    void Write_Single_Registers(){
        uint16_t addraes=(datamodbus[3]*256)+datamodbus[4];
        uint16_t data=(datamodbus[5]*256)+datamodbus[6];
        *send_date = datamodbus;
        *len_send_date=String_len;
    }
















    if(datamodbus[0]==id_modbus)
    {
        int check_crc=datamodbus[String_len] << 8 | datamodbus[String_len-1];
        uint16_t crc=CRC16(datamodbus,String_len-1);

        if(check_crc==crc)
        {

            switch(datamodbus[1])
            {
            case 0x03:
                Read_Holding_Register;
            break;
            case 0x06:
                Write_Single_Register;
            break;
            }

        }
    }
}
