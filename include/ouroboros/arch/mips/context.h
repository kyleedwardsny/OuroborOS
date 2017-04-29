#ifndef OUROBOROS_ARCH_MIPS_CONTEXT_H
#define OUROBOROS_ARCH_MIPS_CONTEXT_H

#include <ouroboros/common.h>

#include <ouroboros/arch/mips/common.h>

#define CTX_SIZE_LOG		(6 + GPR_SIZE_LOG)
#define CTX_SIZE		(1 << REGSTORE_SIZE_LOG)

#define CTX_GPR_1_OFFSET	(GPR_SIZE * 33)
#define CTX_GPR_2_OFFSET	(GPR_SIZE * 34)
#define CTX_GPR_3_OFFSET	(GPR_SIZE * 35)
#define CTX_GPR_4_OFFSET	(GPR_SIZE * 36)
#define CTX_GPR_5_OFFSET	(GPR_SIZE * 37)
#define CTX_GPR_6_OFFSET	(GPR_SIZE * 38)
#define CTX_GPR_7_OFFSET	(GPR_SIZE * 39)
#define CTX_GPR_8_OFFSET	(GPR_SIZE * 40)
#define CTX_GPR_9_OFFSET	(GPR_SIZE * 41)
#define CTX_GPR_10_OFFSET	(GPR_SIZE * 42)
#define CTX_GPR_11_OFFSET	(GPR_SIZE * 43)
#define CTX_GPR_12_OFFSET	(GPR_SIZE * 44)
#define CTX_GPR_13_OFFSET	(GPR_SIZE * 45)
#define CTX_GPR_14_OFFSET	(GPR_SIZE * 46)
#define CTX_GPR_15_OFFSET	(GPR_SIZE * 47)
#define CTX_GPR_16_OFFSET	(GPR_SIZE * 48)
#define CTX_GPR_17_OFFSET	(GPR_SIZE * 49)
#define CTX_GPR_18_OFFSET	(GPR_SIZE * 50)
#define CTX_GPR_19_OFFSET	(GPR_SIZE * 51)
#define CTX_GPR_20_OFFSET	(GPR_SIZE * 52)
#define CTX_GPR_21_OFFSET	(GPR_SIZE * 53)
#define CTX_GPR_22_OFFSET	(GPR_SIZE * 54)
#define CTX_GPR_23_OFFSET	(GPR_SIZE * 55)
#define CTX_GPR_24_OFFSET	(GPR_SIZE * 56)
#define CTX_GPR_25_OFFSET	(GPR_SIZE * 57)
#define CTX_GPR_26_OFFSET	(GPR_SIZE * 58)
#define CTX_GPR_27_OFFSET	(GPR_SIZE * 59)
#define CTX_GPR_28_OFFSET	(GPR_SIZE * 60)
#define CTX_GPR_29_OFFSET	(GPR_SIZE * 61)
#define CTX_GPR_30_OFFSET	(GPR_SIZE * 62)
#define CTX_GPR_31_OFFSET	(GPR_SIZE * 63)

#define CTX_HI_OFFSET		(GPR_SIZE * 32)
#define CTX_LO_OFFSET		(GPR_SIZE * 33)

#define CTX_MASK_0_PC		BIT(0)
#define CTX_MASK_0_HI  		BIT(1)
#define CTX_MASK_0_LO  		BIT(2)
#define CTX_MASK_0_ASID		BIT(3)

#define CTX_MASK_REG_GPR(r)	BIT(r)

#ifndef __ASSEMBLER__

struct gpr_map {
	gpr_t zero;
	gpr_t at;
	gpr_t v0;
	gpr_t v1;
	gpr_t a0;
	gpr_t a1;
	gpr_t a2;
	gpr_t a3;
	gpr_t t0;
	gpr_t t1;
	gpr_t t2;
	gpr_t t3;
	gpr_t t4;
	gpr_t t5;
	gpr_t t6;
	gpr_t t7;
	gpr_t s0;
	gpr_t s1;
	gpr_t s2;
	gpr_t s3;
	gpr_t s4;
	gpr_t s5;
	gpr_t s6;
	gpr_t s7;
	gpr_t t8;
	gpr_t t9;
	gpr_t k0;
	gpr_t k1;
	gpr_t gp;
	gpr_t sp;
	gpr_t fp_s8;
	gpr_t ra;
};

union gpr_store {
	struct gpr_map by_name;
	gpr_t by_index[32];
};

struct tlb_entry {
	unsigned long entry_lo0;
	unsigned long entry_lo1;
	unsigned long entry_hi;
	unsigned long page_mask;
};

struct tlb_entry_access {
	int index;
	struct tlb_entry entry;
};

struct ou_context {
	/* Context mask */
	unsigned long mask_regs;
	unsigned long mask_0;

	/* Space between mask and contents */
	unsigned long _reserved[25];

	/* Actual contents of context */
	unsigned long flags;
	unsigned long asid;	/* Address space ID */
	unsigned long hi;
	unsigned long lo;
	const void *pc;

	union gpr_store gpr;
};

struct ou_context_switch {
	const struct ou_context *new_context;
	struct ou_context *old_context;

	const struct tlb_entry_access *tlb_entries;
	ou_size_t num_tlb_entries;
};

#endif /* __ASSEMBLER__ */

#endif /* OUROBOROS_ARCH_MIPS_CONTEXT_H */
