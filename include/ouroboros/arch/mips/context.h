#ifndef OUROBOROS_ARCH_MIPS_CONTEXT_H
#define OUROBOROS_ARCH_MIPS_CONTEXT_H

#include <ouroboros/arch/mips/common.h>

#define OU_FLAGS_IE	(0x1 << 0)

struct ou_context {
	struct mips_regstore registers;
	unsigned int asid;		/* Address space ID */
	unsigned int flags;
};

#endif /* OUROBOROS_ARCH_MIPS_CONTEXT_H */
