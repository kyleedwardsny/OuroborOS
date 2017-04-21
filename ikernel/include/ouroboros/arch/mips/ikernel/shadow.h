#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_SHADOW_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_SHADOW_H

#include <ouroboros/arch/mips/context.h>

void k_read_current_pss(struct ou_context *context);

void k_write_current_pss(const struct ou_context *context);

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_SHADOW_H */
