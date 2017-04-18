#ifndef KERNEL_ARCH_MIPS_CONFIG_H
#define KERNEL_ARCH_MIPS_CONFIG_H

#include <ouroboros/kernel/common.h>

CPU_LOCAL_DECLARE(unsigned int, _k_num_tlb_entries);
#define k_num_tlb_entries		CPU_LOCAL_ACCESS(_k_num_tlb_entries)

CPU_LOCAL_DECLARE(unsigned int, _k_num_shadow_sets);
#define k_num_shadow_sets		CPU_LOCAL_ACCESS(_k_num_shadow_sets)

CPU_LOCAL_DECLARE(int, _k_user_local_present);
#define k_user_local_present		CPU_LOCAL_ACCESS(_k_user_local_present)

CPU_LOCAL_DECLARE(unsigned int, _k_entry_policy);
#define k_entry_policy			CPU_LOCAL_ACCESS(_k_entry_policy)

CPU_LOCAL_DECLARE(unsigned int, _k_available_entry_policies);
#define k_available_entry_policies	CPU_LOCAL_ACCESS(_k_available_entry_policies)

#endif /* KERNEL_ARCH_MIPS_CONFIG_H */
