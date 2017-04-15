#include <ouroboros/arch/mips/cp0.h>

	.section .text.start

	.global _start
	.type _start, function
_start:
	/* Disable interrupts, set up status register */
	di

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
	la $sp, _stack_bottom

	jal k_main_args

0:
	b 0b
