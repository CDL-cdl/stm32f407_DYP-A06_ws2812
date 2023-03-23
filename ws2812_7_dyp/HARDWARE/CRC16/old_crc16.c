#include"old_crc16.h"

#define CRC_16_POLYNOMIALS  0xA001   //CRC
u16 CRC16( u8* pchar, u8 charlen)
{
  u16 crc16=0xffff;
  u8 i;
  while(charlen--)
  {
    crc16=crc16^((u16)*pchar);
    for(i=0;i<8;i++)
    {
      if(crc16&0x0001)
      {
        crc16=crc16>>1;
        crc16=crc16^CRC_16_POLYNOMIALS;
      }
      else
      {
        crc16=crc16>>1;
      }
    }
    pchar++;
  }
  crc16=(crc16>>8)+(crc16<<8);   
  return crc16;
}
