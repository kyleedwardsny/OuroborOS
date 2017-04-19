#ifndef OUROBOROS_IKERNEL_MAIN_H
#define OUROBOROS_IKERNEL_MAIN_H

#include <ouroboros/arch/current/context.h>

void k_main(const void *fdt);

void k_do_syscall(struct ou_context *context,
		unsigned long index,
		unsigned long arg0,
		unsigned long arg1,
		unsigned long arg2,
		unsigned long arg3,
		unsigned long arg4,
		unsigned long arg5,
		unsigned long arg6,
		unsigned long arg7);

void k_exit(void);

#endif /* OUROBOROS_IKERNEL_MAIN_H */
