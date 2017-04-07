#include <ouroboros/hw/uart/16550.h>
#include <ouroboros/arch/mips/cp0.h>

	.set STACK_BOTTOM, 0x88000000
	.set TEXT_BEGIN, 0x80010000

	.section .text

	.global _start
	.type _start, function
_start:
	li $sp, STACK_BOTTOM
	addiu $sp, -12

	jal k_main

0:
	b 0b

	.global do_syscall
	.type do_syscall, function
do_syscall:
	syscall
	jr $ra

	.global _syscall
	.type _syscall, function
_syscall:

	.section .text.evt
	.global exception_vector_table
exception_vector_table:
	.fill 0x180, 1, 0

	.type general_exception, function
general_exception:
	/* Increment the instruction counter */
	mtc0 $t0, MIPS_CP0_USER_LOCAL
	mfc0 $t0, MIPS_CP0_EPC
	addiu $t0, 4
	mtc0 $t0, MIPS_CP0_EPC
	mfc0 $t0, MIPS_CP0_USER_LOCAL

	/* Do the actual work */
	addiu $v0, $a0, 16
	eret
