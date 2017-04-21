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
#define REGSTORE_SIZE_LOG	(6 + GPR_SIZE_LOG)
#define REGSTORE_SIZE		(1 << REGSTORE_SIZE_LOG)
#define REGSTORE_CORE_SHIFT	(REGSTORE_SIZE_LOG)
#define GPR_STORE		sw
#define GPR_LOAD		lw

#if (1 << REGSTORE_CORE_SHIFT) != REGSTORE_SIZE
#error "Incorrect REGSTORE_CORE_SHIFT value"
#endif

#define PC_OFFSET	(GPR_SIZE * 0)
#define GPR_1_OFFSET	(GPR_SIZE * 1)
#define GPR_2_OFFSET	(GPR_SIZE * 2)
#define GPR_3_OFFSET	(GPR_SIZE * 3)
#define GPR_4_OFFSET	(GPR_SIZE * 4)
#define GPR_5_OFFSET	(GPR_SIZE * 5)
#define GPR_6_OFFSET	(GPR_SIZE * 6)
#define GPR_7_OFFSET	(GPR_SIZE * 7)
#define GPR_8_OFFSET	(GPR_SIZE * 8)
#define GPR_9_OFFSET	(GPR_SIZE * 9)
#define GPR_10_OFFSET	(GPR_SIZE * 10)
#define GPR_11_OFFSET	(GPR_SIZE * 11)
#define GPR_12_OFFSET	(GPR_SIZE * 12)
#define GPR_13_OFFSET	(GPR_SIZE * 13)
#define GPR_14_OFFSET	(GPR_SIZE * 14)
#define GPR_15_OFFSET	(GPR_SIZE * 15)
#define GPR_16_OFFSET	(GPR_SIZE * 16)
#define GPR_17_OFFSET	(GPR_SIZE * 17)
#define GPR_18_OFFSET	(GPR_SIZE * 18)
#define GPR_19_OFFSET	(GPR_SIZE * 19)
#define GPR_20_OFFSET	(GPR_SIZE * 20)
#define GPR_21_OFFSET	(GPR_SIZE * 21)
#define GPR_22_OFFSET	(GPR_SIZE * 22)
#define GPR_23_OFFSET	(GPR_SIZE * 23)
#define GPR_24_OFFSET	(GPR_SIZE * 24)
#define GPR_25_OFFSET	(GPR_SIZE * 25)
#define GPR_26_OFFSET	(GPR_SIZE * 26)
#define GPR_27_OFFSET	(GPR_SIZE * 27)
#define GPR_28_OFFSET	(GPR_SIZE * 28)
#define GPR_29_OFFSET	(GPR_SIZE * 29)
#define GPR_30_OFFSET	(GPR_SIZE * 30)
#define GPR_31_OFFSET	(GPR_SIZE * 31)

#define HI_OFFSET	(GPR_SIZE * 32)
#define LO_OFFSET	(GPR_SIZE * 33)

#define PAGE_SIZE		(0x1000)
#define IS_PAGE_ALIGNED(val)	((val & (PAGE_SIZE - 1)) == 0)

#ifndef __ASSEMBLER__

#include <ouroboros/common.h>
#include <ouroboros/stddef.h>

typedef const void * gpr_ptr_t;
typedef ou_size_t gpr_u_t;
typedef ou_ptrdiff_t gpr_s_t;

typedef union {
	gpr_ptr_t ptr;
	gpr_u_t u;
	gpr_s_t s;
} gpr_t;

struct mips_regstore {
	unsigned long pc;

	gpr_t gpr_1;
	gpr_t gpr_2;
	gpr_t gpr_3;
	gpr_t gpr_4;
	gpr_t gpr_5;
	gpr_t gpr_6;
	gpr_t gpr_7;
	gpr_t gpr_8;
	gpr_t gpr_9;
	gpr_t gpr_10;
	gpr_t gpr_11;
	gpr_t gpr_12;
	gpr_t gpr_13;
	gpr_t gpr_14;
	gpr_t gpr_15;
	gpr_t gpr_16;
	gpr_t gpr_17;
	gpr_t gpr_18;
	gpr_t gpr_19;
	gpr_t gpr_20;
	gpr_t gpr_21;
	gpr_t gpr_22;
	gpr_t gpr_23;
	gpr_t gpr_24;
	gpr_t gpr_25;
	gpr_t gpr_26;
	gpr_t gpr_27;
	gpr_t gpr_28;
	gpr_t gpr_29;
	gpr_t gpr_30;
	gpr_t gpr_31;

	unsigned long hi;
	unsigned long lo;

	unsigned long _reserved[30];
};

#define mips_regstore_by_index(regstore, index)	\
	(((gpr_t *) (regstore))[index])

#endif /* __ASSEMBLER__ */

#endif /* OUROBOROS_ARCH_MIPS_COMMON_H */
