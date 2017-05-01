#include <ouroboros/common.h>

#include <ouroboros/arch/mips/context.h>

#define TLB_ENTRY_ACCESS(i)	\
{				\
	.index = (i),		\
}

#define TLB_ENTRY_ACCESS_8(i)	\
TLB_ENTRY_ACCESS((i) + 0),	\
TLB_ENTRY_ACCESS((i) + 1),	\
TLB_ENTRY_ACCESS((i) + 2),	\
TLB_ENTRY_ACCESS((i) + 3),	\
TLB_ENTRY_ACCESS((i) + 4),	\
TLB_ENTRY_ACCESS((i) + 5),	\
TLB_ENTRY_ACCESS((i) + 6),	\
TLB_ENTRY_ACCESS((i) + 7)	\

struct tlb_entry_access tlb_read_data[64] __attribute__((section(".data.early"))) = {
	TLB_ENTRY_ACCESS_8(0),
	TLB_ENTRY_ACCESS_8(8),
	TLB_ENTRY_ACCESS_8(16),
	TLB_ENTRY_ACCESS_8(24),
	TLB_ENTRY_ACCESS_8(32),
	TLB_ENTRY_ACCESS_8(40),
	TLB_ENTRY_ACCESS_8(48),
	TLB_ENTRY_ACCESS_8(56),
};

#undef TLB_ENTRY_ACCESS_8
#undef TLB_ENTRY_ACCESS

ou_size_t tlb_read_data_num_entries __attribute__((section(".data.early"))) = ARRAY_SIZE(tlb_read_data);
