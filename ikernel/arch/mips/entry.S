#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/common.h>
#include <ouroboros/genconfig.h>
#include <ouroboros/arch/mips/ikernel/entry.h>

	.section .text

	.macro store_hi_lo kreg
	mfhi $t0
	GPR_STORE $t0, CTX_HI_OFFSET(\kreg)
	mflo $t0
	GPR_STORE $t0, CTX_LO_OFFSET(\kreg)
	.endm

	.macro load_hi_lo kreg
	GPR_LOAD $t0, CTX_HI_OFFSET(\kreg)
	mthi $t0
	GPR_LOAD $t0, CTX_LO_OFFSET(\kreg)
	mtlo $t0
	.endm

	.macro store_regs kreg
	.set noat
	GPR_STORE $1, CTX_GPR_1_OFFSET(\kreg)
	.set at
	GPR_STORE $2, CTX_GPR_2_OFFSET(\kreg)
	GPR_STORE $3, CTX_GPR_3_OFFSET(\kreg)
	GPR_STORE $4, CTX_GPR_4_OFFSET(\kreg)
	GPR_STORE $5, CTX_GPR_5_OFFSET(\kreg)
	GPR_STORE $6, CTX_GPR_6_OFFSET(\kreg)
	GPR_STORE $7, CTX_GPR_7_OFFSET(\kreg)
	GPR_STORE $8, CTX_GPR_8_OFFSET(\kreg)
	GPR_STORE $9, CTX_GPR_9_OFFSET(\kreg)
	GPR_STORE $10, CTX_GPR_10_OFFSET(\kreg)
	GPR_STORE $11, CTX_GPR_11_OFFSET(\kreg)
	GPR_STORE $12, CTX_GPR_12_OFFSET(\kreg)
	GPR_STORE $13, CTX_GPR_13_OFFSET(\kreg)
	GPR_STORE $14, CTX_GPR_14_OFFSET(\kreg)
	GPR_STORE $15, CTX_GPR_15_OFFSET(\kreg)
	GPR_STORE $16, CTX_GPR_16_OFFSET(\kreg)
	GPR_STORE $17, CTX_GPR_17_OFFSET(\kreg)
	GPR_STORE $18, CTX_GPR_18_OFFSET(\kreg)
	GPR_STORE $19, CTX_GPR_19_OFFSET(\kreg)
	GPR_STORE $20, CTX_GPR_20_OFFSET(\kreg)
	GPR_STORE $21, CTX_GPR_21_OFFSET(\kreg)
	GPR_STORE $22, CTX_GPR_22_OFFSET(\kreg)
	GPR_STORE $23, CTX_GPR_23_OFFSET(\kreg)
	GPR_STORE $24, CTX_GPR_24_OFFSET(\kreg)
	GPR_STORE $25, CTX_GPR_25_OFFSET(\kreg)
	/* $26 and $27 are $k0 and $k1, we will store these later */
	GPR_STORE $28, CTX_GPR_28_OFFSET(\kreg)
	GPR_STORE $29, CTX_GPR_29_OFFSET(\kreg)
	GPR_STORE $30, CTX_GPR_30_OFFSET(\kreg)
	GPR_STORE $31, CTX_GPR_31_OFFSET(\kreg)

	store_hi_lo \kreg
	.endm

	.macro load_regs kreg
	load_hi_lo \kreg

	.set noat
	GPR_LOAD $1, CTX_GPR_1_OFFSET(\kreg)
	.set at
	GPR_LOAD $2, CTX_GPR_2_OFFSET(\kreg)
	GPR_LOAD $3, CTX_GPR_3_OFFSET(\kreg)
	GPR_LOAD $4, CTX_GPR_4_OFFSET(\kreg)
	GPR_LOAD $5, CTX_GPR_5_OFFSET(\kreg)
	GPR_LOAD $6, CTX_GPR_6_OFFSET(\kreg)
	GPR_LOAD $7, CTX_GPR_7_OFFSET(\kreg)
	GPR_LOAD $8, CTX_GPR_8_OFFSET(\kreg)
	GPR_LOAD $9, CTX_GPR_9_OFFSET(\kreg)
	GPR_LOAD $10, CTX_GPR_10_OFFSET(\kreg)
	GPR_LOAD $11, CTX_GPR_11_OFFSET(\kreg)
	GPR_LOAD $12, CTX_GPR_12_OFFSET(\kreg)
	GPR_LOAD $13, CTX_GPR_13_OFFSET(\kreg)
	GPR_LOAD $14, CTX_GPR_14_OFFSET(\kreg)
	GPR_LOAD $15, CTX_GPR_15_OFFSET(\kreg)
	GPR_LOAD $16, CTX_GPR_16_OFFSET(\kreg)
	GPR_LOAD $17, CTX_GPR_17_OFFSET(\kreg)
	GPR_LOAD $18, CTX_GPR_18_OFFSET(\kreg)
	GPR_LOAD $19, CTX_GPR_19_OFFSET(\kreg)
	GPR_LOAD $20, CTX_GPR_20_OFFSET(\kreg)
	GPR_LOAD $21, CTX_GPR_21_OFFSET(\kreg)
	GPR_LOAD $22, CTX_GPR_22_OFFSET(\kreg)
	GPR_LOAD $23, CTX_GPR_23_OFFSET(\kreg)
	GPR_LOAD $24, CTX_GPR_24_OFFSET(\kreg)
	GPR_LOAD $25, CTX_GPR_25_OFFSET(\kreg)
	/* $26 and $27 are $k0 and $k1, we will load these later */
	GPR_LOAD $28, CTX_GPR_28_OFFSET(\kreg)
	GPR_LOAD $29, CTX_GPR_29_OFFSET(\kreg)
	GPR_LOAD $30, CTX_GPR_30_OFFSET(\kreg)
	GPR_LOAD $31, CTX_GPR_31_OFFSET(\kreg)
	.endm

	.macro get_ebase_2 kreg_addr kreg_clobber
	mfc0 \kreg_clobber, MIPS_CP0_EBASE
	andi \kreg_clobber, MIPS_CP0_EBASE_CPUNUM
	sll \kreg_clobber, CTX_SIZE_LOG

	la \kreg_addr, CPU_LOCAL_NAME(_k_context)
	add \kreg_addr, \kreg_clobber
	.endm

	.macro get_sp
	mfc0 $t0, MIPS_CP0_EBASE
	andi $t0, MIPS_CP0_EBASE_CPUNUM
	sll $t0, STACK_SIZE_LOG

	la $sp, _stack_begin + STACK_SIZE /* Bottom of stack */
	add $sp, $t0
	.endm

	.type _entry_standard, function
_entry_standard:
	get_ebase_2 $k0, $k1
	store_regs $k0

	get_sp
	bal k_entry

	.global k_exit_k0_k1
	.type k_exit_k0_k1, function
k_exit_standard:
	get_ebase_2 $k0, $k1
	load_regs $k0
	/* For security, don't leak this info */
	move $k0, $0
	move $k1, $0

	eret

	.type _entry_scratch, function
_entry_scratch:
	mtc0 $k0, MIPS_CP0_KSCRATCH(2)
	mtc0 $k1, MIPS_CP0_KSCRATCH(3)
	get_ebase_2 $k0, $k1
	store_regs $k0

	move $t0, $k0
	mfc0 $k0, MIPS_CP0_KSCRATCH(2)
	mfc0 $k0, MIPS_CP0_KSCRATCH(3)
	GPR_STORE $k0, CTX_GPR_26_OFFSET($t0)
	GPR_STORE $k1, CTX_GPR_27_OFFSET($t0)

	get_sp
	bal k_entry

	.global k_exit_scratch
	.type k_exit_scratch, function
k_exit_scratch:
	get_ebase_2 $k0, $k1
	load_regs $k0
	GPR_LOAD $k1, CTX_GPR_27_OFFSET($k0)
	GPR_LOAD $k0, CTX_GPR_26_OFFSET($k0)

	eret

_entry_shadow:
	get_sp
	bal k_entry

	.global k_exit_shadow
	.type k_exit_shadow, function
k_exit_shadow:
	eret

	.section .text.evt

	.macro next_evt
	.org ALIGN(., 0x1000)
	.endm

	.macro evt_tlb_refill evt
	.org \evt + 0x000
	.endm

	.macro evt_general_exception evt
	.org \evt + 0x180
	.endm

	.macro evt_interrupt evt
	.org \evt + 0x200
	.endm

	.macro evt name
	next_evt
	.global k_evt_\name
	.type k_evt_\name, function
k_evt_\name:

	evt_tlb_refill k_evt_\name
_evt_\name\()_tlb_refill:
	j _entry_\name

	evt_general_exception k_evt_\name
_evt_\name\()_general_exception:
	j _entry_\name

	evt_interrupt k_evt_\name
_evt_\name\()_interrupt:
	j _entry_\name
	.endm

	evt standard
	evt scratch
	evt shadow
