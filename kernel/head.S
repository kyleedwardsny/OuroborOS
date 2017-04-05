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
