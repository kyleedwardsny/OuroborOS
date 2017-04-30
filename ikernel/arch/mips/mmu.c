#include <ouroboros/ikernel/mmu.h>

#include <ouroboros/ikernel/config.h>

#include <ouroboros/arch/mips/ikernel/config.h>
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

static int check_entry_lo_validity(unsigned long entry_lo)
{
	int retval = -OU_ERR_UNKNOWN;

	if (entry_lo & BITS(31, 26)) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	switch (entry_lo & MIPS_CP0_ENTRY_LO_C) {
	case MIPS_CP0_ENTRY_LO_C_C(MIPS_CP0_CACHE_ATTR_CNWTNA):
	case MIPS_CP0_ENTRY_LO_C_C(MIPS_CP0_CACHE_ATTR_U):
	case MIPS_CP0_ENTRY_LO_C_C(MIPS_CP0_CACHE_ATTR_CNWBA):
	case MIPS_CP0_ENTRY_LO_C_C(MIPS_CP0_CACHE_ATTR_UA):
		break;

	default:
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	retval -OU_ERR_SUCCESS;
ret:
	return retval;
}

static int check_tlb_entry_validity(int index, const struct tlb_entry *entry)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;

	if (index >= k_num_tlb_entries) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	if ((err = check_entry_lo_validity(entry->entry_lo0)) < 0) {
		retval = err;
		goto ret;
	}

	if ((err = check_entry_lo_validity(entry->entry_lo1)) < 0) {
		retval = err;
		goto ret;
	}

	if (entry->entry_hi & BITS(12, 8)) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	switch (entry->page_mask & MIPS_CP0_PAGE_MASK_MASK) {
	case MIPS_CP0_PAGE_MASK_MASK_4K:
	case MIPS_CP0_PAGE_MASK_MASK_16K:
	case MIPS_CP0_PAGE_MASK_MASK_64K:
	case MIPS_CP0_PAGE_MASK_MASK_256K:
	case MIPS_CP0_PAGE_MASK_MASK_1M:
	case MIPS_CP0_PAGE_MASK_MASK_4M:
	case MIPS_CP0_PAGE_MASK_MASK_16M:
	case MIPS_CP0_PAGE_MASK_MASK_64M:
	case MIPS_CP0_PAGE_MASK_MASK_256M:
		break;

	default:
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

int k_get_tlb_entry(int index, struct tlb_entry *entry)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;
	unsigned long hi_old;
	unsigned long entry_lo0;
	unsigned long entry_lo1;
	unsigned long entry_hi;
	unsigned long page_mask;

	if (index < 0 || index >= k_num_tlb_entries) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	MFC0(hi_old, MIPS_CP0_ENTRY_HO);

	MTC0(MIPS_CP0_INDEX_INDEX_INDEX(index), MIPS_CP0_INDEX);
	TLBR();

	MFC0(entry_lo0, MIPS_CP0_ENTRY_LO0);
	MFC0(entry_lo1, MIPS_CP0_ENTRY_LO1);
	MFC0(entry_hi, MIPS_CP0_ENTRY_HO);
	MFC0(page_mask, MIPS_CP0_PAGE_MASK);

	MTC0(hi_old, MIPS_CP0_ENTRY_HO);

	entry->entry_lo0 = entry_lo0;
	entry->entry_lo1 = entry_lo1;
	entry->entry_hi = entry_hi;
	entry->page_mask = page_mask;

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

int k_set_tlb_entry(int index, const struct tlb_entry *entry)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;
	unsigned long hi_old;
	unsigned long entry_lo0;
	unsigned long entry_lo1;
	unsigned long entry_hi;
	unsigned long page_mask;

	if ((err = check_tlb_entry_validity(index, entry)) < 0) {
		retval = err;
		goto ret;
	}

	entry_lo0 = entry->entry_lo0;
	entry_lo1 = entry->entry_lo1;
	entry_hi = entry->entry_hi;
	page_mask = entry->page_mask;

	MFC0(hi_old, MIPS_CP0_ENTRY_HO);

	MTC0(entry_lo0, MIPS_CP0_ENTRY_LO0);
	MTC0(entry_lo1, MIPS_CP0_ENTRY_LO1);
	MTC0(entry_hi, MIPS_CP0_ENTRY_HO);
	MTC0(page_mask, MIPS_CP0_PAGE_MASK);

	if (index < 0) { /* Random index */
		TLBWR();
	} else {
		MTC0(MIPS_CP0_INDEX_INDEX_INDEX(index), MIPS_CP0_INDEX);
		TLBWI();
	}

	MTC0(hi_old, MIPS_CP0_ENTRY_HO);

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}
