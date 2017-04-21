#ifndef OUROBOROS_ARCH_MIPS_ASM_H
#define OUROBOROS_ARCH_MIPS_ASM_H

#include <ouroboros/common.h>

#define MIPS_CP_STR(r, s)	CPP_STR(r) ", " CPP_STR(s)

#define MTC0_R(expr, reg, select)									\
do {													\
	__asm__ volatile("mtc0 %[mips_reg], " MIPS_CP_STR(reg, select) : : [mips_reg] "r" (expr));	\
} while (0)

#define MTC0(expr, reg)		MTC0_R(expr, reg)

#define MFC0_R(var, reg, select)									\
do {													\
	__asm__ volatile("mfc0 %[mips_reg], " MIPS_CP_STR(reg, select) : [mips_reg] "=r" (var) :);	\
} while (0)

#define MFC0(var, reg)		MFC0_R(var, reg)

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

#define RDPGPR(var, reg)									\
do {												\
	__asm__ volatile("rdpgpr %[mips_reg], " CPP_STR(reg) : [mips_reg] "=r" (var) :);	\
} while (0)

#define WRPGPR(expr, reg)										\
do {													\
	__asm__ volatile("wrpgpr %[mips_reg], " CPP_STR(reg) : : [mips_reg] "r" (expr) :);	\
} while (0)

#endif /* OUROBOROS_ARCH_MIPS_ASM_H */
