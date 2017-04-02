#include <ouroboros/hw/uart/16550.h>
#include <ouroboros/arch/mips/cp0.h>

	.abicalls
	.set STACK_BOTTOM, 0x8000000
	.set TEXT_BEGIN, 0x10000

	.section .text

	.global _start
	.type _start, function
_start:
	li $sp, STACK_BOTTOM

	bal k_main

0:
	b 0b
