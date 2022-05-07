#include <stdio.h>
#include <stdint.h>
#include "modbuslib.h"
uint16_t datatest[10]={2000,0x03,300,0x00,0x00,   0x00,0x00,0x00,0x00,2000};
uint8_t testdata[256]={0x01,0x03,0x00,0x00,0x00,0x0A,0xC5,0xCD};
uint8_t data_tx[256];
uint8_t data_tx_lan;
int main()
{
 modbus(1,testdata,7,datatest,data_tx,&data_tx_lan);
    printf("\n");
    for(int x=0;x<data_tx_lan;x++){
    printf(" %X ",data_tx[x]);
    }
        
    

  
 
}

