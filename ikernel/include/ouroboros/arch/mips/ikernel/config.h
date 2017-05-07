#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_CONFIG_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_CONFIG_H

#include <ouroboros/ikernel/common.h>

#include <ouroboros/arch/mips/ikernel/entry.h>

CPU_LOCAL_DECLARE(unsigned int, _k_num_tlb_entries);
#define k_num_tlb_entries		CPU_LOCAL_ACCESS(_k_num_tlb_entries)

CPU_LOCAL_DECLARE(unsigned int, _k_num_shadow_sets);
#define k_num_shadow_sets		CPU_LOCAL_ACCESS(_k_num_shadow_sets)

CPU_LOCAL_DECLARE(int, _k_user_local_present);
#define k_user_local_present		CPU_LOCAL_ACCESS(_k_user_local_present)

CPU_LOCAL_DECLARE(int, _k_scratch_present);
#define k_scratch_present		CPU_LOCAL_ACCESS(_k_scratch_present)

typedef void (*k_exit_fn)(void);

CPU_LOCAL_DECLARE(k_exit_fn, _k_exit_function);
#define k_exit_function			CPU_LOCAL_ACCESS(_k_exit_function)

static inline void k_exit_no_shadow(void)
{
	k_exit_function();
}

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_CONFIG_H */
