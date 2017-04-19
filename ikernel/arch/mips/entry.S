#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/common.h>
#include <ouroboros/genconfig.h>
#include <ouroboros/arch/mips/ikernel/entry.h>

	.section .text

	.macro store_regs kreg
	.set noat
	GPR_STORE $1, GPR_1_OFFSET(\kreg)
	.set at
	GPR_STORE $2, GPR_2_OFFSET(\kreg)
	GPR_STORE $3, GPR_3_OFFSET(\kreg)
	GPR_STORE $4, GPR_4_OFFSET(\kreg)
	GPR_STORE $5, GPR_5_OFFSET(\kreg)
	GPR_STORE $6, GPR_6_OFFSET(\kreg)
	GPR_STORE $7, GPR_7_OFFSET(\kreg)
	GPR_STORE $8, GPR_8_OFFSET(\kreg)
	GPR_STORE $9, GPR_9_OFFSET(\kreg)
	GPR_STORE $10, GPR_10_OFFSET(\kreg)
	GPR_STORE $11, GPR_11_OFFSET(\kreg)
	GPR_STORE $12, GPR_12_OFFSET(\kreg)
	GPR_STORE $13, GPR_13_OFFSET(\kreg)
	GPR_STORE $14, GPR_14_OFFSET(\kreg)
	GPR_STORE $15, GPR_15_OFFSET(\kreg)
	GPR_STORE $16, GPR_16_OFFSET(\kreg)
	GPR_STORE $17, GPR_17_OFFSET(\kreg)
	GPR_STORE $18, GPR_18_OFFSET(\kreg)
	GPR_STORE $19, GPR_19_OFFSET(\kreg)
	GPR_STORE $20, GPR_20_OFFSET(\kreg)
	GPR_STORE $21, GPR_21_OFFSET(\kreg)
	GPR_STORE $22, GPR_22_OFFSET(\kreg)
	GPR_STORE $23, GPR_23_OFFSET(\kreg)
	GPR_STORE $24, GPR_24_OFFSET(\kreg)
	GPR_STORE $25, GPR_25_OFFSET(\kreg)
	/* $26 and $27 are $k0 and $k1, we will store these later */
	GPR_STORE $28, GPR_28_OFFSET(\kreg)
	GPR_STORE $29, GPR_29_OFFSET(\kreg)
	GPR_STORE $30, GPR_30_OFFSET(\kreg)
	GPR_STORE $31, GPR_31_OFFSET(\kreg)
	.endm

	.macro load_regs kreg
	.set noat
	GPR_LOAD $1, GPR_1_OFFSET(\kreg)
	.set at
	GPR_LOAD $2, GPR_2_OFFSET(\kreg)
	GPR_LOAD $3, GPR_3_OFFSET(\kreg)
	GPR_LOAD $4, GPR_4_OFFSET(\kreg)
	GPR_LOAD $5, GPR_5_OFFSET(\kreg)
	GPR_LOAD $6, GPR_6_OFFSET(\kreg)
	GPR_LOAD $7, GPR_7_OFFSET(\kreg)
	GPR_LOAD $8, GPR_8_OFFSET(\kreg)
	GPR_LOAD $9, GPR_9_OFFSET(\kreg)
	GPR_LOAD $10, GPR_10_OFFSET(\kreg)
	GPR_LOAD $11, GPR_11_OFFSET(\kreg)
	GPR_LOAD $12, GPR_12_OFFSET(\kreg)
	GPR_LOAD $13, GPR_13_OFFSET(\kreg)
	GPR_LOAD $14, GPR_14_OFFSET(\kreg)
	GPR_LOAD $15, GPR_15_OFFSET(\kreg)
	GPR_LOAD $16, GPR_16_OFFSET(\kreg)
	GPR_LOAD $17, GPR_17_OFFSET(\kreg)
	GPR_LOAD $18, GPR_18_OFFSET(\kreg)
	GPR_LOAD $19, GPR_19_OFFSET(\kreg)
	GPR_LOAD $20, GPR_20_OFFSET(\kreg)
	GPR_LOAD $21, GPR_21_OFFSET(\kreg)
	GPR_LOAD $22, GPR_22_OFFSET(\kreg)
	GPR_LOAD $23, GPR_23_OFFSET(\kreg)
	GPR_LOAD $24, GPR_24_OFFSET(\kreg)
	GPR_LOAD $25, GPR_25_OFFSET(\kreg)
	/* $26 and $27 are $k0 and $k1, we will load these later */
	GPR_LOAD $28, GPR_28_OFFSET(\kreg)
	GPR_LOAD $29, GPR_29_OFFSET(\kreg)
	GPR_LOAD $30, GPR_30_OFFSET(\kreg)
	GPR_LOAD $31, GPR_31_OFFSET(\kreg)
	.endm

	.macro get_ebase_2 kreg_addr kreg_clobber
	mfc0 \kreg_clobber, MIPS_CP0_EBASE
	andi \kreg_clobber, MIPS_CP0_EBASE_CPUNUM
	sll \kreg_clobber, REGSTORE_CORE_SHIFT

	la \kreg_addr, CPU_LOCAL_NAME(_k_regstore)
	add \kreg_addr, \kreg_clobber
	.endm

	.macro get_ebase kreg
	mfc0 \kreg, MIPS_CP0_EBASE
	andi \kreg, MIPS_CP0_EBASE_CPUNUM
	sll \kreg, (16 + REGSTORE_CORE_SHIFT)

	ori \kreg, _regstore_upper
	rotr \kreg, 16
	ori \kreg, _regstore_lower
	.endm

	.macro get_sp
	mfc0 $t0, MIPS_CP0_EBASE
	andi $t0, MIPS_CP0_EBASE_CPUNUM
	sll $t0, STACK_SIZE_LOG

	la $sp, _stack_begin + STACK_SIZE /* Bottom of stack */
	add $sp, $t0
	.endm

	.type _entry_k0_k1, function
_entry_k0_k1:
	get_ebase_2 $k0, $k1
	store_regs $k0

	get_sp
	bal k_entry

	.global k_exit_k0_k1
	.type k_exit_k0_k1, function
k_exit_k0_k1:
	get_ebase_2 $k0, $k1
	load_regs $k0
	/* For security, don't leak this info */
	move $k0, $0
	move $k1, $0

	eret

	.type _entry_k0_rotr, function
_entry_k0_rotr:
	get_ebase $k0
	store_regs $k0
	GPR_STORE $k1, GPR_27_OFFSET($k0)

	get_sp
	bal k_entry

	.global k_exit_k0_rotr
	.type k_exit_k0_rotr, function
k_exit_k0_rotr:
	get_ebase_2 $k0, $k1
	load_regs $k0
	GPR_LOAD $k1, GPR_27_OFFSET($k0)
	/* For security, don't leak this info */
	move $k0, $0

	eret

	.type _entry_k1_rotr, function
_entry_k1_rotr:
	get_ebase $k1
	store_regs $k1
	GPR_STORE $k0, GPR_26_OFFSET($k1)

	get_sp
	bal k_entry

	.global k_exit_k1_rotr
	.type k_exit_k1_rotr, function
k_exit_k1_rotr:
	get_ebase_2 $k1, $k0
	load_regs $k1
	GPR_LOAD $k0, GPR_26_OFFSET($k1)
	/* For security, don't leak this info */
	move $k1, $0

	eret

	.type _entry_k0_ul, function
_entry_k0_ul:
	mtc0 $k1, MIPS_CP0_USER_LOCAL

	get_ebase_2 $k1, $k0
	store_regs $k1

	move $k0, $k1
	mfc0 $k1, MIPS_CP0_USER_LOCAL
	GPR_STORE $k1, GPR_27_OFFSET($k0)

	get_sp
	bal k_entry

	.global k_exit_k0_ul
	.type k_exit_k0_ul, function
k_exit_k0_ul:
	get_ebase_2 $k0, $k1
	load_regs $k0
	GPR_LOAD $k1, GPR_27_OFFSET($k0) /* This MUST be done before $k0 */
	/* For security, don't leak this info */
	move $k0, $0

	eret

	.type _entry_k1_ul, function
_entry_k1_ul:
	mtc0 $k0, MIPS_CP0_USER_LOCAL

	get_ebase_2 $k0, $k1
	store_regs $k0

	move $k1, $k0
	mfc0 $k0, MIPS_CP0_USER_LOCAL
	GPR_STORE $k0, GPR_26_OFFSET($k1)

	get_sp
	bal k_entry

	.global k_exit_k1_ul
	.type k_exit_k1_ul, function
k_exit_k1_ul:
	get_ebase_2 $k1, $k0
	load_regs $k1
	GPR_LOAD $k0, GPR_26_OFFSET($k1)
	/* For security, don't leak this info */
	move $k1, $0

	eret

	.type _entry_ul_rotr, function
_entry_ul_rotr:
	mtc0 $k0, MIPS_CP0_USER_LOCAL

	get_ebase $k0
	store_regs $k0
	GPR_STORE $k1, GPR_27_OFFSET($k0)

	move $k1, $k0
	mfc0 $k0, MIPS_CP0_USER_LOCAL
	GPR_STORE $k0, GPR_26_OFFSET($k1)

	get_sp
	bal k_entry

	.global k_exit_ul_rotr
	.type k_exit_ul_rotr, function
k_exit_ul_rotr:
	get_ebase_2 $k0, $k1
	load_regs $k0
	GPR_LOAD $k1, GPR_27_OFFSET($k0)
	GPR_LOAD $k0, GPR_26_OFFSET($k0)

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

	.macro evt_interrupt evt int_num
	.org \evt + 0x200 + (\int_num * 0x80)
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

	evt_interrupt k_evt_\name 0
_evt_\name\()_interrupt_0:
	j _entry_\name
	.endm

	evt k0_k1
	evt k0_rotr
	evt k1_rotr
	evt k0_ul
	evt k1_ul
	evt ul_rotr
	evt shadow
