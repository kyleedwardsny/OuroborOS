#include <ouroboros/ikernel/main.h>
#include <ouroboros/ikernel/eat_self.h>

#include <ouroboros/arch/mips/ikernel/config.h>
#include <ouroboros/arch/mips/ikernel/entry.h>
#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/context.h>

#include <ouroboros/errno.h>
#include <ouroboros/stdint.h>
#include <ouroboros/string.h>

CPU_LOCAL_DEFINE(struct mips_regstore, _k_regstore) __attribute__((section(".bss.regstore")));

void k_main_args(unsigned long arg0, unsigned long arg1, unsigned long arg2)
{
	const void *fdt;

	switch (arg0) {
	case -2:
		fdt = (const void *) arg1;
		k_main(fdt);

	default:
		k_hang();
	}
}

void k_entry(void)
{
	ou_uint32_t cause;
	struct ou_context context;

	ou_memcpy(&context.registers, &k_regstore, sizeof(context.registers));

	MFC0(cause, MIPS_CP0_CAUSE);

	switch (cause & MIPS_CP0_CAUSE_EXC) {
	case MIPS_CP0_CAUSE_EXC_SYS:
		k_do_syscall(&context,
				context.registers.gpr_2.u,	/* $v0 = index */
				context.registers.gpr_4.u,	/* $a0 = argument 0 */
				context.registers.gpr_5.u,	/* $a1 = argument 1 */
				context.registers.gpr_6.u,	/* $a2 = argument 2 */
				context.registers.gpr_7.u,	/* $a3 = argument 3 */
				context.registers.gpr_16.u,	/* $s0 = argument 4 */
				context.registers.gpr_17.u,	/* $s1 = argument 4 */
				context.registers.gpr_18.u,	/* $s2 = argument 4 */
				context.registers.gpr_19.u);	/* $s3 = argument 4 */
		break;
	}
}

void k_exit(void)
{
	k_exit_policy();
}

int k_enter_initrd(void *start, void *end, void *load_addr, void *entry_addr)
{
	int retval = -OU_ERR_UNKNOWN;
	ou_size_t length = end - start;
	ou_uint32_t index;
	ou_uint32_t entry_lo;
	ou_uint32_t entry_ho;
	struct ou_context_mask context_mask;
	struct ou_context context;
	ou_size_t i;

	if (!IS_PAGE_ALIGNED((ou_size_t) start) || !IS_PAGE_ALIGNED((ou_size_t) load_addr)) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	if (entry_addr < load_addr || entry_addr >= load_addr + PAGE_SIZE) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	index = (k_num_tlb_entries - 1) & MIPS_CP0_INDEX_INDEX;
	MTC0(index, MIPS_CP0_INDEX);

	entry_lo = MIPS_CP0_ENTRY_LO_PFN_PFN(((ou_size_t) start) & ~0xC0000000) | MIPS_CP0_ENTRY_LO_C_C(MIPS_CP0_CACHE_ATTR_U) | MIPS_CP0_ENTRY_LO_D | MIPS_CP0_ENTRY_LO_V;
	MTC0(entry_lo, MIPS_CP0_ENTRY_LO0);
	entry_ho = MIPS_CP0_ENTRY_HO_VPN2_VPN2((ou_size_t) load_addr) | MIPS_CP0_ENTRY_HO_ASID_ASID(1);
	MTC0(entry_ho, MIPS_CP0_ENTRY_HO);
	MTC0(MIPS_CP0_PAGE_MASK_MASK_4K, MIPS_CP0_PAGE_MASK);

	TLBWI();

	context_mask.flags0 = MIPS_CONTEXT_MASK_0_ASID | MIPS_CONTEXT_MASK_0_HI | MIPS_CONTEXT_MASK_0_LO;
	context_mask.reg_mask = BITS(31, 0);

	context.registers.pc = entry_addr;
	for (i = 1; i < 31; i++) {
		mips_regstore_by_index(&context.registers, i).u = 0;
	}
	context.asid = 1;

	k_load_new_context(&context_mask, &context);

	k_exit();

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}
