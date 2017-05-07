#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_CONTEXT_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_CONTEXT_H

#include <ouroboros/arch/mips/common.h>

gpr_t k_get_prev_gpr(unsigned int gpr);

void k_set_prev_gpr(unsigned int gpr, gpr_t value);

void k_save_old_context(struct ou_context *context);

void k_load_new_context(const struct ou_context *context);

int k_switch_context(const struct ou_context_switch *context_switch);

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_CONTEXT_H */
