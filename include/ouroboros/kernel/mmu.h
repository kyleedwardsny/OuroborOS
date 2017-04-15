#ifndef OUROBOROS_KERNEL_MMU_H
#define OUROBOROS_KERNEL_MMU_H

#include <ouroboros/stddef.h>

int k_reserve_mem(const void *start, ou_size_t size);

int k_check_reserved_mem(const void *start, ou_size_t size);

void k_clear_tlb(void);

#endif /* OUROBOROS_KERNEL_MMU_H */
