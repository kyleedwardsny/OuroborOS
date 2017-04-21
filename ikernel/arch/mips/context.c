#include <ouroboros/arch/mips/context.h>
#include <ouroboros/arch/mips/ikernel/entry.h>

#include <ouroboros/ikernel/context.h>

void k_save_old_context(const struct ou_context_mask *mask, struct ou_context *context)
{
	ou_uint32_t entry_hi;
	size_t i;

	if (mask->reg_mask & MIPS_CONTEXT_MASK_REG_PC) {
		MFC0(context->registers.pc, MIPS_CP0_EPC);
	}

	for (i = 1; i < 32; i++) {
		if (mask->reg_mask & MIPS_CONTEXT_MASK_REG_GPR(i)) {
			mips_regstore_by_index(&context->registers, i) = mips_regstore_by_index(&k_regstore, i);
		}
	}

	if (mask->flags0 & MIPS_CONTEXT_MASK_0_ASID) {
		MFC0(entry_hi, MIPS_CP0_ENTRY_HO);
		context->asid = entry_hi & MIPS_CP0_ENTRY_HO_ASID;
	}

	if (mask->flags0 & MIPS_CONTEXT_MASK_0_HI) {
		context->registers.hi = k_regstore.hi;
	}

	if (mask->flags0 & MIPS_CONTEXT_MASK_0_LO) {
		context->registers.lo = k_regstore.lo;
	}
}

void k_load_new_context(const struct ou_context_mask *mask, const struct ou_context *context)
{
	ou_uint32_t entry_hi;
	size_t i;

	if (mask->reg_mask & MIPS_CONTEXT_MASK_REG_PC) {
		MTC0(context->registers.pc, MIPS_CP0_EPC);
	}

	for (i = 1; i < 32; i++) {
		if (mask->reg_mask & MIPS_CONTEXT_MASK_REG_GPR(i)) {
			mips_regstore_by_index(&k_regstore, i) = mips_regstore_by_index(&context->registers, i);
		}
	}

	if (mask->flags0 & MIPS_CONTEXT_MASK_0_ASID) {
		MFC0(entry_hi, MIPS_CP0_ENTRY_HO);
		entry_hi &= ~MIPS_CP0_ENTRY_HO_ASID;
		entry_hi |= MIPS_CP0_ENTRY_HO_ASID_ASID(context->asid);
		MTC0(entry_hi, MIPS_CP0_ENTRY_HO);
	}

	if (mask->flags0 & MIPS_CONTEXT_MASK_0_HI) {
		k_regstore.hi = context->registers.hi;
	}

	if (mask->flags0 & MIPS_CONTEXT_MASK_0_LO) {
		k_regstore.lo = context->registers.lo;
	}
}
