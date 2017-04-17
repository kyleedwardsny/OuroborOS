#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/common.h>
#include <ouroboros/config.h>

	.section .bss.regstore

	.global k_regstore
	.type k_regstore, object
k_regstore:
	.fill OU_MAX_CORES_ALIGNED * 32, GPR_SIZE

	.section .text

	.macro store_regs kreg
	.set noat
	GPR_STORE $1, GPR_1_OFFSET(\kreg)
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
	.set at
	.endm

	.macro load_regs kreg
	.set noat
	GPR_LOAD $1, GPR_1_OFFSET(\kreg)
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
	.set at
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

	.type _entry_basic, function
_entry_basic:
	get_ebase $k0
	store_regs $k0
	GPR_STORE $k1, GPR_27_OFFSET($k0)

	get_sp

	/* TODO Do kernel stuff */

	get_ebase $k0
	load_regs $k0
	move $k0, $0 /* For security - don't leak $k0 */
	GPR_LOAD $k1, GPR_27_OFFSET($k0)

	eret

	.type _entry_user_local, function
_entry_user_local:
	mtc0 $k0, MIPS_CP0_USER_LOCAL

	get_ebase $k0
	store_regs $k0
	GPR_STORE $k1, GPR_27_OFFSET($k0)

	move $k1, $k0
	mfc0 $k0, MIPS_CP0_USER_LOCAL
	GPR_STORE $k0, GPR_26_OFFSET($k1)

	get_sp

	/* TODO Do kernel stuff */

	get_ebase $k0
	load_regs $k0
	GPR_LOAD $k1, GPR_27_OFFSET($k0) /* This MUST be done before $k0 */
	GPR_LOAD $k0, GPR_26_OFFSET($k0)

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

	next_evt
	.global evt_basic
	.type evt_basic, function
evt_basic:

	evt_tlb_refill evt_basic
_evt_basic_tlb_refill:
	j _entry_basic

	evt_general_exception evt_basic
_evt_basic_general_exception:
	j _entry_basic

	evt_interrupt evt_basic 0

	.global evt_user_local
	.type evt_user_local, function
evt_user_local:

	evt_tlb_refill evt_user_local
_evt_user_local_tlb_refill:
	j _entry_user_local

	evt_general_exception evt_user_local
_evt_user_local_general_exception:
	j _entry_user_local

	next_evt
