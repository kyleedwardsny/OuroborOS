#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_ENTRY_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_ENTRY_H

#include <ouroboros/ikernel/common.h>
#include <ouroboros/arch/mips/context.h>

#define k_context	CPU_LOCAL_ACCESS(_k_context)

#ifndef __ASSEMBLER__

CPU_LOCAL_DECLARE(struct ou_context, _k_context);

void k_exit_standard(void);
void k_exit_scratch(void);
void k_exit_shadow(void);

void k_evt_standard(void);
void k_evt_scratch(void);
void k_evt_shadow(void);

static inline unsigned int k_get_current_cpu()
{
	gpr_u_t ebase;

	MFC0(ebase, MIPS_CP0_EBASE);
	return (ebase & MIPS_CP0_EBASE_CPUNUM) >> 0;
}

#endif /* __ASSEMBLER__ */

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_ENTRY_H */
