#include <ouroboros/arch/mips/syscall.h>

	.section .rodata.header

_header_load_addr:
	.word _load_addr

_header_entry_addr:
	.word _start

	.section .text.early

	.global _start
	.type _start, function
_start:
	la $a0, tlb_read_data
	la $t0, tlb_read_data_num_entries
	lw $a1, ($t0)
	syscall OU_SYSCALL_READTLB

0:
	b 0b
