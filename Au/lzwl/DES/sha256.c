#include "sha256.h"
#include "string.h"


/*******************************************************************************
*
*�� ����SHA256_Starts( )
*�� �ܣ�
*�� �룺
*�� ����
*�� �ߣ�WGS
*ʱ �䣺2019.03.07
*�� ע��
*
********************************************************************************/
void SHA256_Starts(sha256_context *ctx)
{
	ctx->total[0] = 0;
	ctx->total[1] = 0;
	
	ctx->state[0] = 0x6A09E667;
	ctx->state[1] = 0xBB67AE85;
	ctx->state[2] = 0x3C6EF372;
	ctx->state[3] = 0xA54FF53A;
	ctx->state[4] = 0x510E527F;
	ctx->state[5] = 0x9B05688C;
	ctx->state[6] = 0x1F83D9AB;
	ctx->state[7] = 0x5BE0CD19;
}


/*******************************************************************************
*
*�� ����SHA256_Process( )
*�� �ܣ�
*�� �룺
*�� ����
*�� �ߣ�WGS
*ʱ �䣺2019.03.07
*�� ע��
*
********************************************************************************/
void SHA256_Process(sha256_context *ctx, uint8_t *pData)
{
	uint32_t temp1, temp2;
	uint32_t A, B, C, D, E, F, G, H;
	uint32_t W[64]={0};
	
	SHA256_GET_UINT32( W[0],  pData,  0 );
	SHA256_GET_UINT32( W[1],  pData,  4 );
	SHA256_GET_UINT32( W[2],  pData,  8 );
	SHA256_GET_UINT32( W[3],  pData, 12 );
	SHA256_GET_UINT32( W[4],  pData, 16 );
	SHA256_GET_UINT32( W[5],  pData, 20 );
	SHA256_GET_UINT32( W[6],  pData, 24 );
	SHA256_GET_UINT32( W[7],  pData, 28 );
	SHA256_GET_UINT32( W[8],  pData, 32 );
	SHA256_GET_UINT32( W[9],  pData, 36 );
	SHA256_GET_UINT32( W[10], pData, 40 );
	SHA256_GET_UINT32( W[11], pData, 44 );
	SHA256_GET_UINT32( W[12], pData, 48 );
	SHA256_GET_UINT32( W[13], pData, 52 );
	SHA256_GET_UINT32( W[14], pData, 56 );
	SHA256_GET_UINT32( W[15], pData, 60 );
	
	#define  SHR(x,n) ((x & 0xFFFFFFFF) >> n)
	#define ROTR(x,n) (SHR(x,n) | (x << (32 - n)))
		
	#define S0(x) (ROTR(x, 7) ^ ROTR(x,18) ^  SHR(x, 3))
	#define S1(x) (ROTR(x,17) ^ ROTR(x,19) ^  SHR(x,10))
		
	#define S2(x) (ROTR(x, 2) ^ ROTR(x,13) ^ ROTR(x,22))
	#define S3(x) (ROTR(x, 6) ^ ROTR(x,11) ^ ROTR(x,25))
		
	#define F0(x,y,z) ((x & y) | (z & (x | y)))
	#define F1(x,y,z) (z ^ (x & (y ^ z)))
	
	#define R(t)  (W[t] = S1(W[t - 2]) + W[t - 7] + S0(W[t -15]) + W[t - 16])
		
	#define P(a,b,c,d,e,f,g,h,x,K)            \
	{                                         \
	  temp1 = h + S3(e) + F1(e,f,g) + K + x;  \
		temp2 = S2(a) + F0(a,b,c);              \
		d += temp1; 														\
		h = temp1 + temp2;                      \
	}
	A = ctx->state[0];
	B = ctx->state[1];
	C = ctx->state[2];
	D = ctx->state[3];
	E = ctx->state[4];
	F = ctx->state[5];
	G = ctx->state[6];
	H = ctx->state[7];
	
	P( A, B, C, D, E, F, G, H, W[ 0], 0x428A2F98 );
	P( H, A, B, C, D, E, F, G, W[ 1], 0x71374491 );
	P( G, H, A, B, C, D, E, F, W[ 2], 0xB5C0FBCF );
	P( F, G, H, A, B, C, D, E, W[ 3], 0xE9B5DBA5 );
	P( E, F, G, H, A, B, C, D, W[ 4], 0x3956C25B );
	P( D, E, F, G, H, A, B, C, W[ 5], 0x59F111F1 );
	P( C, D, E, F, G, H, A, B, W[ 6], 0x923F82A4 );
	P( B, C, D, E, F, G, H, A, W[ 7], 0xAB1C5ED5 );
	P( A, B, C, D, E, F, G, H, W[ 8], 0xD807AA98 );
	P( H, A, B, C, D, E, F, G, W[ 9], 0x12835B01 );
	P( G, H, A, B, C, D, E, F, W[10], 0x243185BE );
	P( F, G, H, A, B, C, D, E, W[11], 0x550C7DC3 );
	P( E, F, G, H, A, B, C, D, W[12], 0x72BE5D74 );
	P( D, E, F, G, H, A, B, C, W[13], 0x80DEB1FE );
	P( C, D, E, F, G, H, A, B, W[14], 0x9BDC06A7 );
	P( B, C, D, E, F, G, H, A, W[15], 0xC19BF174 );
	P( A, B, C, D, E, F, G, H, R(16), 0xE49B69C1 );
	P( H, A, B, C, D, E, F, G, R(17), 0xEFBE4786 );
	P( G, H, A, B, C, D, E, F, R(18), 0x0FC19DC6 );
	P( F, G, H, A, B, C, D, E, R(19), 0x240CA1CC );
	P( E, F, G, H, A, B, C, D, R(20), 0x2DE92C6F );
	P( D, E, F, G, H, A, B, C, R(21), 0x4A7484AA );
	P( C, D, E, F, G, H, A, B, R(22), 0x5CB0A9DC );
	P( B, C, D, E, F, G, H, A, R(23), 0x76F988DA );
	P( A, B, C, D, E, F, G, H, R(24), 0x983E5152 );
	P( H, A, B, C, D, E, F, G, R(25), 0xA831C66D );
	P( G, H, A, B, C, D, E, F, R(26), 0xB00327C8 );
	P( F, G, H, A, B, C, D, E, R(27), 0xBF597FC7 );
	P( E, F, G, H, A, B, C, D, R(28), 0xC6E00BF3 );
	P( D, E, F, G, H, A, B, C, R(29), 0xD5A79147 );
	P( C, D, E, F, G, H, A, B, R(30), 0x06CA6351 );
	P( B, C, D, E, F, G, H, A, R(31), 0x14292967 );
	P( A, B, C, D, E, F, G, H, R(32), 0x27B70A85 );
	P( H, A, B, C, D, E, F, G, R(33), 0x2E1B2138 );
	P( G, H, A, B, C, D, E, F, R(34), 0x4D2C6DFC );
	P( F, G, H, A, B, C, D, E, R(35), 0x53380D13 );
	P( E, F, G, H, A, B, C, D, R(36), 0x650A7354 );
	P( D, E, F, G, H, A, B, C, R(37), 0x766A0ABB );
	P( C, D, E, F, G, H, A, B, R(38), 0x81C2C92E );
	P( B, C, D, E, F, G, H, A, R(39), 0x92722C85 );
	P( A, B, C, D, E, F, G, H, R(40), 0xA2BFE8A1 );
	P( H, A, B, C, D, E, F, G, R(41), 0xA81A664B );
	P( G, H, A, B, C, D, E, F, R(42), 0xC24B8B70 );
	P( F, G, H, A, B, C, D, E, R(43), 0xC76C51A3 );
	P( E, F, G, H, A, B, C, D, R(44), 0xD192E819 );
	P( D, E, F, G, H, A, B, C, R(45), 0xD6990624 );
	P( C, D, E, F, G, H, A, B, R(46), 0xF40E3585 );
	P( B, C, D, E, F, G, H, A, R(47), 0x106AA070 );
	P( A, B, C, D, E, F, G, H, R(48), 0x19A4C116 );
	P( H, A, B, C, D, E, F, G, R(49), 0x1E376C08 );
	P( G, H, A, B, C, D, E, F, R(50), 0x2748774C );
	P( F, G, H, A, B, C, D, E, R(51), 0x34B0BCB5 );
	P( E, F, G, H, A, B, C, D, R(52), 0x391C0CB3 );
	P( D, E, F, G, H, A, B, C, R(53), 0x4ED8AA4A );
	P( C, D, E, F, G, H, A, B, R(54), 0x5B9CCA4F );
	P( B, C, D, E, F, G, H, A, R(55), 0x682E6FF3 );
	P( A, B, C, D, E, F, G, H, R(56), 0x748F82EE );
	P( H, A, B, C, D, E, F, G, R(57), 0x78A5636F );
	P( G, H, A, B, C, D, E, F, R(58), 0x84C87814 );
	P( F, G, H, A, B, C, D, E, R(59), 0x8CC70208 );
	P( E, F, G, H, A, B, C, D, R(60), 0x90BEFFFA );
	P( D, E, F, G, H, A, B, C, R(61), 0xA4506CEB );
	P( C, D, E, F, G, H, A, B, R(62), 0xBEF9A3F7 );
	P( B, C, D, E, F, G, H, A, R(63), 0xC67178F2 );
	
	ctx->state[0] += A;
	ctx->state[1] += B;
	ctx->state[2] += C;
	ctx->state[3] += D;
	ctx->state[4] += E;
	ctx->state[5] += F;
	ctx->state[6] += G;
	ctx->state[7] += H;
}

/*******************************************************************************
*
*�� ����SHA256_update( )
*�� �ܣ�SHA256ɢ�����
*�� �룺
*�� ����
*�� �ߣ�WGS
*ʱ �䣺2019.03.07
*�� ע��
*
********************************************************************************/
void SHA256_Update(sha256_context *ctx, uint8_t *input, uint16_t len)
{
	uint32_t left, fill;
	
	if(!len) return;  
	left = ctx->total[0] & 0x3F;         
	fill = 64 - left;
	
	ctx->total[0] += len;  
	ctx->total[0] &= 0xFFFFFFFF;	
	if( ctx->total[0] < len )
		ctx->total[1]++;
	if( left && (len >= fill))
	{
		memcpy((ctx->buffer + left),input,fill);
		SHA256_Process(ctx, ctx->buffer);
		len -= fill;
		input  += fill;
		left = 0;
	}
	while(len >= 64 )
	{
		SHA256_Process( ctx, input );
		len -= 64;
		input  += 64;
	}
	if(len)
		memcpy((ctx->buffer + left),input,len);
}

static const uint8_t sha256_padding[64] =
{
 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
/*******************************************************************************
*
*�� ����SHA256_Finish( )
*�� �ܣ�SHA256ɢ�����
*�� �룺
*�� ����
*�� �ߣ�WGS
*ʱ �䣺2019.03.07
*�� ע��
*
********************************************************************************/
void SHA256_Finish(sha256_context *ctx, uint8_t *digest)
{
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t  msglen[8];

    high = ( ctx->total[0] >> 29 )|(ctx->total[1] <<  3);
    low  = ( ctx->total[0] <<  3 );
    SHA256_PUT_UINT32(high,msglen, 0 );
    SHA256_PUT_UINT32(low, msglen, 4 );
    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last ) : (120 - last);
    SHA256_Update( ctx,(uint8_t*)sha256_padding, padn);
    SHA256_Update( ctx, msglen, 8 );
    SHA256_PUT_UINT32(ctx->state[0], digest,  0 );
    SHA256_PUT_UINT32(ctx->state[1], digest,  4 );
    SHA256_PUT_UINT32(ctx->state[2], digest,  8 );
    SHA256_PUT_UINT32(ctx->state[3], digest, 12 );
    SHA256_PUT_UINT32(ctx->state[4], digest, 16 );
    SHA256_PUT_UINT32(ctx->state[5], digest, 20 );
    SHA256_PUT_UINT32(ctx->state[6], digest, 24 );
    SHA256_PUT_UINT32(ctx->state[7], digest, 28 );
}
