#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/common.h>
#include <ouroboros/config.h>

	.section .bss.regstore

	.global k_regstore
	.type k_regstore, object
k_regstore:
	.fill OU_MAX_CORES_ALIGNED * 32, GPR_SIZE

	.section .text

	.macro store_regs_k0
	.set noat
	GPR_STORE $1, GPR_1_OFFSET($k0)
	GPR_STORE $2, GPR_2_OFFSET($k0)
	GPR_STORE $3, GPR_3_OFFSET($k0)
	GPR_STORE $4, GPR_4_OFFSET($k0)
	GPR_STORE $5, GPR_5_OFFSET($k0)
	GPR_STORE $6, GPR_6_OFFSET($k0)
	GPR_STORE $7, GPR_7_OFFSET($k0)
	GPR_STORE $8, GPR_8_OFFSET($k0)
	GPR_STORE $9, GPR_9_OFFSET($k0)
	GPR_STORE $10, GPR_10_OFFSET($k0)
	GPR_STORE $11, GPR_11_OFFSET($k0)
	GPR_STORE $12, GPR_12_OFFSET($k0)
	GPR_STORE $13, GPR_13_OFFSET($k0)
	GPR_STORE $14, GPR_14_OFFSET($k0)
	GPR_STORE $15, GPR_15_OFFSET($k0)
	GPR_STORE $16, GPR_16_OFFSET($k0)
	GPR_STORE $17, GPR_17_OFFSET($k0)
	GPR_STORE $18, GPR_18_OFFSET($k0)
	GPR_STORE $19, GPR_19_OFFSET($k0)
	GPR_STORE $20, GPR_20_OFFSET($k0)
	GPR_STORE $21, GPR_21_OFFSET($k0)
	GPR_STORE $22, GPR_22_OFFSET($k0)
	GPR_STORE $23, GPR_23_OFFSET($k0)
	GPR_STORE $24, GPR_24_OFFSET($k0)
	GPR_STORE $25, GPR_25_OFFSET($k0)
	/* $26 is $k0, we will store this later */
	GPR_STORE $27, GPR_27_OFFSET($k0)
	GPR_STORE $28, GPR_28_OFFSET($k0)
	GPR_STORE $29, GPR_29_OFFSET($k0)
	GPR_STORE $30, GPR_30_OFFSET($k0)
	GPR_STORE $31, GPR_31_OFFSET($k0)
	.set at
	.endm

	.macro load_regs_k0
	.set noat
	GPR_LOAD $1, GPR_1_OFFSET($k0)
	GPR_LOAD $2, GPR_2_OFFSET($k0)
	GPR_LOAD $3, GPR_3_OFFSET($k0)
	GPR_LOAD $4, GPR_4_OFFSET($k0)
	GPR_LOAD $5, GPR_5_OFFSET($k0)
	GPR_LOAD $6, GPR_6_OFFSET($k0)
	GPR_LOAD $7, GPR_7_OFFSET($k0)
	GPR_LOAD $8, GPR_8_OFFSET($k0)
	GPR_LOAD $9, GPR_9_OFFSET($k0)
	GPR_LOAD $10, GPR_10_OFFSET($k0)
	GPR_LOAD $11, GPR_11_OFFSET($k0)
	GPR_LOAD $12, GPR_12_OFFSET($k0)
	GPR_LOAD $13, GPR_13_OFFSET($k0)
	GPR_LOAD $14, GPR_14_OFFSET($k0)
	GPR_LOAD $15, GPR_15_OFFSET($k0)
	GPR_LOAD $16, GPR_16_OFFSET($k0)
	GPR_LOAD $17, GPR_17_OFFSET($k0)
	GPR_LOAD $18, GPR_18_OFFSET($k0)
	GPR_LOAD $19, GPR_19_OFFSET($k0)
	GPR_LOAD $20, GPR_20_OFFSET($k0)
	GPR_LOAD $21, GPR_21_OFFSET($k0)
	GPR_LOAD $22, GPR_22_OFFSET($k0)
	GPR_LOAD $23, GPR_23_OFFSET($k0)
	GPR_LOAD $24, GPR_24_OFFSET($k0)
	GPR_LOAD $25, GPR_25_OFFSET($k0)
	/* $26 is $k0, we will load this later */
	GPR_LOAD $27, GPR_27_OFFSET($k0)
	GPR_LOAD $28, GPR_28_OFFSET($k0)
	GPR_LOAD $29, GPR_29_OFFSET($k0)
	GPR_LOAD $30, GPR_30_OFFSET($k0)
	GPR_LOAD $31, GPR_31_OFFSET($k0)
	.set at
	.endm

	.macro get_ebase_k0
	mfc0 $k0, MIPS_CP0_EBASE
	andi $k0, MIPS_CP0_EBASE_CPUNUM
	sll $k0, (16 + REGSTORE_CORE_SHIFT)

	ori $k0, _regstore_upper
	rotr $k0, 16
	ori $k0, _regstore_lower
	.endm

	.type _entry_basic, function
_entry_basic:
	get_ebase_k0
	store_regs_k0

	/* TODO Do kernel stuff */

	get_ebase_k0
	load_regs_k0
	move $k0, $0 /* For security - don't leak $k0 */

	eret

	.type _entry_user_local, function
_entry_user_local:
	mtc0 $k0, MIPS_CP0_USER_LOCAL

	get_ebase_k0
	store_regs_k0

	move $k1, $k0
	mfc0 $k0, MIPS_CP0_USER_LOCAL
	GPR_STORE $k0, GPR_26_OFFSET($k1)

	/* TODO Do kernel stuff */

	get_ebase_k0
	load_regs_k0
	GPR_LOAD $26, GPR_26_OFFSET($k0)

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
