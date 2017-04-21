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

CPU_LOCAL_DECLARE(unsigned int, _k_entry_policy);
#define k_entry_policy			CPU_LOCAL_ACCESS(_k_entry_policy)

CPU_LOCAL_DECLARE(unsigned int, _k_available_entry_policies);
#define k_available_entry_policies	CPU_LOCAL_ACCESS(_k_available_entry_policies)

typedef void (*k_exit_fn)(void);

CPU_LOCAL_DECLARE(k_exit_fn, _k_exit_policy);
#define k_exit_policy			CPU_LOCAL_ACCESS(_k_exit_policy)

int k_set_entry_policy(unsigned int entry_policy);

/* EVT entries */
void k_evt_k0_k1(void);
void k_evt_k0_rotr(void);
void k_evt_k1_rotr(void);
void k_evt_k0_ul(void);
void k_evt_k1_ul(void);
void k_evt_ul_rotr(void);
void k_evt_shadow(void);

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_CONFIG_H */
