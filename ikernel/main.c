#include <ouroboros/common.h>

#include <ouroboros/ikernel/config.h>
#include <ouroboros/ikernel/main.h>
#include <ouroboros/ikernel/mmu.h>

#include <ouroboros/stdio.h>
#include <ouroboros/stdint.h>
#include <ouroboros/stdlib.h>
#include <ouroboros/string.h>

#include <libfdt.h>

void k_entry(void)
{
	/* TODO */
}

void k_main(const void *fdt)
{
	k_read_cpu_config();
	k_clear_tlb();

	/* TODO */
}
