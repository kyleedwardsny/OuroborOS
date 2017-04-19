#include <ouroboros/common.h>

#include <ouroboros/ikernel/config.h>
#include <ouroboros/ikernel/main.h>
#include <ouroboros/ikernel/mmu.h>

#include <ouroboros/stdio.h>
#include <ouroboros/stdint.h>
#include <ouroboros/stdlib.h>
#include <ouroboros/string.h>

#include <libfdt.h>

void k_main(const void *fdt)
{
	k_read_cpu_config();
	k_clear_tlb();

	/* TODO */
}

void k_do_syscall(struct ou_context *context,
		unsigned long index,
		unsigned long arg0,
		unsigned long arg1,
		unsigned long arg2,
		unsigned long arg3,
		unsigned long arg4,
		unsigned long arg5,
		unsigned long arg6,
		unsigned long arg7)
{
}
