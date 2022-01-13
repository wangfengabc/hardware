#ifndef __DES_H__
#define __DES_H__

#include "compiler.h"

/*
*DES
*/
typedef struct
{
  U32 esk[32];     //加密子秘钥
  U32 dsk[32];     //解密子秘钥
  
}des_context;

/*
*3DES
*/
typedef struct
{
  U32 esk[96];     /* Triple-DES encryption subkeys */
  U32 dsk[96];     /* Triple-DES decryption subkeys */
	
}des3_context;

//函数声明
U8 DES_Encrypt(U8* pKey,U8* pInput,U8 uInputSize,U8* pOut);
U8 DES_Decrypt(U8 *pKey,U8* pInput,U8 uInputSize,U8* pOut);
uint8_t LZWL_DES_TripleDecrypt(U8 *pKey,U8* pInput,U8 uInputSize,U8* pOut);
uint8_t LZWL_DES_TripleEncrypt(U8 *pKey,U8* pInput,U8 uInputSize,U8* pOut);

#endif 