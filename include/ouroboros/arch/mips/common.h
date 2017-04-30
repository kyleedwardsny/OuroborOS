#ifndef OUROBOROS_ARCH_MIPS_COMMON_H
#define OUROBOROS_ARCH_MIPS_COMMON_H

#include <ouroboros/common.h>

#include <ouroboros/arch/mips/asm.h>
#include <ouroboros/arch/mips/cp0.h>

#define STACK_SIZE_LOG		(10)
#define STACK_SIZE		(1 << STACK_SIZE_LOG)

/* TODO mips64 */
#define GPR_SIZE_LOG		(2)
#define GPR_SIZE		(1 << GPR_SIZE_LOG)
#define GPR_STORE		sw
#define GPR_LOAD		lw

#define PAGE_SIZE		(0x1000)
#define IS_PAGE_ALIGNED(val)	(((val) & (PAGE_SIZE - 1)) == 0)

#ifndef __ASSEMBLER__

#include <ouroboros/stddef.h>

typedef const void * gpr_ptr_t;
typedef ou_size_t gpr_u_t;
typedef ou_ptrdiff_t gpr_s_t;

typedef union {
	gpr_ptr_t ptr;
	gpr_u_t u;
	gpr_s_t s;
} gpr_t;

#endif /* __ASSEMBLER__ */

#endif /* OUROBOROS_ARCH_MIPS_COMMON_H */
