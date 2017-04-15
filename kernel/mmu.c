#include <ouroboros/kernel/mmu.h>

#include <ouroboros/kernel/config.h>

#include <ouroboros/arch/mips/cp0.h>

#include <ouroboros/common.h>
#include <ouroboros/errno.h>
#include <ouroboros/stddef.h>

int _kernel_begin;
int _kernel_size;

struct reserved_mem {
	const void *start;
	ou_size_t size;
};

static struct reserved_mem reserved_mem[64] = {
	[0] = {
		.start = &_kernel_begin,
		.size = (ou_size_t) &_kernel_size,
	},
};

static ou_size_t reserved_mem_entries = 1;

int k_reserve_mem(const void *start, ou_size_t size)
{
	int retval = -OU_ERR_UNKNOWN;

	if (reserved_mem_entries >= ARRAY_SIZE(reserved_mem)) {
		retval = -OU_ERR_NO_MEMORY;
		goto ret;
	}

	reserved_mem[reserved_mem_entries].start = start;
	reserved_mem[reserved_mem_entries].size = size;
	reserved_mem_entries++;

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

int k_check_reserved_mem(const void *start, ou_size_t size)
{
	int retval = -OU_ERR_UNKNOWN;
	ou_size_t i;

	for (i = 0; i < reserved_mem_entries; i++) {
		if (reserved_mem[i].start <= start && start < reserved_mem[i].start + reserved_mem[i].size) {
			retval = -OU_ERR_NO_MEMORY;
			goto ret;
		} else if (start <= reserved_mem[i].start && reserved_mem[i].start < start + size) {
			retval = -OU_ERR_NO_MEMORY;
			goto ret;
		}
	}

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

void k_clear_tlb(void)
{
	unsigned int i;

	for (i = 0; i < k_num_tlb_entries; i++) {
		MTC0(MIPS_CP0_INDEX_INDEX_INDEX(i), MIPS_CP0_INDEX);
		MTC0(0, MIPS_CP0_ENTRY_LO0);
		MTC0(0, MIPS_CP0_ENTRY_LO1);
		MTC0(0, MIPS_CP0_ENTRY_HO);
		MTC0(MIPS_CP0_PAGE_MASK_MASK_4K, MIPS_CP0_PAGE_MASK);
		TLBWI();
	}
}
