#ifndef OUROBOROS_ARCH_MIPS_CONTEXT_H
#define OUROBOROS_ARCH_MIPS_CONTEXT_H

#include <ouroboros/common.h>

#include <ouroboros/arch/mips/common.h>

#define OU_CONTEXT_FLAGS_IE	(0x1 << 0)

struct ou_context {
	struct mips_regstore registers;
	unsigned int asid;		/* Address space ID */
	unsigned int flags;
};

#define MIPS_CONTEXT_MASK_0_ASID	BIT(0)
#define MIPS_CONTEXT_MASK_0_HI  	BIT(1)
#define MIPS_CONTEXT_MASK_0_LO  	BIT(2)

#define MIPS_CONTEXT_MASK_REG_PC	BIT(0)
#define MIPS_CONTEXT_MASK_REG_GPR(r)	BIT(r)

struct ou_context_mask {
	ou_uint32_t flags0;
	ou_uint32_t reg_mask;
};

struct ou_context_switch {
	const struct ou_context *new_context;
	struct ou_context *old_context;
};

#endif /* OUROBOROS_ARCH_MIPS_CONTEXT_H */
