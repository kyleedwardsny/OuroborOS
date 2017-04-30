#include <ouroboros/arch/mips/syscall.h>

	.section .rodata.header

_load_addr:
	.word 0x40000000

_entry_addr:
	.word _start

	.section .text.early

	.global _start
	.type _start, function
_start:
	la $a0, tlb_table
	li $a1, 64
	syscall OU_SYSCALL_READTLB

0:
	b 0b

	.macro tlb_entry index
	.word \index
	.fill 4, 4
	.endm

	.macro tlb_entry_8 index
	tlb_entry \index + 0
	tlb_entry \index + 1
	tlb_entry \index + 2
	tlb_entry \index + 3
	tlb_entry \index + 4
	tlb_entry \index + 5
	tlb_entry \index + 6
	tlb_entry \index + 7
	.endm

	.section .data.early
	.type tlb_table, object
tlb_table:
	tlb_entry_8 0
	tlb_entry_8 8
	tlb_entry_8 16
	tlb_entry_8 24
	tlb_entry_8 32
	tlb_entry_8 40
	tlb_entry_8 48
	tlb_entry_8 56
