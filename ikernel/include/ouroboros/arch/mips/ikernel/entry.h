#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_ENTRY_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_ENTRY_H

#include <ouroboros/ikernel/common.h>

#define k_regstore	CPU_LOCAL_ACCESS(_k_regstore)

#ifndef __ASSEMBLER__

CPU_LOCAL_DECLARE(struct mips_regstore, _k_regstore);

void k_exit_k0_k1(void);

void k_exit_k0_rotr(void);

void k_exit_k1_rotr(void);

void k_exit_k0_ul(void);

void k_exit_k1_ul(void);

void k_exit_ul_rotr(void);

void k_exit_shadow(void);

static inline unsigned int k_get_current_cpu()
{
	gpr_u_t ebase;

	MFC0(ebase, MIPS_CP0_EBASE);
	return (ebase & MIPS_CP0_EBASE_CPUNUM) >> 0;
}

#endif /* __ASSEMBLER__ */

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_ENTRY_H */
