#ifndef OUROBOROS_COMMON_H
#define OUROBOROS_COMMON_H

#ifdef __GNUC__
#define GCC_PACKED	__attribute__((packed))
#else
#define GCC_PACKED
#endif

/* TODO CLang support? */
#define CLANG_PACKED

#define PACKED_STRUCT_BEGIN(name)	struct name CLANG_PACKED
#define PACKED_STRUCT_END		GCC_PACKED

#define BIT(i)		(0x1 << (i))
#define BITS(hi, lo)	((~0ULL << (lo)) & ~(~0ULL << ((hi) + 1)))

#define SWAP16(val)	((((val) & 0xFF) << 8) | (((val) & 0xFF00) >> 8))
#define SWAP32(val)	((SWAP16((val) & 0xFFFF) << 16) | SWAP16(((val) & 0xFFFF0000) >> 16))
#define SWAP64(val)	((SWAP32((val) & 0xFFFFFFFF) << 16) | SWAP32(((val) & 0xFFFFFFFF00000000) >> 32))

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

#define BTON16(val)	(val)
#define BTON32(val)	(val)
#define BTON64(val)	(val)

#define NTOB16(val)	(val)
#define NTOB32(val)	(val)
#define NTOB64(val)	(val)

#define LTON16(val)	SWAP16(val)
#define LTON32(val)	SWAP32(val)
#define LTON64(val)	SWAP64(val)

#define NTOL16(val)	SWAP16(val)
#define NTOL32(val)	SWAP32(val)
#define NTOL64(val)	SWAP64(val)

#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define BTON16(val)	SWAP16(val)
#define BTON32(val)	SWAP32(val)
#define BTON64(val)	SWAP64(val)

#define NTOB16(val)	SWAP16(val)
#define NTOB32(val)	SWAP32(val)
#define NTOB64(val)	SWAP64(val)

#define LTON16(val)	(val)
#define LTON32(val)	(val)
#define LTON64(val)	(val)

#define NTOL16(val)	(val)
#define NTOL32(val)	(val)
#define NTOL64(val)	(val)

#endif

#define ALIGN(val, align)	((val) + (align) - 1 - (((val) + (align) - 1) % (align)))

#define ARRAY_SIZE(arr)		(sizeof(arr) / sizeof(*(arr)))

#endif /* OUROBOROS_COMMON_H */
