#ifndef OUROBOROS_IKERNEL_CONTEXT_H
#define OUROBOROS_IKERNEL_CONTEXT_H

#include <ouroboros/arch/current/context.h>

void k_save_old_context(const struct ou_context_mask *mask, struct ou_context *context);

void k_load_new_context(const struct ou_context_mask *mask, const struct ou_context *context);

#endif /* OUROBOROS_IKERNEL_CONTEXT_H */
