#include "CRC.h"                                                                      
                            
void crcInit(void) ;                                                                                





/**********************************************************************           
*                                                                                 
* Filename: crc.h                                                                 
*                                                                                 
* Description: A header file describing the various CRC standards.                
*                                                                                 
* Notes:                                                                          
*                                                                                 
*                                                                                 
* Copyright (c) 2000 by Michael Barr. This software is placed into                

* the public domain and may be used for any purpose. However, this                
* notice must not be changed or removed and no warranty is either                 
* expressed or implied by its publication or distribution.                        
**********************************************************************/           

#ifndef _crc_h                                                                    
#define _crc_h                                                                    


#define FALSE 0                                                                   
#define TRUE !FALSE                                                               

/*                                                                                
* Select the CRC standard from the list that follows.                             
*/                                                                                
#define CRC_CCITT                                                                 


#if defined(CRC_CCITT)                                                            

typedef unsigned short crc;                                                       


#define CRC_NAME "CRC-CCITT"                                                      
#define POLYNOMIAL 0x1021                                                         
#define INITIAL_REMAINDER 0xFFFF                                                  
#define FINAL_XOR_VALUE 0x0000                                                    
#define REFLECT_DATA FALSE                                                        
#define REFLECT_REMAINDER FALSE                                                   
#define CHECK_VALUE 0x29B1                                                        

#elif defined(CRC16)                                                              

typedef unsigned short crc;                                                       

#define CRC_NAME "CRC-16"                                                         
#define POLYNOMIAL 0x8005                                                         
#define INITIAL_REMAINDER 0x0000                                                  
#define FINAL_XOR_VALUE 0x0000                                                    
#define REFLECT_DATA TRUE                                                         
#define REFLECT_REMAINDER TRUE                                                    
#define CHECK_VALUE 0xBB3D                                                        

#elif defined(CRC32)                                                              


typedef unsigned long crc;                                                        

#define CRC_NAME "CRC-32"                                                         
#define POLYNOMIAL 0x04C11DB7                                                     
#define INITIAL_REMAINDER 0xFFFFFFFF                                              
#define FINAL_XOR_VALUE 0xFFFFFFFF                                                
#define REFLECT_DATA TRUE                                                         
#define REFLECT_REMAINDER TRUE                                                    
#define CHECK_VALUE 0xCBF43926                                                    

#else                                                                             

#error "One of CRC_CCITT, CRC16, or CRC32 must be #define'd."                     

#endif                                                                            


void crcInit(void);                                                               
unsigned int crcSlow(unsigned char const message[], int nBytes);                           
unsigned int crcFast(unsigned char const message[], int nBytes);                           



#endif /* _crc_h */                                                               



/**********************************************************************           
*                                                                                 
* Filename: crc.c                                                                 
*                                                                                 
* Description: Slow and fast implementations of the CRC standards.                
*                                                                                 
* Notes: The parameters for each supported CRC standard are                       
* defined in the header file crc.h. The implementtations                          
* here should stand up to further additions to thaat list.                        
*                                                                                 
*                                                                                 
* Copyright (c) 2000 by Michael Barr. This software is placed into                
* the public domain and may be used for any purpose. However, this                
* notice must not be changed or removed and no warranty is either                 
* expressed or implied by its publication or distribution.                        
**********************************************************************/           


/*                                                                                
* Derive parameters from the standard-specific parameters in crc.h.               
*/                                                                                
#define WIDTH (8 * sizeof(crc))                                                   
#define TOPBIT (1 << (WIDTH - 1))                                                 

#if (REFLECT_DATA == TRUE)                                                        
#undef REFLECT_DATA                                                               
#define REFLECT_DATA(X) ((unsigned char) reflect((X), 8))                         
#else                                                                             
#undef REFLECT_DATA                                                               
#define REFLECT_DATA(X) (X)                                                       
#endif                                                                            

#if (REFLECT_REMAINDER == TRUE)                                                   
#undef REFLECT_REMAINDER                                                          
#define REFLECT_REMAINDER(X) ((unsigned int) reflect((X), WIDTH))                          
#else                                                                             
#undef REFLECT_REMAINDER                                                          
#define REFLECT_REMAINDER(X) (X)                                                  

#endif                                                                            


/*********************************************************************            
*                                                                                 
* Function: reflect()                                                             
*                                                                                 
* Description: Reorder the bits of a binary sequence, by reflecting               
* them about the middle position.                                                 
*                                                                                 
* Notes: No checking is done that nBits <= 32.                                    
*                                                                                 
* Returns: The reflection of the original data.                                   
*                                                                                 
*********************************************************************/
/*            
static unsigned long  reflect(unsigned long data, unsigned char nBits)                                  
{                                                                                 
unsigned long reflection = 0x00000000;                                            
unsigned char bit;                                                                


for (bit = 0; bit < nBits; ++bit)                                                 
{                                                                                 

if (data & 0x01)                                                                  
{                                                                                 
reflection |= (1 << ((nBits - 1) - bit));
}                                                                                 

data = (data >> 1);                                                               
}                                                                                 

return (reflection);                                                              

}*/                                                         


/*********************************************************************            
*                                                                                 
*                                                                                 
* Function: crcSlow()                                                             
*                                                                                 
* Description: Compute the CRC of a given message.                                
*                                                                                 
* Notes:                                                                          
*                                                                                 
* Returns: The CRC of the message.                                                
*                                                                                 
*********************************************************************/            
unsigned int crcSlow(unsigned char const message[], int nBytes)                                
{                                                                                 
  unsigned int remainder = INITIAL_REMAINDER;                                                
  int byte;                                                                         
  unsigned char bit;                                                                
  
  
  /*                                                                                
  * Perform modulo-2 division, a byte at a time.                                    
  */                                                                                
  for (byte = 0; byte < nBytes; ++byte)                                             
  {                                                                                 
    {                                                                                 
      /*                                                                                
      * Bring the next byte into the remainder.                                         
      */                                                                                
      remainder ^= (REFLECT_DATA(message[byte]) << (WIDTH - 8));                        
      
      /*                                                                                
      * Perform modulo-2 division, a bit at a time.
      */
      for (bit = 8; bit > 0; --bit)
      {
        /* 
        * Try to divide the current data bit.
        */                                                                                
        if (remainder & TOPBIT)
        {                                                                                 
          remainder = (remainder << 1) ^ POLYNOMIAL; 
        }
        else                                                                              
        {
          remainder = (remainder << 1);
        }
      }
    }
  }
  
  /*                                                                                
  * The final remainder is the CRC result.                                          
  */                                                                                
  return (REFLECT_REMAINDER(remainder) ^ FINAL_XOR_VALUE);                          
  
} /* crcSlow() */                                                                 


//crc crcTable[256];                                                                


/*********************************************************************            
*                                                                                 
* Function: crcInit()                                                             
*                                                                                 
* Description: Populate the partial CRC lookup table.                             
*                                                                                 
* Notes: This function must be rerun any time the CRC standard                    
* is changed. If desired, it can be run "offline"" and                            
* the table results stored in an embedded system'ss ROM.                          

*                                                                                 
* Returns: None defined.                                                          
*                                                                                 
*********************************************************************/            
void crcInit(void)                                                                     
{      
  crc remainder; 
  int dividend; 
  unsigned char bit; 
  
  
  /* 
  * Compute the remainder of each possible dividend. 
  */ 
  for (dividend = 0; dividend < 256; ++dividend) 
  { 
    /* 
    * Start with the dividend followed by zeros. 
    */ 
    remainder = dividend << (WIDTH - 8); 
    
    
    /* 
    * Perform modulo-2 division, a bit at a time. 
    */ 
    for (bit = 8; bit > 0; --bit) 
    { 
      /* 
      * Try to divide the current data bit. 
      */ 
      if (remainder & TOPBIT) 
      { 
        remainder = (remainder << 1) ^ POLYNOMIAL; 
      } 
      else 
      { 
        remainder = (remainder << 1); 
      } 
    } 
    
    
    //crcTable[dividend] = remainder; 
    //sendChar(( unsigned long )remainder/256); 
    //sendChar(( unsigned long )remainder%256); 
    //sendChar(',');
    
  } 
  
}











/*********************************************************************            
*                                                                                 
* Function: crcFast()                                                             
*                                                                                 
* Description: Compute the CRC of a given message.                                
*                                                                                 
* Notes: crcInit() must be called first.                                          
*                                                                                 
* Returns: The CRC of the message.                                                
*                                                                                 
*********************************************************************/            
unsigned int crcFast(unsigned char const message[], int nBytes)                                
{                                                                                 
  unsigned char data;                                                               
  int tbyte;                                                                         
  
  unsigned int remainder = INITIAL_REMAINDER;                                                
  
  
  /*                                                                                
  * Divide the message by the polynomial, a byte at a time.                         
  */                                                                                
  for (tbyte = 0; tbyte < nBytes; ++tbyte)                                             
  {                                                                                 
    data = REFLECT_DATA(message[tbyte]) ^ (remainder >> (WIDTH - 8));                  
    remainder = CRC_table[data] ^ (remainder << 8);                                    
  }                                                                                 
  
  return ((REFLECT_REMAINDER(remainder)) ^ FINAL_XOR_VALUE);                          
  
}

// 计算 16 位 CRC 值，CRC-16 或 CRC-CCITT 
unsigned short CRC_16( unsigned char *aData, unsigned char aSize ) 
{ 
  unsigned char i; 
  unsigned short nAccum = 0; 
  
  for ( i = 0; i < aSize; i++ ) 
    nAccum = ( nAccum << 8 ) ^ ( unsigned short )CRC_table[( nAccum >> 8 ) ^ *aData++];
  return nAccum; 
} 

void Calculate_Crc16(unsigned char * aData, unsigned char aSize ) 
{
  unsigned char i; 
  unsigned short nAccum = 0; 
  for ( i = 0; i < aSize; i++ ) 
  nAccum = ( nAccum << 8 ) ^ ( unsigned short )(CRC_table[( nAccum >> 8 ) ^ *aData++]);
  *aData++ = nAccum/256;
  *aData++ = nAccum%256;
  
}


/*国军标CRC校验*/
unsigned short XCRC(unsigned short crc,unsigned char cp)
{
  unsigned short t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;
  
  t1 = (unsigned short)(crc >> 8);
  t2 = (unsigned short)(t1 & 0xff);
  t3 = (unsigned short)(cp & 0xff);
  t4 = (unsigned short)(crc << 8);
  t5 = (unsigned short)(t2 ^ t3);
  t6 = (unsigned short)(CRC_table[t5] ^ t4);
  return t6;
} 

unsigned short CRC_16ForRIPback( unsigned char *pData, unsigned short  nDataLen ) 
{ 
  unsigned char crc16reg = 0; 
  unsigned short nAccum = 0; 
  for (nAccum=0;nAccum<nDataLen;nAccum++)
  {
    crc16reg = XCRC(crc16reg,pData[nAccum]);
  }
  return ~crc16reg;
} 
void CRC_16ForRIP( unsigned char *pData, unsigned short  nDataLen ) 
{ 
  unsigned short crc16reg = 0; 
  unsigned short nAccum = 0; 
  for (nAccum=0;nAccum<nDataLen;nAccum++)
  {
    crc16reg = XCRC(crc16reg,pData[nAccum]);
  }
  
  pData[ nDataLen++]=~crc16reg;
  pData[ nDataLen++]=~crc16reg>>8;
} 

unsigned short CRC16Make( unsigned char* pData,unsigned short nDataLen )
{
  unsigned short crc16reg = 0xFFFF;
  for (unsigned short i=0;i<nDataLen;i++)
  {    
    crc16reg = XCRC(crc16reg,pData[i]);
  }
  return ~crc16reg;
}



unsigned char SumCheck8(unsigned char * buf,unsigned short count)
{
  unsigned char tempcount=0x00;
  for(unsigned short i=0;i<count;i++){
    tempcount+=buf[i];
  }
  return tempcount; 
}


