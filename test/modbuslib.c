#include <stdint.h>

#include <stdio.h>
#include "mod_crc.h"
void modbus(uint8_t modbus_id, uint8_t *modbus_data, uint8_t modbus_data_len, uint16_t *ragiser, uint8_t *data_tranmit, uint8_t *data_trasmit_lan)
{

    void CRC_CHECK(uint8_t * modbus_data_crc, uint8_t modbus_data_len_crc, uint8_t * data_low, uint8_t * data_high)
    {
        uint16_t crc = CRC16(modbus_data_crc, modbus_data_len_crc - 1);
        uint8_t crc_low = crc >> 8;
        uint8_t crc_high = crc;
        *data_low = crc_low;
        *data_high = crc_high;
    }
    void trnsmit(uint8_t mode, uint8_t * data, uint8_t len)
    {
        
        switch (mode)
        {
        case 0x03:
            data_tranmit[0] = modbus_id;
            data_tranmit[1] = mode;
            data_tranmit[2] = (modbus_data[4] * 256) + (modbus_data[5]) * 2;
            int y = 3;
            for (int x = 0; x < len; x++,y++)
            {
                data_tranmit[y] = data[x]; // هر دو بایت برسی شود
            }
            CRC_CHECK(data_tranmit, y, &data_tranmit[y + 1], &data_tranmit[y + 2]);
            *data_trasmit_lan = y+2;
            break;

        default:
            break;
        }
    }
    void Read_Holding_Register()
    {
        uint16_t start_addreas_ragister = (modbus_data[2] * 256) + (modbus_data[3]);
        uint16_t Quantity_addres_ragister = (modbus_data[4] * 256) + (modbus_data[5]); // error 1 or 125
        uint8_t data_read[Quantity_addres_ragister * 2];
        int y = 0;
       // printf(":%d:",start_addreas_ragister);
        //for (int x=0;x < Quantity_addres_ragister ;x++)printf("%d ",ragiser[x]);
        for (int x = start_addreas_ragister; x < (start_addreas_ragister + Quantity_addres_ragister);x++,y++)
        {   
            
            if (ragiser[x] > 255)
            {   
                printf("\n%d",ragiser[x]);
                data_read[y] = ragiser[x]>>8;
                printf("\n%X\n",data_read[y]);
                y++;
                data_read[y] = ragiser[x];
                printf("%X\n",data_read[y]);
                
            }
            else
            {
                data_read[y] = 0x00;
                data_read[++y] = ragiser[x];
                
            }
        }

        printf("%d\n", y);
    for(int x=0;x<y;x++){
    printf(" %X ",data_read[x]);
    }
        trnsmit(0x03, data_read, y);

    }

    if (modbus_id == modbus_data[0])
    {
        uint8_t data_low;
        uint8_t data_high;
        CRC_CHECK(modbus_data, modbus_data_len, &data_low, &data_high);
        if (data_high == modbus_data[modbus_data_len - 1])
        {
            if (data_low == modbus_data[modbus_data_len])
            {
                switch (modbus_data[1])
                {
                case 0x03:
                    Read_Holding_Register();
                    break;
                case 0x06:
                    break;
                default:
                    break;
                }
            }
        }
    }
}
