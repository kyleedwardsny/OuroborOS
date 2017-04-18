#include <ouroboros/arch/mips/common.h>
#include <ouroboros/arch/mips/cp0.h>

	.section .text.start

	.global _start
	.type _start, function
_start:
	/* Disable cache for now TODO */
	mfc0 $t0, MIPS_CP0_CONFIG
	li $t1, MIPS_CP0_CONFIG_M
	and $t0, $t1
	beqz $t0, 0f

	li $t0, MIPS_CP0_CONFIG_K0_K0(MIPS_CP0_CACHE_ATTR_U)
	mtc0 $t0, MIPS_CP0_CONFIG

0:
	/* Disable interrupts, set up status register for changing shadow set */
	li $t0, MIPS_CP0_STATUS_BEV | MIPS_CP0_STATUS_KSU_K | MIPS_CP0_STATUS_EXL
	mtc0 $t0, MIPS_CP0_STATUS

	/* Make sure we are using shadow set 0 */
	mfc0 $t0, MIPS_CP0_SRSCTL
	li $t1, ~MIPS_CP0_SRSCTL_PSS
	and $t0, $t1
	mtc0 $t0, MIPS_CP0_SRSCTL

	/* Perform the jump to shadow set 0 and kseg0 */
	la $t0, _kseg0
	mtc0 $t0, MIPS_CP0_EPC
	eret

_kseg0:
	/* Set up the status register to its true status */
	li $t0, MIPS_CP0_STATUS_BEV | MIPS_CP0_STATUS_KSU_U | MIPS_CP0_STATUS_EXL
	mtc0 $t0, MIPS_CP0_STATUS

	/* Clear .bss */
	la $t0, _bss_begin
	la $t1, _bss_end

0:
	sltu $t2, $t0, $t1
	beqz $t2, 0f
	sw $0, 0($t0)
	sw $0, 4($t0)
	sw $0, 8($t0)
	sw $0, 12($t0)
	sw $0, 16($t0)
	sw $0, 20($t0)
	sw $0, 24($t0)
	sw $0, 28($t0)
	addiu $t0, 32
	b 0b

0:
	la $sp, _stack_begin + STACK_SIZE

	/* This should never return */
	bal k_main_args
	b k_hang
