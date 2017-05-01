#include <ouroboros/arch/mips/syscall.h>
#include <ouroboros/arch/mips/context.h>

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

	li $t0, MIPS_CP0_ENTRY_LO_PFN_PFN(0) | MIPS_CP0_ENTRY_LO_D | MIPS_CP0_ENTRY_LO_V
	sw $t0, TLB_ENTRY_ACCESS_ENTRY_LO1_OFFSET($a0)

	la $a0, context_switch

	.type _swcontext, function
	syscall OU_SYSCALL_SWCONTEXT

	la $t0, 0x40001FFC
	li $t1, 0xCAFEBABE
	sw $t1, ($t0)

0:
	b 0b
