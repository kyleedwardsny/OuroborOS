#include <ouroboros/arch/mips/context.h>
#include <ouroboros/arch/mips/ikernel/entry.h>

#include <ouroboros/ikernel/context.h>

void k_save_old_context(struct ou_context *context)
{
	unsigned long entry_hi;
	size_t i;

	for (i = 1; i < 32; i++) {
		if (context->mask_regs & CTX_MASK_REG_GPR(i)) {
			context->gpr.by_index[i] = k_context.gpr.by_index[i];
		}
	}

	if (context->mask_0 & CTX_MASK_0_PC) {
		MFC0(context->pc, MIPS_CP0_EPC);
	}

	if (context->mask_0 & CTX_MASK_0_HI) {
		context->hi = k_context.hi;
	}

	if (context->mask_0 & CTX_MASK_0_LO) {
		context->lo = k_context.lo;
	}

	if (context->mask_0 & CTX_MASK_0_ASID) {
		MFC0(entry_hi, MIPS_CP0_ENTRY_HO);
		context->asid = entry_hi & MIPS_CP0_ENTRY_HO_ASID;
	}
}

void k_load_new_context(const struct ou_context *context)
{
	unsigned long entry_hi;
	size_t i;

	for (i = 1; i < 32; i++) {
		if (context->mask_regs & CTX_MASK_REG_GPR(i)) {
			k_context.gpr.by_index[i] = context->gpr.by_index[i];
		}
	}

	if (context->mask_0 & CTX_MASK_0_PC) {
		MTC0(context->pc, MIPS_CP0_EPC);
	}

	if (context->mask_0 & CTX_MASK_0_HI) {
		k_context.hi = context->hi;
	}

	if (context->mask_0 & CTX_MASK_0_LO) {
		k_context.lo = context->lo;
	}

	if (context->mask_0 & CTX_MASK_0_ASID) {
		MFC0(entry_hi, MIPS_CP0_ENTRY_HO);
		entry_hi &= ~MIPS_CP0_ENTRY_HO_ASID;
		entry_hi |= MIPS_CP0_ENTRY_HO_ASID_ASID(context->asid);
		MTC0(entry_hi, MIPS_CP0_ENTRY_HO);
	}
}
