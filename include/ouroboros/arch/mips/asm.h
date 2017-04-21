#ifndef OUROBOROS_ARCH_MIPS_ASM_H
#define OUROBOROS_ARCH_MIPS_ASM_H

#include <ouroboros/common.h>

#define MIPS_CP_STR(r, s)	CPP_STR(r) ", " CPP_STR(s)

#define MTC0(expr, reg)										\
do {												\
	__asm__ volatile("mtc0 %[mips_reg], " MIPS_CP_STR(reg) : : [mips_reg] "r" (expr));	\
} while (0)

#define MFC0(var, reg)										\
do {												\
	__asm__ volatile("mfc0 %[mips_reg], " MIPS_CP_STR(reg) : [mips_reg] "=r" (var) :);	\
} while (0)

#define TLBR()				\
do {					\
	__asm__ volatile("tlbr" : :);	\
} while (0)

#define TLBWI()				\
do {					\
	__asm__ volatile("tlbwi" : :);	\
} while (0)

#define TLBWR()				\
do {					\
	__asm__ volatile("tlbwr" : :);	\
} while (0)

#define TLBP()				\
do {					\
	__asm__ volatile("tlbp" : :);	\
} while (0)

#define MTHI(expr)							\
do {									\
	__asm__ volatile("mthi %[mips_reg]" : : [mips_reg] "r" (expr));	\
} while (0)

#define MFHI(var)							\
do {									\
	__asm__ volatile("mfhi %[mips_reg]" : [mips_reg] "=r" (var) :);	\
} while (0)

#define MTLO(expr)							\
do {									\
	__asm__ volatile("mtlo %[mips_reg]" : : [mips_reg] "r" (expr));	\
} while (0)

#define MFLO(var)							\
do {									\
	__asm__ volatile("mflo %[mips_reg]" : [mips_reg] "=r" (var) :);	\
} while (0)

#endif /* OUROBOROS_ARCH_MIPS_ASM_H */
