#ifndef M_MICRO_H
#define M_MICRO_H

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) \
    ((int)((sizeof(array) / sizeof((array)[0]))))
#endif

typedef  enum
{
	M_SUCCESS=0,
	M_FAILED,
	
}m_err_t;

#ifndef true
#define true	1
#endif

#ifndef false
#define false	0
#endif


#ifdef BIT
#undef BIT
#define BIT(n) (1UL << (n))
#else
#define BIT(n) (1UL << (n))
#endif

//#define DIFF(a,b) ((a>=b)?(a-b):(b-a))
#define DIFF(a,b) (((a) >= (b)) ? ((a) - (b)) : ((b) - (a)))

#define offset_of(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)


#define BUILD_UINT16(loByte, hiByte) \
          ((uint16_t)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define LOW_BYTE(n)		((uint8_t)(n&0xFF))

#define HIGH_BYTE(n)	((uint8_t)((n>>8)&0xFF))

#define BREAK_UINT32( var, ByteNum ) \
          (uint8_t)((uint32_t)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
          ((uint32_t)((uint32_t)((Byte0) & 0x00FF) \
          + ((uint32_t)((Byte1) & 0x00FF) << 8) \
          + ((uint32_t)((Byte2) & 0x00FF) << 16) \
          + ((uint32_t)((Byte3) & 0x00FF) << 24)))



#endif




