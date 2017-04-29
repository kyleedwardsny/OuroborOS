#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_MMU_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_MMU_H

#include <ouroboros/arch/mips/context.h>

int k_get_tlb_entry(int index, struct tlb_entry *entry);

int k_set_tlb_entry(int index, const struct tlb_entry *entry);

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_MMU_H */
