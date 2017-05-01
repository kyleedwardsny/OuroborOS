#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_MMU_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_MMU_H

#include <ouroboros/arch/mips/context.h>

int k_get_tlb_entries(struct tlb_entry_access *entries, ou_size_t num_entries);

int k_set_tlb_entries(const struct tlb_entry_access *entries, ou_size_t num_entries);

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_MMU_H */
