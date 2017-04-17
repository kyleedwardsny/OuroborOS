#ifndef OUROBOROS_ARCH_MIPS_SHADOW_H
#define OUROBOROS_ARCH_MIPS_SHADOW_H

#include <ouroboros/arch/mips/common.h>

void k_read_current_pss(struct mips_regstore *regstore);

void k_write_current_pss(const struct mips_regstore *regstore);

#define mips_reg_xstr(r)	mips_reg_str(r)
#define mips_reg_str(r)		#r

#define RDPGPR(var, reg)									\
do {												\
	__asm__ volatile("rdpgpr %[mips_reg], " mips_reg_xstr(reg) : [mips_reg] "=r" (var) :);	\
} while (0)

#define WRPGPR(expr, reg)										\
do {													\
	__asm__ volatile("wrpgpr %[mips_reg], " mips_reg_xstr(reg) : : [mips_reg] "r" (expr) :);	\
} while (0)

#endif /* OUROBOROS_ARCH_MIPS_SHADOW_H */
