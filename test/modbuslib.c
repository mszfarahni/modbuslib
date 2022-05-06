#include <stdint.h>

#include <stdio.h>
#include "mod_crc.h"
void modbus(uint8_t modbus_id,uint8_t * modbus_data,uint8_t modbus_data_len,uint16_t * ragiser,uint8_t *data_tranmit,uint8_t * data_trasmit_lan)
{
 
    void CRC_CHECK(uint8_t * modbus_data_crc,uint8_t modbus_data_len_crc,uint8_t * data_low,uint8_t * data_high)
    {
        uint16_t crc=CRC16(modbus_data_crc,modbus_data_len_crc-1);
        uint8_t crc_low= crc>>8;
        uint8_t crc_high=crc;
        *data_low=crc_low;
        *data_high=crc_high;

    }
    void trnsmit(uint8_t mode,uint8_t * data,uint8_t len)
    {   
        uint8_t data_send[256];
        switch (mode)
        {
        case 0x03:
            data_send[0]=modbus_id;
            data_send[1]=mode;
            data_send[2]=(modbus_data[4]*256)+(modbus_data[5])*2;
            int y=3;
            for(int x=0;x<len;x++,
            
            y++)
            {   
                data_send[y]=data[x];// هر دو بایت برسی شود 
                
            }
            y=y+2;
            CRC_CHECK(data_send,y,&data_send[y+1],&data_send[y+2]);
            


            for(int x=0;x<y;x++)
            {
                data_tranmit[x]=data_send[x];
                printf(data_send[x]);
            }
            *data_trasmit_lan=y; 
            break;
        
        default:
            break;
        }
    }
    void Read_Holding_Register()
    {
        uint8_t start_addreas_ragister=(modbus_data[2]*256)+(modbus_data[3]);
        uint8_t Quantity_addres_ragister=(modbus_data[4]*256)+(modbus_data[5]);//error 1 or 125
        uint8_t data_read[Quantity_addres_ragister*2];
        int y=0;
        for(int x=start_addreas_ragister;x<(start_addreas_ragister+Quantity_addres_ragister);x++,y=y++)
        {
            if(ragiser[0] < 255)
            {
                data_read[y]=ragiser[x]>>8;
                printf("1:%d\n",y);
                data_read[++y]=ragiser[x];
                printf("2:%d\n",y);    
               // printf("%X || %X\n",data_read[y-1],data_read[y]);
                printf("3:%d\n",y);
            }
            else
            {
                printf("ok\n");
                data_read[y]=0;
                data_read[++y]=ragiser[x];
            }

        }
          

        printf("%d",y);
        trnsmit(0x03,data_read,y);

    }




    if(modbus_id==modbus_data[0])
    {   uint8_t data_low;
        uint8_t data_high;
        CRC_CHECK(modbus_data,modbus_data_len,&data_low,&data_high);
        if(data_high==modbus_data[modbus_data_len-1])
        {
            if(data_low==modbus_data[modbus_data_len])
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
