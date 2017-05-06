#include <ouroboros/ikernel/mmu.h>

#include <ouroboros/ikernel/config.h>

#include <ouroboros/arch/mips/ikernel/config.h>
#include <ouroboros/arch/mips/ikernel/mmu.h>
#include <ouroboros/arch/mips/cp0.h>

#include <ouroboros/common.h>
#include <ouroboros/errno.h>
#include <ouroboros/stddef.h>
#include <ouroboros/stdint.h>

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

static int check_entry_lo(unsigned long entry_lo)
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

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

static int check_tlb_entry(int index, const struct tlb_entry *entry)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;

	if (index >= k_num_tlb_entries) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	if ((err = check_entry_lo(entry->entry_lo0)) < 0) {
		retval = err;
		goto ret;
	}

	if ((err = check_entry_lo(entry->entry_lo1)) < 0) {
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

int k_get_tlb_entries(struct tlb_entry_access *entries, ou_size_t num_entries)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;
	ou_size_t i;
	unsigned long hi_old;
	unsigned long entry_lo0;
	unsigned long entry_lo1;
	unsigned long entry_hi;
	unsigned long page_mask;

	for (i = 0; i < num_entries; i++) {
		if (entries[i].index < 0 || entries[i].index >= k_num_tlb_entries) {
			retval = -OU_ERR_INVALID_ARGUMENT;
			goto ret;
		}

		MFC0(hi_old, MIPS_CP0_ENTRY_HO);

		MTC0(MIPS_CP0_INDEX_INDEX_INDEX(entries[i].index), MIPS_CP0_INDEX);
		TLBR();

		MFC0(entry_lo0, MIPS_CP0_ENTRY_LO0);
		MFC0(entry_lo1, MIPS_CP0_ENTRY_LO1);
		MFC0(entry_hi, MIPS_CP0_ENTRY_HO);
		MFC0(page_mask, MIPS_CP0_PAGE_MASK);

		MTC0(hi_old, MIPS_CP0_ENTRY_HO);

		entries[i].entry.entry_lo0 = entry_lo0;
		entries[i].entry.entry_lo1 = entry_lo1;
		entries[i].entry.entry_hi = entry_hi;
		entries[i].entry.page_mask = page_mask;
	}

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

int k_set_tlb_entries(const struct tlb_entry_access *entries, ou_size_t num_entries)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;
	ou_size_t i;
	unsigned long hi_old;
	unsigned long entry_lo0;
	unsigned long entry_lo1;
	unsigned long entry_hi;
	unsigned long page_mask;

	for (i = 0; i < num_entries; i++) {
		if ((err = check_tlb_entry(entries[i].index, &entries[i].entry)) < 0) {
			retval = err;
			goto ret;
		}
	}

	for (i = 0; i < num_entries; i++) {
		entry_lo0 = entries[i].entry.entry_lo0;
		entry_lo1 = entries[i].entry.entry_lo1;
		entry_hi = entries[i].entry.entry_hi;
		page_mask = entries[i].entry.page_mask;

		MFC0(hi_old, MIPS_CP0_ENTRY_HO);

		MTC0(entry_lo0, MIPS_CP0_ENTRY_LO0);
		MTC0(entry_lo1, MIPS_CP0_ENTRY_LO1);
		MTC0(entry_hi, MIPS_CP0_ENTRY_HO);
		MTC0(page_mask, MIPS_CP0_PAGE_MASK);

		if (entries[i].index < 0) { /* Random index */
			TLBWR();
		} else {
			MTC0(MIPS_CP0_INDEX_INDEX_INDEX(entries[i].index), MIPS_CP0_INDEX);
			TLBWI();
		}

		MTC0(hi_old, MIPS_CP0_ENTRY_HO);
	}

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

static int get_physical_address_single(const void *addr, unsigned int asid, ou_uint64_t *result)
{
	int retval = -OU_ERR_UNKNOWN;
	unsigned long hi;
	unsigned long lo;
	unsigned long index;

	hi = MIPS_CP0_ENTRY_HO_VPN2_VPN2((unsigned long) addr) | MIPS_CP0_ENTRY_HO_ASID_ASID(asid);
	MTC0(hi, MIPS_CP0_ENTRY_HO);
	TLBP();

	MFC0(index, MIPS_CP0_INDEX);
	if (index & MIPS_CP0_INDEX_P) {
		retval = -OU_ERR_TLB_MISS;
		goto ret;
	}

	TLBR();
	if (((unsigned long) addr) & 0x1000) {
		MFC0(lo, MIPS_CP0_ENTRY_LO1);
	} else {
		MFC0(lo, MIPS_CP0_ENTRY_LO0);
	}

	*result = ((lo & MIPS_CP0_ENTRY_LO_PFN) << 6) | ((unsigned long) addr) & 0xFFF;

ret:
	return retval;
}

int k_get_physical_address(const void *start, ou_size_t length, ou_uint64_t *result)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;
	unsigned long hi_old;
	const void *i;
	ou_uint64_t pa_prev;
	ou_uint64_t pa;

	MFC0(hi_old, MIPS_CP0_ENTRY_HO);

	if ((err = get_physical_address_single(start, hi_old & MIPS_CP0_ENTRY_HO_ASID, result)) < 0) {
		retval = err;
		goto cleanup_hi;
	}

	pa_prev = *result & ~0xFFF;
	for (i = (const void *) ((unsigned long) start & ~0xFFF) + 0x1000; i <= start + length - 1; i += 0x1000) {
		if ((err = get_physical_address_single(start, hi_old & MIPS_CP0_ENTRY_HO_ASID, &pa)) < 0) {
			retval = err;
			goto cleanup_hi;
		}

		if (pa != pa_prev + 0x1000) {
			retval = -OU_ERR_NONCONTIGUOUS_MEMORY;
			goto cleanup_hi;
		}

		pa_prev = pa;
	}

cleanup_hi:
	MTC0(hi_old, MIPS_CP0_ENTRY_HO);
ret:
	return retval;
}
