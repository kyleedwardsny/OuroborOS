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

#endif /* OUROBOROS_COMMON_H */
