#include <stdio.h>
#include <stdint.h>
#include "modbuslib.h"
uint8_t datatest[2]={0x01,0x03};
uint8_t testdata[256]={0x01,0x03,0x00,0x00,0x00,0x0A,0xC5,0xCD};
uint8_t data_tx[256];
int main()
{
 modbus(1,testdata,7,datatest,data_tx);
}

