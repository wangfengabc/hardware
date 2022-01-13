#ifndef __SHA256_H__
#define __SHA256_H__
#include <stdint.h>
typedef struct
{
  uint32_t total[2];
  uint32_t state[8];
  uint8_t  buffer[64];
	
}sha256_context;

#define SHA256_GET_UINT32(n,b,i)        \
{                                       \
	(n) = ( (uint32_t) (b)[(i)    ] << 24 )    \
		  | ( (uint32_t) (b)[(i) + 1] << 16 )    \
			| ( (uint32_t) (b)[(i) + 2] <<  8 )    \
			| ( (uint32_t) (b)[(i) + 3]       );   \
}

#define SHA256_PUT_UINT32(n,b,i)        \
{                                       \
	(b)[(i)    ] = (uint8_t) ( (n) >> 24 );    \
	(b)[(i) + 1] = (uint8_t) ( (n) >> 16 );    \
	(b)[(i) + 2] = (uint8_t) ( (n) >>  8 );    \
	(b)[(i) + 3] = (uint8_t) ( (n)       );    \
}


//º¯ÊýÉùÃ÷
void SHA256_Starts(sha256_context *ctx);
void SHA256_Update(sha256_context *ctx, uint8_t *input, uint16_t len);
void SHA256_Finish(sha256_context *ctx, uint8_t *digest);
extern const short CRC_table[256];
#endif 
